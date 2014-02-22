// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "os.h"
#include "arch.h"
#include "env.h"
#include "sys.h"
#include "detect.h"

// Usage.
static const char *USAGE = "Usage: cbuild [-c] [-o output] files...";

// List of supported oses.
static struct os osList[] = {
  {0, "freebsd"},
  {1, "openbsd"},
  {2, "netbsd"},
  {3, "darwin"},
  {4, "linux"},
  {5, "windows"},
  {-1, ""}
};

// List of supported architectures.
static struct arch archList[] = {
  {0, "386"},
  {1, "amd64"},
  {2, "arm"},
  {-1, ""}
};

int main(int argc, char **argv) {
  int rc = 0;

  struct env *env = malloc(sizeof(struct env));
  if (env == NULL) {
    fprintf(stderr, "Unable to allocate environment.\n");
    return 1;
  }

  int n = newEnv(env);
  if (n <= 0) {
    fprintf(stderr, "Unable to generate environment.\n");
    rc = 1;
    goto cleanup;
  }

  // Get the appropriate os struct.
  struct os os;
  for (int i = 0; ; i++) {
    os = osList[i];
    if (os.ident < 0) {
      break;
    }

    if (strcmp(os.name, env->osStr) == 0) {
      env->os = &os;
      break;
    }
  }
  if (env->os == NULL) {
    fprintf(stderr, "OS %s is not supported.\n", env->osStr);
    rc = 1;
    goto cleanup;
  }

  // Get the appropriate arch struct.
  struct arch arch;
  for (int i = 0; ; i++) {
    arch = archList[i];
    if (arch.ident < 0) {
      break;
    }

    if (strcmp(arch.name, env->archStr) == 0) {
      env->arch = &arch;
      break;
    }
  }
  if (env->arch == NULL) {
    fprintf(stderr, "ARCH %s is not supported.\n", env->archStr);
    rc = 1;
    goto cleanup;
  }

  // Check if we're displaying help or compiling stdin.
  if (argc <= 1) {
    int tty = isaterm(0);

    if (tty < 0 || tty >= 1) {
      fprintf(stderr, "%s\n", USAGE);
      rc = 2;
      goto cleanup;
    }

    // Compile from stdin
  }

  rc = 0;
  goto cleanup;

cleanup:
  free(env);
  return rc;
}
