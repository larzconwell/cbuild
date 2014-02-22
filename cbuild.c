/*
 * cbuild.c
 *
 * Copyright 2014 Larz Conwell, see LICENSE for details.
 */
#include <stdlib.h>
#include <stdio.h>

#include "env.h"

int main(void) {
  int rc = 0;

  struct env *env = malloc(sizeof(struct env));
  if (env == NULL) {
    fprintf(stderr, "Unable to allocate environment.");
    return 1;
  }

  int n = newEnv(env);
  if (n <= 0) {
    fprintf(stderr, "Unable to generate environment.");
    rc = 1;
    goto cleanup;
  }

  printf("%s %s %s %s %s %s %s %s %s %s %s %s", env->os, env->arch, env->ar, env->as, env->cc, env->cpp, env->arflags, env->asflags, env->cflags, env->cppflags, env->ldflags, env->ldlibs);

  rc = 0;
  goto cleanup;

cleanup:
  free(env);
  return rc;
}
