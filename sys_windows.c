// Copyright 2014 Larz Conwell, see LICENSE for details.
#include "detect.h"
#if CUR_OS_NUM == 5
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <errno.h>

#include "sys.h"

int sys_isatty(int fd) {
  fd = -1;
  return fd;
}

char *sys_tmpdirpath(void) {
  char *dir = getenv("TEMP");
  if (dir == NULL) {
    dir = getenv("TMP");
  }

  return dir;
}

int sys_mkdirp(const char *path) {
  int n = _mkdir(path);
  if (n < 0 && errno != EEXIST) {
    return -1;
  }

  return 0;
}

int sys_rmrf(const char *path) {
  return 0;
}

#endif
