#ifndef CBUILD_SYS_H
#define CBUILD_SYS_H 1

// Define the OS names.
#define WINDOWS_OS_NAME "windows"
#define DARWIN_OS_NAME "darwin"
#define LINUX_OS_NAME "linux"
#define FREEBSD_OS_NAME "freebsd"
#define NETBSD_OS_NAME "netbsd"
#define OPENBSD_OS_NAME "openbsd"
#define UNKNOWN_OS_NAME ""

// Define the OS idents.
#define WINDOWS_OS_IDENT 5
#define DARWIN_OS_IDENT 4
#define LINUX_OS_IDENT 3
#define FREEBSD_OS_IDENT 2
#define NETBSD_OS_IDENT 1
#define OPENBSD_OS_IDENT 0
#define UNKNOWN_OS_IDENT -1

// Define the supported oses.
#define WINDOWS_OS {WINDOWS_OS_NAME, WINDOWS_OS_IDENT}
#define DARWIN_OS {DARWIN_OS_NAME, DARWIN_OS_IDENT}
#define LINUX_OS {LINUX_OS_NAME, LINUX_OS_IDENT}
#define FREEBSD_OS {FREEBSD_OS_NAME, FREEBSD_OS_IDENT}
#define NETBSD_OS {NETBSD_OS_NAME, NETBSD_OS_IDENT}
#define OPENBSD_OS {OPENBSD_OS_NAME, OPENBSD_OS_IDENT}
#define UNKNOWN_OS {UNKNOWN_OS_NAME, UNKNOWN_OS_IDENT}

// Define the ARCH names.
#define ARM_ARCH_NAME "arm"
#define AMD64_ARCH_NAME "amd64"
#define I386_ARCH_NAME "386"
#define UNKNOWN_ARCH_NAME ""

// Define the ARCH idents.
#define ARM_ARCH_IDENT 2
#define AMD64_ARCH_IDENT 1
#define I386_ARCH_IDENT 0
#define UNKNOWN_ARCH_IDENT -1

// Define the supported arches.
#define ARM_ARCH {ARM_ARCH_NAME, ARM_ARCH_IDENT}
#define AMD64_ARCH {AMD64_ARCH_NAME, AMD64_ARCH_IDENT}
#define I386_ARCH {I386_ARCH_NAME, I386_ARCH_IDENT}
#define UNKNOWN_ARCH {UNKNOWN_ARCH_NAME, UNKNOWN_ARCH_IDENT}

// Detect host os.
#if defined(_WIN32) || defined(_WIN64)
  #define HOST_OS WINDOWS_OS
#elif defined(__APPLE__) || defined(__MACH__)
  #define HOST_OS DARWIN_OS
#elif defined(__linux__)
  #define HOST_OS LINUX_OS
#elif defined(__FreeBSD__)
  #define HOST_OS FREEBSD_OS
#elif defined(__NetBSD__)
  #define HOST_OS NETBSD_OS
#elif defined(__OpenBSD__)
  #define HOST_OS OPENBSD_OS
#else
  #define HOST_OS UNKNOWN_OS
#endif

// Detect host arch.
#if defined(__arm__) || defined(_M_ARM) || defined(_M_ARMT)
  #define HOST_ARCH ARM_ARCH
#elif defined(__amd64__) || defined(_M_X64) || defined(_WIN64)
  #define HOST_ARCH AMD64_ARCH
#elif defined(__i386__) || defined(_M_IX86) || defined(_WIN32)
  #define HOST_ARCH I386_ARCH
#else
  #define HOST_ARCH UNKNOWN_ARCH
#endif

// platform_t defines the name and an ident number for a supported platform.
typedef struct platform {
  const char *name;
  int ident;
} platform_t;

// os_list is a list opossible oses.
extern platform_t os_list[];

// arch_list is a list of possibles arches.
extern platform_t arch_list[];

// dest_os retrieves the destination os.
platform_t dest_os(void);

// dest_arch retrieves the destination arch.
platform_t dest_arch(void);

#endif
