# Problem 2

## Solution
* Use grep to find which source file prints the prompt

    From /usr/src/sys/arch/i386/stand:
    ```
    grep -r ".*printf.*> .*" .
    ```

* Modify ./lib/menuutils.c where string is printed

* Recompile boot program code from same directory as above
    ```
    make && make install
    ```
    
* Take a hint from the lab and search for 'boot_monitor'
    1. Find this referenced in an 'updateboot.sh' script
    2. Run this program

## Diffs
```
$ diff -r /usr/src /usr/src-orig
diff -r /usr/src/sys/arch/i386/stand/lib/menuutils.c /usr/src-orig/sys/arch/i386/stand/lib/menuutils.c
73c73
<           printf(">> ");
---
>           printf("> ");
```    
