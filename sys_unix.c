// Copyright 2014 Larz Conwell, see LICENSE for details.
#include "detect.h"
#if CUR_OS_NUM != 5
#define _BSD_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "sys.h"

int sys_isatty(int fd) {
  return isatty(fd);
}

char *sys_tmpdirpath(void) {
  char *dir = getenv("TMPDIR");
  if (dir == NULL) {
    dir = "/tmp";
  }

  return dir;
}

int sys_mkdir(const char *path) {
  int n = mkdir(path, S_IRWXU);
  if (n < 0 && errno != EEXIST) {
    return -1;
  }

  return 0;
}

int sys_rmrf(const char *path) {
  struct dirent *entry;

  DIR *dir = opendir(path);
  if (dir == NULL) {
    return -1;
  }

  // Remove files and directories recursively.
  while ((entry = readdir(dir)) != NULL) {
    // Skip ., ..
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char *full = malloc(strlen(path)+strlen(entry->d_name)+2);
    if (full == NULL) {
      closedir(dir);
      return -1;
    }

    int n = sprintf(full, "%s/%s", path, entry->d_name);
    if (n < 0) {
      free(full);
      closedir(dir);
      return -1;
    }

    if (entry->d_type == DT_DIR) {
      n = sys_rmrf(full);
    } else {
      n = remove(full);
    }
    free(full);
    if (n < 0 && errno != ENOENT) {
      closedir(dir);
      return -1;
    }
  }

  // Remove the final parent directory.
  closedir(dir);
  int n = remove(path);
  if (n < 0 && errno != ENOENT) {
    return -1;
  }

  return 0;
}

#endif
