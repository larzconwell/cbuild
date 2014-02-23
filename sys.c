// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sys.h"

char *currtime(void) {
  time_t time_val = time(NULL);
  if (time_val == -1) {
    return NULL;
  }

  struct tm *now = localtime(&time_val);
  if (now == NULL) {
    return NULL;
  }

  char *timestr = asctime(now);
  if (timestr == NULL) {
    return NULL;
  }

  char *timedup = malloc(strlen(timestr)+1);
  if (timedup == NULL) {
    return NULL;
  }
  strcpy(timedup, timestr);

  // Remove spaces and strip newline.
  char *i = timedup;
  char *j = timedup;
  while (*j != '\0') {
    *i = *j++;
    if (*i != ' ' && *i != '\n') {
      i++;
    }
  }
  *i = '\0';

  return timedup;
}
