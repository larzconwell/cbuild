// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>

#include "detect.h"
#include "env.h"

static char buf[256];

struct env *newenv(void) {
  struct env *env = malloc(sizeof(struct env));
  if (env == NULL) {
    return env;
  }

  env->osstr = getenv("OS");
  if (env->osstr == NULL) {
    env->osstr = CUR_OS;
  }

  env->archstr = getenv("ARCH");
  if (env->archstr == NULL) {
    env->archstr = CUR_ARCH;
  }

  env->ar = getenv("AR");
  if (env->ar == NULL) {
    env->ar = "ar";
  }

  env->cc = getenv("CC");
  if (env->cc == NULL) {
    env->cc = "cc";
  }

  env->cpp = getenv("CPP");
  if (env->cpp == NULL) {
    int n = snprintf(buf, sizeof(buf), "%s -E", env->cc);
    if (n < 0) {
      free(env);
      return NULL;
    }

    env->cpp = buf;
  }

  env->arflags = getenv("ARFLAGS");
  if (env->arflags == NULL) {
    env->arflags = "crus";
  }

  env->cflags = getenv("CFLAGS");
  if (env->cflags == NULL) {
    env->cflags = "";
  }

  env->cppflags = getenv("CPPFLAGS");
  if (env->cppflags == NULL) {
    env->cppflags = "";
  }

  env->ldflags = getenv("LDFLAGS");
  if (env->ldflags == NULL) {
    env->ldflags = "";
  }

  env->ldlibs = getenv("LDLIBS");
  if (env->ldlibs == NULL) {
    env->ldlibs = "";
  }

  return env;
}
