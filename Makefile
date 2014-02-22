PREFIX ?= /usr/local
CFLAGS += -std=c99 -Wall -Wextra
OBJS = env.o

cbuild: $(OBJS) sys.a

debug: CFLAGS += -g
debug: cbuild

sys.a: sys_unix.o sys_windows.o
	ar crus $@ $^

install: cbuild
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	cp man1/* $(PREFIX)/share/man/man1
	install cbuild $(PREFIX)/bin

clean:
	rm -f cbuild *.o *.a

.PHONY: install clean
