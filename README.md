# Welcome to msh-packages
MSH has no "normal" commands in it by default.
You must add them manually, before compiling.
This is be easier with packages, which contain one or more commands.
You can build your own packages or use these ones.

If you want to add these packages:
- clone or download the code of this repo next to the mshgit folder
- type `make command action=package data=../packages/< package name >;`
For a full guide, please visit the [wiki](https://github.com/Max2github/mshgit/wiki).

## std-essential
This package has all relevant commands in it.
Without it even printing is not possible. (exept you have another package for it)

## std-extended
This package has all non-relevant "standard" commands in it.

## list
This package contains the "list" commands, which can manage linked lists automatically.

## async
This packages enables multi-threading in msh. The stage is rather BETA and there may still be BUGS.
This package uses the pthread.h library, which may not exist everywhere and cause errors when cross-compiling.
If you want to use this package please set "MULTI_THREAD" in mshgit in "dependencies/std.h" to "1".
