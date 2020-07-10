#include "Node.hpp"

namespace rastr {
namespace ast {

std::atomic<int> Node::id_counter_(-1);

int Node::get_next_id_() {
    return ++id_counter_;
}

} // namespace ast
} // namespace rastr
