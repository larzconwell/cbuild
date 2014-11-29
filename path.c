#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "path.h"
#include "sys.h"
#include "util.h"

char *extname(const char *path) {
  char *cpy = strdup(path);
  if (cpy == NULL) {
    return NULL;
  }

  char *name = basename(cpy);
  if (name == NULL) {
    free(cpy);
    return NULL;
  }

  // Get ext, if no . found, or the result is the same as the name then it's
  // a hidden path.
  char *ext = strrchr(name, '.');
  if (ext == NULL || ext == name) {
    free(cpy);
    return NULL;
  }

  // Get the pointer to the ext from the given str rather than returning a
  // copy to simplify caller code.
  char *s = (char *)path;
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    if (strcmp(s, ext) == 0) {
      break;
    }

    (void)*s++;
  }

  free(cpy);
  return s;
}

char *path_join(const char *dir, const char *name) {
  char *path = malloc(strlen(dir) + strlen(name) + 2);
  if (path == NULL) {
    return NULL;
  }

  sprintf(path, "%s%c%s", dir, '/', name);
  return path;
}

char *stripbaseext(char *path) {
  char *ext = strrchr(path, '.');
  if (ext == NULL || ext == path) {
    return path;
  }

  ext[0] = '\0';
  return path;
}
