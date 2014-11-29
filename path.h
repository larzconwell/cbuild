#ifndef CBUILD_PATH_H
#define CBUILD_PATH_H 1

// extname returns a pointer to the extension in a given string. NULL is returned
// if there's no extension.
char *extname(const char *);

// path_join joins two paths and returns a new string. NULL is returned if the
// paths can't be joined.
char *path_join(const char *, const char *);

// stripbaseext strips the extension from the given string. The given string
// is modified.
char *stripbaseext(char *);

#endif
