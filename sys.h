// Copyright 2014 Larz Conwell, see LICENSE for details.
#ifndef CBUILD_SYS_H
#define CBUILD_SYS_H 1

// sys_isatty checks if a file descriptor is associated with a terminal,
// on non Unix machines this should return -1.
int sys_isatty(int);

// sys_tmpdir creates a temporary directory. NULL indicates error.
char *sys_tmpdir(void);

// sys_tmpdirpath retrieves the base temporary directory. The result
// should not be freed.
char *sys_tmpdirpath(void);

// sys_currtime retrieves the current time as a string. NULL
// indicates error.
char *sys_currtime(void);

// sys_mkdirp creates the given directory and it's parents. -1
// indicates error.
int sys_mkdirp(const char *);

// sys_mkdir creates the given directory, -1 indicates error.
int sys_mkdir(const char *);

// sys_rmrf removes a directory and it's contents. -1 indicates
// error.
int sys_rmrf(const char *);

#endif
