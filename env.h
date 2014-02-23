// Copyright 2014 Larz Conwell, see LICENSE for details.
#ifndef CBUILD_ENV_H
#define CBUILD_ENV_H 1

#include "arch.h"
#include "os.h"

// env contains the environment variables to configure the
// build process.
struct env {
  struct os *os;
  struct arch *arch;
  char *osstr;
  char *archstr;
  char *ar;
  char *cc;
  char *cpp;
  char *arflags;
  char *cflags;
  char *cppflags;
  char *ldflags;
  char *ldlibs;
};

// newEnv creates a new env with the current environment, including
// defaults if not given. NULL indicates error, the resulting fields should
// not be freed.
struct env *newenv(void);

#endif
