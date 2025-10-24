CXX = clang++
SUBDIRS = test
NPROC := $(shell nproc)

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

all: $(OBJS)
	for d in $(SUBDIRS); do $(MAKE) -C $$d -j$(NPROC); done

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
