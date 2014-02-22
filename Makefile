PREFIX ?= /usr/local
CFLAGS += -std=c99 -Wall -Wextra
OBJS = $(filter-out cbuild.o, $(patsubst %.c, %.o, $(wildcard *.c)))

cbuild: $(OBJS)

debug: CFLAGS += -g
debug: cbuild

install: cbuild
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp man1/* $(PREFIX)/share/man/man1
	install cbuild $(PREFIX)/bin

clean:
	rm -f cbuild $(OBJS)

.PHONY: install clean
