# Problem 3

## Solution
* Discover that 'getty' is the program that runs before the login shell

* Edit getty source code at /usr/src/commands/getty/getty.c

* Recompile from /usr/src/commands/getty
  ```
  make clean && make && make install
  ````
  
* Reboot

## Diffs
```
$ diff -r /usr/src/commands/getty/getty.c /usr/src-orig/commands/getty/getty.c
91c91
<   static char *def_banner[] = { "%s Lab5 RELEASE %r VERSION %v  (%t)\n\n%n login: ", 0 };
---
>   static char *def_banner[] = { "%s  Release %r Version %v  (%t)\n\n%n login: ", 0 };
```
