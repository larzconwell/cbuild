// Copyright 2014 Larz Conwell, see LICENSE for details.
#include "detect.h"
#if CUR_OS_NUM == 5
#include <stdio.h>

#include "sys.h"

int istty(int fd) {
  fd = -1;
  return fd;
}

char *tmpdir(void) {
  return NULL;
}

int mkdirp(const char *path) {
  return 0;
}

int rmrf(const char *path) {
  return 0;
}

#endif
