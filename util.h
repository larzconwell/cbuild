#ifndef CBUILD_UTIL_H
#define CBUILD_UTIL_H 1

// strdup implements strdup found in the POSIX standard.
char *strdup(const char *);

// trailstr strips the given character from from the end of str.
char *trailstr(char *, char);

#endif
