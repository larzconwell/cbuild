PREFIX ?= /usr/local
CFLAGS += -std=c99 -Wall -Wextra
DEPS = deps/commander/commander.o deps/vector/vector.o
OBJS = sys.o path.o detect.o util.o

cbuild: $(DEPS) $(OBJS)

debug: CFLAGS += -g
debug: cbuild

install: cbuild
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp man1/* $(PREFIX)/share/man/man1
	install cbuild $(PREFIX)/bin

clean:
	rm -rf cbuild $(OBJS) $(DEPS)

.PHONY: install clean
