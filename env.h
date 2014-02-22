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
  char *osStr;
  char *archStr;
  char *ar;
  char *as;
  char *cc;
  char *cpp;
  char *arflags;
  char *asflags;
  char *cflags;
  char *cppflags;
  char *ldflags;
  char *ldlibs;
};

// newEnv fills the given env with the current environment
// configuration, including defaults if they're not given. 0 is returned
// if the env couldn't be filled. The resulting fields should not be freed.
int newEnv(struct env *);

#endif
