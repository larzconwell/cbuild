#include <stdlib.h>
#include <string.h>

#include "util.h"

char *strdup(const char *str) {
  size_t len = strlen(str) + 1;
  char *new = malloc(len);
  if (new == NULL) {
    return NULL;
  }

  memcpy(new, str, len);
  return new;
}

char *trailstr(char *str, char c) {
  size_t i = strlen(str) - 1;

  for (; i > 0 && str[i] == c; i--) {
    str[i] = '\0';
  }

  return str;
}
