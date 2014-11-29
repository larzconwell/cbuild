#include <stdlib.h>
#include <string.h>

#include "sys.h"

platform_t os_list[] = {
  OPENBSD_OS,
  NETBSD_OS,
  FREEBSD_OS,
  LINUX_OS,
  DARWIN_OS,
  WINDOWS_OS,
  UNKNOWN_OS
};

platform_t arch_list[] = {
  I386_ARCH,
  AMD64_ARCH,
  ARM_ARCH,
  UNKNOWN_ARCH
};

platform_t dest_os(void) {
  const char *name = getenv("OS");
  if (name == NULL) {
    name = ((platform_t)HOST_OS).name;
  }

  for (int i = 0; ; i++) {
    platform_t dest = os_list[i];
    if (dest.ident == -1) {
      break;
    }

    if (strcmp(dest.name, name) == 0) {
      return dest;
    }
  }

  return (platform_t)UNKNOWN_OS;
}

platform_t dest_arch(void) {
  const char *name = getenv("ARCH");
  if (name == NULL) {
    name = ((platform_t)HOST_ARCH).name;
  }

  for (int i = 0; ; i++) {
    platform_t dest = arch_list[i];
    if (dest.ident == -1) {
      break;
    }

    if (strcmp(dest.name, name) == 0) {
      return dest;
    }
  }

  return (platform_t)UNKNOWN_OS;
}
