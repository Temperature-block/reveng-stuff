SUBDIRS = a1 a2 a3
NPROC := $(shell nproc)

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

all: $(OBJS)
	for d in $(SUBDIRS); do $(MAKE) -C $$d -j$(NPROC); done

