#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "deps/commander/commander.h"
#include "deps/vector/vector.h"

#include "cbuild.h"
#include "sys.h"
#include "path.h"
#include "detect.h"
#include "util.h"

// Command line flags.
bool compileOnly = false;
char *out = NULL;

// set_compile sets the compile flag to true.
static void set_compile(command_t *);
static void set_compile(command_t *cmd) {
  (void)(cmd); // Supress unused warning.

  compileOnly = true;
}

// set_out sets the output file to write to.
static void set_out(command_t *);
static void set_out(command_t *cmd) {
  out = (char *)cmd->arg;
}

int main(int argc, char **argv) {
  int ret = 0; // Exit code.
  command_t cmd;
  command_init(&cmd, "cbuild", VERSION);
  command_option(&cmd, "-c", "--compile", "Compile but don't link. The output is an archive of the compiled objects.", set_compile);
  command_option(&cmd, "-o", "--out <name>", "Set the output file name.", set_out);
  command_parse(&cmd, argc, argv);

  vector_t args;
  if (vector_new(&args, 20) == NULL) {
    perror("cbuild");
    ret = 1;
    goto exit;
  }

  // Figure out dest os.
  platform_t os = dest_os();
  if (os.ident == ((platform_t)UNKNOWN_OS).ident) {
    char *name = getenv("OS");
    if (name == NULL) {
      fprintf(stderr, "cbuild: Current OS is not supported.\n");
    } else {
      fprintf(stderr, "cbuild: OS %s is not supported.\n", name);
    }
    ret = 1;
    goto exit;
  }

  // Figure out dest arch.
  platform_t arch = dest_arch();
  if (arch.ident == ((platform_t)UNKNOWN_OS).ident) {
    char *name = getenv("ARCH");
    if (name == NULL) {
      fprintf(stderr, "cbuild: Current architecture is not supported.\n");
    } else {
      fprintf(stderr, "cbuild: ARCH %s is not supported.\n", name);
    }
    ret = 1;
    goto exit;
  }

  // Set the output name if no option set it.
  if (out == NULL) {
    if (compileOnly) {
      out = "out.a";
    } else {
      out = "out";

      if (os.ident == ((platform_t)WINDOWS_OS).ident) {
        out = "out.exe";
      }
    }
  }

  // Error out if no inputs are given.
  if (cmd.argc <= 0) {
    fprintf(stderr, "cbuild: no input files\n");
    ret = 1;
    goto exit;
  }

  // Get list of files to use for the compile step.
  for (int i = 0; i < cmd.argc; i++) {
    vector_t *result = NULL;
    cmd.argv[i] = trailstr(cmd.argv[i], '/');

    if (extname(cmd.argv[i]) != NULL) {
      path_arg_t *arg = malloc(sizeof(path_arg_t));
      if (arg == NULL) {
        perror("cbuild");
        ret = 1;
        goto exit;
      }
      arg->path = cmd.argv[i];
      arg->detected = false;

      result = vector_push(&args, arg);
    } else {
      // If no extension is given get files to use for the dest platform.
      result = detect_files(&args, os, arch, cmd.argv[i]);
    }

    if (result == NULL) {
      perror("cbuild");
      ret = 1;
      goto exit;
    }
  }

  for (size_t i = 0; i < args.len; i++) {
    printf("Using source: %s\n", ((path_arg_t *)vector_get(&args, i))->path);
  }

exit:
  for (size_t i = 0; i < args.len; i++) {
    path_arg_t *arg = vector_get(&args, i);
    if (arg->detected) {
      free(arg->path);
    }
    free(arg);
  }
  vector_free(&args);
  command_free(&cmd);
  return ret;
}
