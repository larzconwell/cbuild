// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sys.h"

char *sys_currtime(void) {
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

char *sys_tmpdir(void) {
  char buf[256];
  char *dir = sys_tmpdirpath();

  char *time = sys_currtime();
  if (time == NULL) {
    return NULL;
  }

  int n = snprintf(buf, sizeof(buf), "%s/cbuild-%s", dir, time);
  if (n < 0) {
    free(time);
    return NULL;
  }

  char *dirdup = malloc(strlen(buf)+1);
  if (dirdup == NULL) {
    free(time);
    return NULL;
  }
  strcpy(dirdup, buf);

  n = sys_mkdirp(dirdup);
  if (n < 0) {
    free(time);
    free(dirdup);
    return NULL;
  }

  free(time);
  return dirdup;
}

int sys_mkdirp(const char *path) {
  size_t pathlen = strlen(path);

  char *pathdup = malloc(pathlen+1);
  if (pathdup == NULL) {
    return -1;
  }
  strcpy(pathdup, path);

  // Create each directory in the path.
  for (char *p = pathdup+1; *p; p++) {
    if (*p == '/') {
      *p = '\0';

      int n = sys_mkdir(pathdup);
      if (n < 0) {
        free(pathdup);
        return -1;
      }

      *p = '/';
    }
  }

  // Create the final path.
  int n = sys_mkdir(pathdup);
  if (n < 0) {
    free(pathdup);
    return -1;
  }

  free(pathdup);
  return 0;
}
