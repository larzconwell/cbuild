// Copyright 2014 Larz Conwell, see LICENSE for details.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "os.h"
#include "arch.h"
#include "env.h"
#include "sys.h"
#include "detect.h"

static const char *USAGE = "Usage: cbuild [-c] [-o output] files...";

// os_list is a list of supported oses.
static struct os os_list[] = {
  {0, "freebsd"},
  {1, "openbsd"},
  {2, "netbsd"},
  {3, "darwin"},
  {4, "linux"},
  {5, "windows"},
  {-1, ""}
};

// arch_list is a list of supported architectures.
static struct arch arch_list[] = {
  {0, "386"},
  {1, "amd64"},
  {2, "arm"},
  {-1, ""}
};

int main(int argc, char **argv) {
  int rc = 0;

  struct env *env = newenv();
  if (env == NULL) {
    fprintf(stderr, "Unable to generate environment.\n");
    rc = 1;
    goto cleanup;
  }

  // Get the appropriate os struct.
  struct os os;
  for (int i = 0; ; i++) {
    os = os_list[i];
    if (os.ident < 0) {
      break;
    }

    if (strcmp(os.name, env->osstr) == 0) {
      env->os = &os;
      break;
    }
  }
  if (env->os == NULL) {
    fprintf(stderr, "OS %s is not supported.\n", env->osstr);
    rc = 1;
    goto cleanup;
  }

  // Get the appropriate arch struct.
  struct arch arch;
  for (int i = 0; ; i++) {
    arch = arch_list[i];
    if (arch.ident < 0) {
      break;
    }

    if (strcmp(arch.name, env->archstr) == 0) {
      env->arch = &arch;
      break;
    }
  }
  if (env->arch == NULL) {
    fprintf(stderr, "ARCH %s is not supported.\n", env->archstr);
    rc = 1;
    goto cleanup;
  }

  // Check if we should display help.
  int tty = istty(0);
  if (argc <= 1) {
    if (tty < 0 || tty >= 1) {
      fprintf(stderr, "%s\n", USAGE);
      rc = 2;
      goto cleanup;
    }
  }

  // Create build directory.
  char *builddir = tmpdir();
  if (builddir == NULL) {
    fprintf(stderr, "Unable to create build directory.\n");
    rc = 1;
    goto cleanup;
  }

  printf("%s\n", builddir);

  // Clean up the build directory.
  int n = rmrf(builddir);
  free(builddir);
  if (n < 0) {
    fprintf(stderr, "Unable to remove build directory.\n");
    rc = 1;
    goto cleanup;
  }

  rc = 0;
  goto cleanup;

cleanup:
  free(env);
  return rc;
}
