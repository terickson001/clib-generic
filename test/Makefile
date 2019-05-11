CC=gcc

IDIR=../
SDIR=.
ODIR=obj

CFLAGS=-I$(IDIR) -Wall -Wextra -Wno-unused-variable -Wno-implicit-fallthrough -O0 -g
LDFLAGS=-pthread -ldl

_DEPS=lib.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_SRCS=main.c
SRCS=$(patsubst %,$(SDIR)/%,$(_SRCS))

_OBJS=$(_SRCS:.c=.o)
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))

BINNAME=test

all: $(BINNAME)

$(BINNAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(BINNAME)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm $(ODIR)/*.o
