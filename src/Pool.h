#ifndef RASTR_POOL_H
#define RASTR_POOL_H

#include <cstdlib>
#include "utilities.h"
#include "logger.h"

/* take a type and a function to clone a value of that type */
template <typename T, void (*destroy)(T*)> // T* (*clone)(T*)>
class Pool {
  public:
    // gives the largest possible index
    const std::size_t Null = (std::size_t) -1;

    Pool(std::size_t capacity = 16) {
        buffer_ = static_cast<Node*>(malloc_or_fail(sizeof(Node) * capacity));
        capacity_ = capacity;
        size_ = 0;
        front_ = Null;
        back_ = Null;
        free_ = 0;

        Node* node = buffer_;

        for (std::size_t i = 0; i < capacity_; ++i) {
            node->previous = i == 0 ? Null : (i - 1);
            node->next = i == (capacity_ - 1) ? Null : (i + 1);
            node->free = true;
            node->data = nullptr;
            ++node;
        }
    }

    ~Pool() {
        free(buffer_);
    }

    std::size_t get_size() const {
        return size_;
    }

    std::size_t get_capacity() const {
        return capacity_;
    }

    void resize(std::size_t capacity) {
        // resize only if larger capacity is requested
        if (capacity <= capacity_) {
            return;
        }

        buffer_ = (Node*) realloc_or_fail(buffer_, sizeof(Node) * capacity);

        for (std::size_t index = capacity_; index < capacity; ++index) {
            deallocate_(index);
        }

        capacity_ = capacity;
    }

    void clear() {
        std::size_t index = front_;
        while (index != Null) {
            std::size_t next = get_next_(index);
            destroy(deallocate_(index));
            index = next;
        }

        front_ = Null;
        back_ = Null;
        size_ = 0;
    }

    std::size_t front() const {
        return front_;
    }

    std::size_t back() const {
        return back_;
    }

    T* get_front() const {
        if (get_size() == 0) {
            fail_with("attempt to access the first element of an empty list");
        }

        return get_data_(front_);
    }

    T* get_back() const {
        if (get_size() == 0) {
            fail_with("attempt to access the last element of an empty list");
        }

        return get_data_(back_);
    }

    std::size_t push_back(T* data) {
        std::size_t index = allocate_(data);

        if (front_ == Null) {
            front_ = index;
        } else {
            link_(back_, index);
        }

        back_ = index;
        ++size_;

        return index;
    }

    std::size_t push_front(T* data) {
        std::size_t index = allocate_(data);

        if (front_ == Null) {
            back_ = index;
        } else {
            link_(index, front_);
        }

        front_ = index;
        ++size_;

        return index;
    }

    std::size_t insert(T* data, std::size_t before) {
        if (before == Null) {
            return push_back(data);
        } else if (before == front_) {
            return push_front(data);
        } else {
            int index = allocate_(data);
            int previous = get_previous_(before);

            link_(previous, index);
            link_(index, before);

            ++size_;

            return index;
        }
    }

    T* at(std::size_t index) {
        return get_data_(index);
    }

    T* pop_front() {
        std::size_t index = front_;
        std::size_t size = get_size();

        if (size == 0) {
            fail_with("attempt to remove element from an empty list");
        } else if (size == 1) {
            front_ = Null;
            back_ = Null;
        } else {
            std::size_t next = get_next_(front_);
            set_previous_(next, Null);
            front_ = next;
        }

        --size_;
        return deallocate_(index);
    }

    T* pop_back() {
        std::size_t index = back_;
        std::size_t size = get_size();

        if (size == 0) {
            fail_with("attempt to remove element from an empty list");
        }

        else if (size == 1) {
            front_ = Null;
            back_ = Null;
        }

        else {
            std::size_t previous = get_previous_(back_);
            set_next_(previous, Null);
            back_ = previous;
        }

        --size_;
        return deallocate_(index);
    }

    T* remove(std::size_t index) {
        if (size_ == 0) {
            fail_with("attempt to remove element from an empty list");
        }

        else if (index == front_) {
            return pop_front();
        }

        else if (index == back_) {
            return pop_back();
        }

        else {
            std::size_t previous = get_previous_(index);
            std::size_t next = get_next_(index);
            link_(previous, next);
            --size_;
            return deallocate_(index);
        }
    }

  private:
    struct Node {
        bool free;
        int previous;
        int next;
        T* data;
    };

    Node* buffer_;
    std::size_t front_;
    std::size_t back_;
    std::size_t free_;
    std::size_t capacity_;
    std::size_t size_;

    void set_free_(std::size_t index) {
        buffer_[index].free = true;
    }

    void set_used_(std::size_t index) {
        buffer_[index].free = false;
    }

    std::size_t get_previous_(std::size_t index) {
        return buffer_[index].previous;
    }

    void set_previous_(std::size_t index, int previous) {
        buffer_[index].previous = previous;
    }

    std::size_t get_next_(std::size_t index) {
        return buffer_[index].next;
    }

    void set_next_(std::size_t index, int next) {
        buffer_[index].next = next;
    }

    void link_(std::size_t index, std::size_t next) {
        set_next_(index, next);
        set_previous_(next, index);
    }

    T* get_data_(std::size_t index) {
        return buffer_[index].data;
    }

    void set_data_(std::size_t index, T* data) {
        buffer_[index].data = data;
    }

    bool full_() {
        return size_ == capacity_;
    }

    std::size_t allocate_(T* data) {
        if (full_()) {
            resize(get_capacity() * 2 + 1);
        }

        std::size_t next_free = get_next_(free_);
        std::size_t index = free_;
        free_ = next_free;

        set_used_(index);
        set_data_(index, data);
        set_next_(index, Null);
        set_previous_(index, Null);

        return index;
    }

    T* deallocate_(std::size_t index) {
        T* data = get_data_(index);

        set_data_(index, nullptr);
        set_free_(index);
        set_next_(index, free_);
        set_previous_(index, Null);
        free_ = index;

        

        return data;
    }
};

#endif /* RASTR_POOL_H */
