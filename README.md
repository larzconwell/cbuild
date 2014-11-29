# cbuild
cbuild is a build tool to easily build cross platform C code. Read the man page for details `man cbuild`.

## Install
```
PREFIX=/usr/local sudo make install
```

## Current Status
- [x] Host OS/ARCH detection
- [x] List of files to compile for dest OS/ARCH
- [ ] Gather env flags(e.x. `CFLAGS`, `CXXFLAGS`, `CPPFLAGS`, `LDFLAGS`, `LDLIBS`)
- [ ] Detect compiler
- [ ] Build archiver/Use host archiver
- [ ] Figure out cross compiling
- [ ] Build the compiler/linker steps
- [ ] Windows support
- [ ] Bootstrap code

## Workflow
Below is the overview of the workflow to implement the functionality.

```
- [x] Get dest os using OS env
- [x] Get dest arch using ARCH env
- [x] Compile only flag if -c given
- [x] Default output file name
- [x] Set output file if -o given
- [x] Loop argc
  - [x] If extension add to arg list
  - [x] Else parse name with OS/ARCH and get files to be compiled for dest, adding to arg list
- [ ] Loop arg list
  - [ ] If extension not in source ext list, add to final list and skip
  - [ ] Compile the path, and add the resulting file to final list
- [ ] If linking, link paths in final list writing to output file
- [ ] Else create archive of all paths in final list and write to output file
- [ ] Cleanup files in final list
```


## License
cbuild is MIT licensed, see [here](https://raw.githubusercontent.com/larzconwell/cbuild/master/LICENSE).
