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

int istty(int fd) {
  return isatty(fd);
}

char *tmpdir(void) {
  char buf[256];

  char *time = currtime();
  if (time == NULL) {
    return NULL;
  }

  char *dir = getenv("TMPDIR");
  if (dir == NULL) {
    dir = "/tmp";
  }

  int n = snprintf(buf, sizeof(buf), "%s/cbuild-%s", dir, time);
  if (n < 0) {
    free(time);
    return NULL;
  }

  char *dirdup = malloc(strlen(buf)+1);
  if (dirdup == NULL) {
    free(time);
    return NULL;
  }
  strcpy(dirdup, buf);

  n = mkdirp(dirdup);
  if (n < 0) {
    free(time);
    free(dirdup);
    return NULL;
  }

  free(time);
  return dirdup;
}

int mkdirp(const char *path) {
  size_t pathlen = strlen(path);

  char *pathdup = malloc(pathlen+1);
  if (pathdup == NULL) {
    return -1;
  }
  strcpy(pathdup, path);

  // Create each directory in the path.
  for (char *p = pathdup+1; *p; p++) {
    if (*p == '/') {
      *p = '\0';

      int n = mkdir(pathdup, S_IRWXU);
      if (n < 0 && errno != EEXIST) {
        free(pathdup);
        return -1;
      }

      *p = '/';
    }
  }

  // Create the final path.
  int n = mkdir(pathdup, S_IRWXU);
  if (n < 0 && errno != EEXIST) {
    free(pathdup);
    return -1;
  }

  free(pathdup);
  return 0;
}

int rmrf(const char *path) {
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
      n = rmrf(full);
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
