PREFIX ?= /usr/local

install:
	mkdir -p $(PREFIX)/share/man/man1
	cp man1/* $(PREFIX)/share/man/man1

.PHONY: install
