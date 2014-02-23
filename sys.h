// Copyright 2014 Larz Conwell, see LICENSE for details.
#ifndef CBUILD_SYS_H
#define CBUILD_SYS_H 1

#include <stdio.h>

// istty checks if a file descriptor is associated with a terminal, on non
// Unix machines this should return -1.
int istty(int);

// tmpdir creates a temporary directory. NULL indicates error.
char *tmpdir(void);

// currtime retrieves the current time as a string. NULL indicates error.
char *currtime(void);

// mkdirp creates the given directory and it's parents. -1 indicates error.
int mkdirp(const char *);

// rmrf removes a directory and it's contents. -1 indicates error.
int rmrf(const char *);

#endif
