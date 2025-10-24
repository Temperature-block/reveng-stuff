CXX = clang++
NPROC := $(shell nproc)

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

all: $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
