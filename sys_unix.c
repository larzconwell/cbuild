// Copyright 2014 Larz Conwell, see LICENSE for details.
#include "detect.h"
#if CUR_OS_NUM != 5
#include <unistd.h>

int isaterm(int fd) {
  return isatty(fd);
}

#endif
