#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <dirent.h>

#include "detect.h"
#include "path.h"
#include "util.h"

char *source_exts[] = {".c", ".cc", ".cxx", ".cpp", ".c++", ".s", ".S", ".asm"};

// readline reads a line of data from a file, stripping line endings. NULL
// is returned if reading fails.
static char *readline(FILE *);
static char *readline(FILE *file) {
  char seg[BUFSIZ] = {'\0'};
  char *line = NULL;
  bool done = false;

  while (!done) {
    fgets(seg, sizeof(seg), file);
    if (feof(file) != 0) {
      break;
    }
    if (ferror(file) != 0) {
      if (line != NULL) {
        free(line);
      }
      return NULL;
    }
    size_t len = strlen(seg);

    // Strip trailing line endings.
    if (seg[len - 1] == '\n' || seg[len - 1] == '\r') {
      for (size_t i = len; i > 0; i--) {
        size_t j = i - 1;

        if (seg[j] == '\n' || seg[j] == '\r') {
          seg[j] = '\0';
          len--;
        } else {
          break;
        }
      }

      done = true;
    }

    // Allocate memory for line.
    if (line == NULL) {
      line = malloc(len + 1);
      if (line == NULL) {
        return NULL;
      }
      memset(line, '\0', len + 1);
    } else {
      char *temp = realloc(line, strlen(line) + len + 1);
      if (temp == NULL) {
        free(line);
        return NULL;
      }
      line = temp;
    }

    strcat(line, seg);
  }

  return line;
}

// build_tag retrieves the build tag for a given file. NULL is returned on
// failure, and the string literal "" is returned if no build path is found,
// other values should be free'd.
static char *build_tag(const char *);
static char *build_tag(const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    return NULL;
  }

  for (int i = 0; i < 10; i++) {
    char *line = readline(file);
    if (line == NULL) {
      if (feof(file) != 0) {
        break;
      }

      fclose(file);
      return NULL;
    }

    // Check if the line includes +build at all, don't waste time if not.
    if (strstr(line, "+build") == NULL) {
      free(line);
      continue;
    }

    // Check if we're in a comment.
    if (strncmp(line, "//", 2) != 0) {
      free(line);
      continue;
    }
    char *data = line+2;
    char *d = data;
    size_t len = strlen(data);

    // Skip spaces.
    for (size_t i = 0; i < len; i++) {
      if (d[i] == ' ') {
        (void)*data++;
      } else {
        break;
      }
    }

    // Check if the next text is +build as it should be.
    if (strncmp(data, "+build", 6) == 0) {
      char *new = strdup(data);
      free(line);
      fclose(file);
      return new;
    }

    free(line);
  }

  fclose(file);
  return "";
}

// parse_build checks if a path should be included for a dest platfom by parsing
// the build tag found in the contents. -1 is returned on errors, 0 if the path
// wasn't added, and 1 if the path was added.
static int parse_build(vector_t *, platform_t, platform_t, char *, char *);
static int parse_build(vector_t *args, platform_t os, platform_t arch, char *buildtag, char *path) {
  char combined[512] = {'\0'};

  char *tok = strtok(buildtag, " ");
  while (tok != NULL) {
    if (strcmp(tok, "+build") == 0) {
      tok = strtok(NULL, " ");
      continue;
    }
    sprintf(combined, "%s,%s", os.name, arch.name);

    // Matches with OS, ARCH, or OS,ARCH. Others are skipped.
    if (strcmp(tok, os.name) == 0 || strcmp(tok, arch.name) == 0 ||
        strcmp(tok, combined) == 0) {
      path_arg_t *arg = malloc(sizeof(path_arg_t));
      if (arg == NULL) {
        return -1;
      }
      arg->path = path;
      arg->detected = true;

      if (vector_push(args, arg) == NULL) {
        free(arg);
        return -1;
      }

      return 1;
    }

    tok = strtok(NULL, " ");
  }

  return 0;
}

// parse_fstrain checks if a path should be included for a dest platform by
// parsing the files name. -1 is returned on errors, 0 if the path wasn't
// added, and 1 if the path was added.
static int parse_fstrain(vector_t *, platform_t, platform_t, char *, char *);
static int parse_fstrain(vector_t *args, platform_t os, platform_t arch, char *name, char *path) {
  int ret = 0;
  char *queue[2] = {NULL};
  size_t queuelen = sizeof(queue) / sizeof(char *);

  // Fast path for paths without underscores.
  if (strstr(name, "_") == NULL) {
    path_arg_t *arg = malloc(sizeof(path_arg_t));
    if (arg == NULL) {
      ret = -1;
      goto cleanup;
    }
    arg->path = path;
    arg->detected = true;

    if (vector_push(args, arg) == NULL) {
      free(arg);
      ret = -1;
      goto cleanup;
    }

    ret = 1;
    goto cleanup;
  }

  // Get the last two underscore items in the path.
  char *tok = strtok(name, "_");
  while (tok != NULL) {
    // Shift the items in the queue.
    for (size_t i = 0; i < queuelen; i++) {
      if (i == 0 && queue[i] != NULL) {
        free(queue[i]);
      }

      if (i > 0) {
        queue[i-1] = queue[i];
      }
    }

    char *cpy = strdup(tok);
    if (cpy == NULL) {
      ret = -1;
      goto cleanup;
    }

    queue[queuelen - 1] = cpy;
    tok = strtok(NULL, "_");
  }
  char *last = stripbaseext(queue[queuelen - 1]);

  // Check first if the last item isn't in either OS or ARCH list.
  bool found = false;
  for (int i = 0; ; i++) {
    platform_t plat = os_list[i];
    if (plat.ident == -1) {
      break;
    }

    if (strcmp(last, plat.name) == 0) {
      found = true;
      break;
    }
  }
  if (!found) {
    for (int i = 0; ; i++) {
      platform_t plat = arch_list[i];
      if (plat.ident == -1) {
        break;
      }

      if (strcmp(last, plat.name) == 0) {
        found = true;
        break;
      }
    }
  }
  if (!found) {
    path_arg_t *arg = malloc(sizeof(path_arg_t));
    if (arg == NULL) {
      ret = -1;
      goto cleanup;
    }
    arg->path = path;
    arg->detected = true;

    if (vector_push(args, arg) == NULL) {
      free(arg);
      ret = -1;
      goto cleanup;
    }

    ret = 1;
    goto cleanup;
  }

  // Check if *_OS format.
  if (strcmp(last, os.name) == 0) {
    path_arg_t *arg = malloc(sizeof(path_arg_t));
    if (arg == NULL) {
      ret = -1;
      goto cleanup;
    }
    arg->path = path;
    arg->detected = true;

    if (vector_push(args, arg) == NULL) {
      free(arg);
      ret = -1;
      goto cleanup;
    }

    ret = 1;
    goto cleanup;
  }

  // Check if *_ARCH or *_OS_ARCH formats.
  if (strcmp(last, arch.name) == 0) {
    // Check if the item before the last is a valid OS.
    bool found = false;
    for (int i = 0; ; i++) {
      platform_t plat = os_list[i];
      if (plat.ident == -1) {
        break;
      }

      if (strcmp(queue[queuelen - 2], plat.name) == 0) {
        found = true;
        break;
      }
    }

    // If the item before the last is the dest OS, or if it's no a valid OS
    // we can add it to the list.
    if (strcmp(queue[queuelen - 2], os.name) == 0 || !found) {
      path_arg_t *arg = malloc(sizeof(path_arg_t));
      if (arg == NULL) {
        ret = -1;
        goto cleanup;
      }
      arg->path = path;
      arg->detected = true;

      if (vector_push(args, arg) == NULL) {
        free(arg);
        ret = -1;
        goto cleanup;
      }

      ret = 1;
      goto cleanup;
    }
  }

cleanup:
  for (size_t i = 0; i < queuelen; i++) {
    if (queue[i] != NULL) {
      free(queue[i]);
    }
  }
  return ret;
}

vector_t *detect_files(vector_t *args, platform_t os, platform_t arch, const char *path) {
  DIR *dir = NULL;
  char *dircpy = strdup(path);
  if (dircpy == NULL) {
    return NULL;
  }
  char *namecpy = strdup(path);
  if (namecpy == NULL) {
    args = NULL;
    goto cleanup;
  }
  char *dirp = dirname(dircpy);
  char *namep = basename(namecpy);
  size_t namelen = strlen(namep);

  dir = opendir(dirp);
  if (dir == NULL) {
    args = NULL;
    goto cleanup;
  }

  size_t extslen = sizeof(source_exts) / sizeof(char *);
  while (1) {
    int curerr = errno;
    struct dirent *entry = readdir(dir);
    if (entry == NULL) {
      if (errno == curerr) {
        break; // End of the items.
      }

      args = NULL;
      goto cleanup;
    }

    // If it doesn't start with the name skip it.
    if (strncmp(entry->d_name, namep, namelen) != 0) {
      continue;
    }

    char *ext = extname(entry->d_name);
    if (ext == NULL) {
      continue;
    }

    // Skip paths that aren't source files.
    bool skip = true;
    for (size_t i = 0; i < extslen; i++) {
      if (strcmp(ext, source_exts[i]) == 0) {
        skip = false;
        break;
      }
    }
    if (skip) {
      continue;
    }

    char *path = path_join(dirp, entry->d_name);
    if (path == NULL) {
      args = NULL;
      goto cleanup;
    }

    char *buildtag = build_tag(path);
    if (buildtag == NULL) {
      free(path);
      args = NULL;
      goto cleanup;
    }
    // build_tag returns empty string lit if no build tag was found.
    if (strlen(buildtag) == 0) {
      buildtag = NULL;
    }
    int res = 0;

    // A build tag was found, so only add if it's successful.
    if (buildtag != NULL) {
      res = parse_build(args, os, arch, buildtag, path);
    // No build tag found, so detect through the file name.
    } else {
      res = parse_fstrain(args, os, arch, entry->d_name, path);
    }
    if (res == -1) {
      free(path);
      if (buildtag != NULL) {
        free(buildtag);
      }
      args = NULL;
      goto cleanup;
    }

    if (res == 0) {
      free(path);
    }
    if (buildtag != NULL) {
      free(buildtag);
    }
  }

cleanup:
  if (dir != NULL) {
    closedir(dir);
  }
  if (dircpy != NULL) {
    free(dircpy);
  }
  if (namecpy != NULL) {
    free(namecpy);
  }
  return args;
}
