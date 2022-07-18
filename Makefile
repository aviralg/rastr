CC=clang
CXX=clang++
RM=rm -f
CPPFLAGS= -std=c++11 -O0 -ggdb3
LDFLAGS=
LDLIBS=

SRCS=$(shell find . -name '*.cpp')
INCS=$(shell find . -name '*.h')

all: main

main: $(SRCS) $(INCS)
	$(CXX) $(CPPFLAGS) $(SRCS) $(LDFLAGS) -o main $(LDLIBS)

clean:
	$(RM) main
