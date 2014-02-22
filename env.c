// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>

#include "detect.h"
#include "env.h"

static char buf[1001];

int newEnv(struct env *env) {
  env->osStr = getenv("OS");
  if (env->osStr == NULL) {
    env->osStr = CUR_OS;
  }

  env->archStr = getenv("ARCH");
  if (env->archStr == NULL) {
    env->archStr = CUR_ARCH;
  }

  env->ar = getenv("AR");
  if (env->ar == NULL) {
    env->ar = "ar";
  }

  env->as = getenv("AS");
  if (env->as == NULL) {
    env->as = "as";
  }

  env->cc = getenv("CC");
  if (env->cc == NULL) {
    env->cc = "cc";
  }

  env->cpp = getenv("CPP");
  if (env->cpp == NULL) {
    int n = snprintf(buf, 1000, "%s -E", env->cc);
    if (n < 0) {
      return 0;
    }

    env->cpp = buf;
  }

  env->arflags = getenv("ARFLAGS");
  if (env->arflags == NULL) {
    env->arflags = "rv";
  }

  env->asflags = getenv("ASFLAGS");
  if (env->asflags == NULL) {
    env->asflags = "";
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

  return 1;
}
