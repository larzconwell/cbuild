#ifndef CBUILD_DETECT_H
#define CBUILD_DETECT_H 1

#include <stdbool.h>

#include "deps/vector/vector.h"

#include "sys.h"

// source_exts is a list of extensions for source files.
extern char *source_exts[];

// path_arg_t contains a path and if it was detected. Used to check what paths
// need to be free'd.
typedef struct path_arg {
  char *path;
  bool detected;
} path_arg_t;

// detect_files adds a list of files that satisfy the dest platform. NULL is
// returned on any failures. Read the man pages for details about detection.
vector_t *detect_files(vector_t *, platform_t, platform_t, const char *);

#endif
