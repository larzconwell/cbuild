// Copyright 2014 Larz Conwell, see LICENSE for details.
#ifndef CBUILD_DETECT_H
#define CBUILD_DETECT_H 1

// Detect current OS.
#if defined(_WIN32) || defined(_WIN64)
  #define CUR_OS "windows"
  #define CUR_OS_NUM 5
#elif defined(__APPLE__) || defined(__MACH__)
  #define CUR_OS "darwin"
  #define CUR_OS_NUM 3
#elif defined(__linux__)
  #define CUR_OS "linux"
  #define CUR_OS_NUM 4
#elif defined(__FreeBSD__)
  #define CUR_OS "freebsd"
  #define CUR_OS_NUM 0
#elif defined(__NetBSD__)
  #define CUR_OS "netbsd"
  #define CUR_OS_NUM 2
#elif defined(__OpenBSD__)
  #define CUR_OS "openbsd"
  #define CUR_OS_NUM 1
#else
  #define CUR_OS ""
  #define CUR_OS_NUM -1
#endif

// Detect current ARCH.
#if defined(__arm__) || defined(_M_ARM) || defined(_M_ARMT)
  #define CUR_ARCH "arm"
  #define CUR_ARCH_NUM 2
#elif defined(__amd64__) || defined(_M_X64) || defined(_WIN64)
  #define CUR_ARCH "amd64"
  #define CUR_ARCH_NUM 1
#elif defined(__i386__) || defined(_M_IX86) || defined(_WIN32)
  #define CUR_ARCH "386"
  #define CUR_ARCH_NUM 0
#else
  #define CUR_ARCH ""
  #define CUR_ARCH_NUM -1
#endif

#endif
