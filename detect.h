/*
 * detect.h
 *
 * Copyright 2014 Larz Conwell, see LICENSE for details.
 */
#ifndef CBUILD_DETECT_H
#define CBUILD_DETECT_H 1

// Detect current OS.
#if defined(_WIN32) || defined(_WIN64)
  #define CUR_OS "windows"
#elif defined(__APPLE__) || defined(__MACH__)
  #define CUR_OS "darwin"
#elif defined(__linux__)
  #define CUR_OS "linux"
#elif defined(__FreeBSD__)
  #define CUR_OS "freebsd"
#elif defined(__NetBSD__)
  #define CUR_OS "netbsd"
#elif defined(__OpenBSD__)
  #define CUR_OS "openbsd"
#else
  #define CUR_OS ""
#endif

// Detect current ARCH.
#if defined(__arm__) || defined(_M_ARM) || defined(_M_ARMT)
  #define CUR_ARCH "arm"
#elif defined(__amd64__) || defined(_M_X64) || defined(_WIN64)
  #define CUR_ARCH "amd64"
#elif defined(__i386__) || defined(_M_IX86) || defined(_WIN32)
  #define CUR_ARCH "386"
#else
  #define CUR_ARCH ""
#endif

#endif
