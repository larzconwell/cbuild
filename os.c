/*
 * os.c
 *
 * Copyright 2014 Larz Conwell, see LICENSE for details.
 */
#include "os.h"

// osList contains all the supported os structs.
struct os osList[] = {
  {"freebsd"},
  {"openbsd"},
  {"netbsd"},
  {"darwin"},
  {"linux"},
  {"windows"}
};
