// Copyright 2014 Larz Conwell, see LICENSE for details.
#ifndef CBUILD_SYS_H
#define CBUILD_SYS_H 1

// Check if a file descriptor is associated with a terminal, on non
// Unix machines this should return -1.
int isaterm(int);

#endif
