```c
    gcc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -fno-stack-protector -fno-pie -no-pie -c main.c -o main.o
```
## Thumb Rules 
- The option starting from f-something-something will only for the *compilation* stage (-O2, -Werror, -W\*, -m32, )
- the options starting without f are mainly option for the *linking* stage(-static, etc are exceptions). 

| Flag                      | Meaning                                                                                                         |
| ------------------------- | --------------------------------------------------------------------------------------------------------------- |
| `-fno-pic`                | Disable **Position Independent Code** generation.                                                               |
| `-static`                 | Link statically — include required libraries directly in the executable instead of relying on shared libraries. |
| `-fno-builtin`            | Don't assume standard library functions are GCC built-ins.                                                      |
| `-fno-strict-aliasing`    | Disable optimizations based on the strict-aliasing rules.                                                       |
| `-O2`                     | Enable **level 2 compiler optimizations**.                                                                      |
| `-Wall`                   | Enable a broad set of common compiler warnings. **It does not mean literally every warning.**                   |
| `-MD`                     | Generate **dependency information**, usually in a `.d` file, for use by `make`.                                 |
| `-ggdb`                   | Generate debugging information optimized for **GDB**.                                                           |
| `-m32`                    | Generate **32-bit code**.                                                                                       |
| `-Werror`                 | Treat compiler **warnings as errors**.                                                                          |
| `-fno-omit-frame-pointer` | Keep the frame pointer in functions, useful for debugging/stack traces.                                         |
| `-fno-stack-protector`    | Disable GCC's stack-smashing protection.                                                                        |
| `-fno-pie`                | Don't generate **Position Independent Executable** code.                                                        |
| `-no-pie`                 | Don't produce a **PIE executable** during linking.                                                              |
| `-c`                      | **Compile only; do not link.** Produces an object file (`.o`).                                                  |
| `main.c`                  | Input C source file.                                                                                            |
| `-o main.o`               | Set the output filename to `main.o`.                                                                            |



