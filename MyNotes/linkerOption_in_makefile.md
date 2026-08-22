## Linker Option given in Makefile.
*ld* on host machine is the linker 
## compilation generates the 
```sh
cat.c
  │
  │ compiler
  ▼
cat.o
```

To link this many object files we need to linker will link this files.

```sh 
cat.o
ulib.o
usys.o
printf.o
umalloc.o
        │
        │ ld
        ▼
      _cat
```
this is what is happening during the linking according to make file.



| Linker part   | Purpose                                                                                                                        |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `ld`          | Invokes the linker on Ubuntu/Host                                                                                              |
| `-m elf_i386` | Specifies the **32-bit Intel x86 ELF** linker format                                                                           |
| `-N`          | Makes text/data segments **not page-aligned** and makes the **text segment writable**                                          |
| `-e main`     | Specifies `main` as the **program entry point**                                                                                |
| `-Ttext 0`    | Places the **text/code section at address 0**                                                                                  |
| `-o _cat`     | Specifies `_cat` as the **output executable name**                                                                             |
| `cat.o`       | Object file containing the **compiled `cat` program**                                                                          |
| `ulib.o`      | Object file containing **xv6 user-space library functions**                                                                    |
| `usys.o`      | Object file containing **user-space system-call stubs**                                                                        |
| `printf.o`    | Object file containing **formatted output functions**, especially `printf`                                                     |
| `umalloc.o`   | Object file containing the **user-space memory allocator**; not really needed by `cat`, but included by the default build rule |
