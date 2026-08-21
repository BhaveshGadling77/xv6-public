# xv6-public Source File → Primary Role Mapping

> This mapping is for the **MIT xv6-public (x86)** version, not xv6-riscv.
>
> The categories below describe the **primary role** of each source file. Some files naturally participate in more than one subsystem.

---

## 1. Bootloader

The bootloader is the code that runs before the xv6 kernel.

| File | Primary role |
|---|---|
| `bootasm.S` | First-stage boot code; switches the CPU into the environment needed to run the bootloader and jumps to `bootmain` |
| `bootmain.c` | Second-stage bootloader; reads the kernel from the disk image, loads the ELF kernel into memory, and jumps to the kernel |
| `elf.h` | ELF executable format structures/constants used by the bootloader and kernel |

### Boot flow

```text
BIOS
  ↓
bootasm.S
  ↓
bootmain.c
  ↓
reads kernel from xv6.img
  ↓
kernel
```

---

# 2. Kernel Entry and Initialization

These files start and initialize the xv6 kernel.

| File | Primary role |
|---|---|
| `entry.S` | Kernel entry point; performs early CPU setup before entering C code |
| `entryother.S` | Per-CPU startup code used when starting additional CPUs |
| `main.c` | Main kernel initialization sequence |
| `initcode.S` | Tiny first user-space program executed by the kernel |
| `init.c` | User-space `init` process; starts the shell |
| `defs.h` | Kernel-wide declarations/prototypes used by many kernel source files |

### Kernel startup

```text
bootmain.c
    ↓
entry.S
    ↓
main.c
    ↓
kernel initialization
    ↓
initcode.S
    ↓
init.c
    ↓
sh.c
```

---

# 3. Process Management

These files implement processes, process creation, scheduling, and process-related operations.

| File | Primary role |
|---|---|
| `proc.c` | Process table, allocation, creation, scheduling, sleep/wakeup, exit, wait, etc. |
| `proc.h` | `struct proc` and process-related definitions |
| `sysproc.c` | Process-related system calls such as `fork`, `exit`, `wait`, `kill`, `getpid`, `sbrk`, and `sleep` |
| `param.h` | Kernel configuration limits such as `NPROC`, `NCPU`, `NOFILE`, etc. |
| `user.h` | User-space declarations of system calls and library functions |

### Process relationship

```text
user program
    ↓
user.h
    ↓
system call
    ↓
sysproc.c
    ↓
proc.c
    ↓
proc.h
```

---

# 4. Virtual Memory / Memory Management

| File | Primary role |
|---|---|
| `vm.c` | Virtual memory implementation: page tables, address spaces, mapping, copying address spaces, kernel mappings |
| `kalloc.c` | Physical page allocator |
| `memlayout.h` | Memory layout constants and physical/virtual address definitions |
| `mmu.h` | x86 paging/MMU structures, page-table constants and macros |
| `x86.h` | x86 CPU instructions/register operations used throughout the kernel |

### Memory relationship

```text
vm.c
 ├── mmu.h
 ├── memlayout.h
 ├── x86.h
 └── kalloc.c

kalloc.c
 └── manages physical memory pages
```

---

# 5. File System

The xv6 file system is divided across several layers.

## 5.1 File-system implementation

| File | Primary role |
|---|---|
| `fs.c` | Main file-system implementation: inodes, directories, file allocation, read/write, block allocation |
| `fs.h` | File-system data structures and constants |
| `file.c` | Open-file abstraction and file descriptor operations |
| `file.h` | `struct file` and file-related definitions |
| `log.c` | File-system logging / journaling |
| `buf.h` | Buffer-cache buffer structure |
| `bio.c` | Buffer cache and block I/O |
| `ide.c` | IDE disk driver |
| `memide.c` | In-memory IDE disk used for testing |

### File-system stack

```text
User program
    ↓
system calls
    ↓
sysfile.c
    ↓
file.c
    ↓
fs.c
    ↓
bio.c
    ↓
ide.c / memide.c
    ↓
disk
```

---

# 6. File-Related System Calls

| File | Primary role |
|---|---|
| `sysfile.c` | File-related system calls such as `open`, `read`, `write`, `close`, `link`, `unlink`, `mkdir`, `mknod`, `fstat`, `dup`, `chdir`, etc. |
| `syscall.c` | System-call dispatcher; maps system-call numbers to kernel functions |
| `syscall.h` | System-call number definitions |
| `stat.h` | `struct stat` definition |
| `fcntl.h` | File-control/open flags such as `O_RDONLY`, `O_WRONLY`, `O_CREATE`, etc. |

---

# 7. System Call Mechanism

| File | Primary role |
|---|---|
| `syscall.c` | Kernel-side system-call dispatcher |
| `syscall.h` | System-call number constants |
| `sysproc.c` | Process-related system-call implementations |
| `sysfile.c` | File-related system-call implementations |
| `user.h` | User-space system-call declarations |
| `usys.S` | User-space assembly stubs that invoke system calls |
| `traps.h` | Trap and interrupt-related constants |

### System-call flow

```text
User program
    ↓
user.h
    ↓
usys.S
    ↓
int T_SYSCALL
    ↓
trap.c
    ↓
syscall.c
    ↓
sysproc.c / sysfile.c
    ↓
kernel implementation
```

---

# 8. Trap and Interrupt Handling

| File | Primary role |
|---|---|
| `trap.c` | Handles traps, exceptions, and interrupts in C |
| `trapasm.S` | Assembly entry code for traps/interrupts |
| `traps.h` | Trap numbers and interrupt constants |
| `vectors.S` | Generated interrupt-vector table |
| `vectors.pl` | Perl script that generates `vectors.S` |
| `x86.h` | x86 instructions and CPU register access |
| `picirq.c` | Programmable Interrupt Controller (PIC) setup |
| `ioapic.c` | I/O APIC interrupt controller |
| `lapic.c` | Local APIC implementation |

### Trap flow

```text
Hardware / CPU exception
        ↓
trapasm.S
        ↓
trap.c
        ↓
appropriate handler
```

### System-call trap

```text
User program
    ↓
int 0x40 / T_SYSCALL
    ↓
trapasm.S
    ↓
trap.c
    ↓
syscall.c
```

---

# 9. CPU / Multiprocessor Support

| File | Primary role |
|---|---|
| `mp.c` | Detects and initializes multiple processors |
| `mp.h` | Multiprocessor configuration structures/constants |
| `lapic.c` | Local APIC operations |
| `ioapic.c` | I/O APIC operations |
| `picirq.c` | Legacy PIC interrupt controller |
| `x86.h` | x86-specific CPU instructions and registers |
| `asm.h` | Assembly helper macros |
| `entryother.S` | Starts additional CPUs |

---

# 10. Synchronization / Locking

| File | Primary role |
|---|---|
| `spinlock.c` | Spinlock implementation |
| `spinlock.h` | Spinlock structure/declarations |
| `sleeplock.c` | Sleep-lock implementation |
| `sleeplock.h` | Sleep-lock structure/declarations |

### Locking hierarchy

```text
spinlock.h
    ↓
spinlock.c

sleeplock.h
    ↓
sleeplock.c
    ↓
spinlock.c
```

---

# 11. Device Drivers

## Disk

| File | Primary role |
|---|---|
| `ide.c` | IDE hard-disk driver |
| `memide.c` | Memory-backed IDE disk |

## Console / Keyboard / Serial

| File | Primary role |
|---|---|
| `console.c` | Console input/output and console device |
| `kbd.c` | Keyboard driver |
| `kbd.h` | Keyboard scan-code definitions |
| `uart.c` | Serial-port/UART driver |

## Pipes

| File | Primary role |
|---|---|
| `pipe.c` | Kernel pipe implementation |

---

# 12. Kernel Utility / String Functions

| File | Primary role |
|---|---|
| `string.c` | Kernel implementations of basic string/memory functions |
| `printf.c` | Kernel formatted output |
| `defs.h` | Declarations of many kernel functions |
| `types.h` | Basic kernel/user type definitions |

---

# 13. User-Space Library

These files provide functions used by xv6 user programs.

| File | Primary role |
|---|---|
| `ulib.c` | User-space library functions |
| `umalloc.c` | User-space dynamic memory allocator (`malloc`/`free`) |
| `printf.c` | Formatted output implementation used by user programs in the xv6-public build |
| `user.h` | User-space function/system-call declarations |
| `usys.S` | User-space system-call assembly stubs |
| `string.c` | Common string/memory functions |

> `printf.c`, `string.c`, and some headers are used in both kernel/user build contexts depending on the xv6-public Makefile rules.

---

# 14. User-Space Programs

These are programs that run **inside xv6**, not kernel components.

| File | Primary role |
|---|---|
| `cat.c` | User program that displays file contents |
| `echo.c` | User program that prints its arguments |
| `cp.c` | User program for copying files *(added/custom in your tree)* |
| `date.h` | Header for date-related functionality |
| `forktest.c` | User program for testing `fork()` |
| `grep.c` | User program for searching text |
| `head.c` | User program for displaying the beginning of files *(added/custom in your tree)* |
| `init.c` | First user-space process; starts the shell |
| `kill.c` | User program for sending signals/kill requests |
| `ln.c` | User program for creating hard links |
| `ls.c` | User program for listing directory contents |
| `mkdir.c` | User program for creating directories |
| `rm.c` | User program for removing files |
| `sh.c` | xv6 command shell |
| `stressfs.c` | File-system stress-test program |
| `wc.c` | User program that counts lines, words, and characters |
| `zombie.c` | User program demonstrating zombie processes |
| `tryhello.c` | Custom/test user program in your tree |

---

# 15. User-Space Testing

| File | Primary role |
|---|---|
| `usertests.c` | Large collection of xv6 user-space tests |
| `stressfs.c` | Stress-tests the file system |
| `forktest.c` | Tests process creation using `fork()` |
| `zombie.c` | Tests zombie-process behavior |

---

# 16. File-System Image Creation

| File | Primary role |
|---|---|
| `mkfs.c` | Host-side utility that creates `fs.img`/file-system images containing xv6 files |
| `fs.h` | File-system structures used by `mkfs.c` and the kernel |
| `param.h` | File-system/kernel configuration constants |

### Image creation

```text
User programs
     ↓
mkfs.c
     ↓
filesystem image
     ↓
xv6 kernel
```

---

# 17. Kernel Headers / Data Structures

| File | Primary role |
|---|---|
| `types.h` | Basic type definitions |
| `defs.h` | Kernel function declarations |
| `param.h` | Kernel limits/configuration |
| `proc.h` | Process structures |
| `file.h` | Open-file structures |
| `fs.h` | File-system structures |
| `buf.h` | Buffer-cache structures |
| `spinlock.h` | Spinlock definitions |
| `sleeplock.h` | Sleep-lock definitions |
| `stat.h` | File metadata structure |
| `memlayout.h` | Memory layout definitions |
| `mmu.h` | x86 MMU/page-table definitions |
| `elf.h` | ELF executable format definitions |
| `mp.h` | Multiprocessor structures |
| `kbd.h` | Keyboard definitions |
| `fcntl.h` | File-open flags |
| `syscall.h` | System-call numbers |
| `traps.h` | Trap/interrupt numbers |
| `user.h` | User-space API declarations |
| `asm.h` | Assembly helper macros |
| `x86.h` | x86 CPU-specific operations |

---

# 18. Important Files to Understand First

If your goal is to understand the xv6-public architecture, don't study all files randomly.

A good order is:

```text
1. types.h
2. defs.h
3. param.h
4. proc.h
5. memlayout.h
6. mmu.h
7. x86.h

        ↓

8. bootasm.S
9. bootmain.c

        ↓

10. entry.S
11. main.c

        ↓

12. proc.c
13. vm.c
14. kalloc.c

        ↓

15. trapasm.S
16. trap.c
17. syscall.c
18. sysproc.c
19. sysfile.c

        ↓

20. file.c
21. fs.c
22. bio.c
23. ide.c

        ↓

24. console.c
25. uart.c
26. kbd.c
27. pipe.c

        ↓

28. sh.c
29. init.c
30. user programs
31. usertests.c
```

---

# 19. Big-Picture xv6-public Architecture

```text
                         xv6-public
                             │
          ┌──────────────────┴──────────────────┐
          │                                     │
      BOOTLOADER                              KERNEL
          │                                     │
   ┌──────┴──────┐              ┌───────────────┼────────────────┐
   │             │              │               │                │
bootasm.S   bootmain.c      Process          Memory          Interrupts
                              │               │                │
                         proc.c/proc.h     vm.c/kalloc.c    trap.c
                              │               │                │
                         sysproc.c       mmu.h/memlayout.h   APIC/PIC
                              │
                         System Calls
                              │
                     ┌────────┴────────┐
                     │                 │
                 sysproc.c          sysfile.c
                                       │
                                  File System
                                       │
                              ┌────────┼────────┐
                              │        │        │
                            file.c    fs.c    pipe.c
                              │        │
                            bio.c      │
                              │        │
                           ide.c      log.c
```

---

# 20. User Space vs Kernel Space

One of the most important distinctions in xv6 is:

## Kernel files

```text
bio.c
console.c
exec.c
file.c
fs.c
ide.c
ioapic.c
kalloc.c
kbd.c
lapic.c
log.c
main.c
mp.c
pipe.c
proc.c
sleeplock.c
spinlock.c
string.c
syscall.c
sysfile.c
sysproc.c
trap.c
uart.c
vm.c
...
```

These become part of the **xv6 kernel**.

## User programs

```text
cat.c
echo.c
cp.c
forktest.c
grep.c
head.c
init.c
kill.c
ln.c
ls.c
mkdir.c
rm.c
sh.c
stressfs.c
wc.c
zombie.c
usertests.c
tryhello.c
...
```

These are compiled as **separate user-space executables** and placed into the xv6 file-system image.

---

# 21. Build-Time Tools vs xv6 Runtime Code

Some files are executed on your **Ubuntu/host machine**, not inside xv6.

| File | Runs where? | Purpose |
|---|---|---|
| `mkfs.c` | Host | Creates the xv6 file-system image |
| `vectors.pl` | Host | Generates `vectors.S` |
| `bootasm.S` | xv6/CPU | Bootloader |
| `bootmain.c` | xv6/CPU | Bootloader |
| `mkfs` | Host | Creates filesystem image |
| `gcc` | Host | Compiles xv6 source |
| `ld` | Host | Links kernel/boot components |
| `objcopy` | Host | Converts/extracts binary sections |
| `objdump` | Host | Produces assembly/debug information |
| `dd` | Host | Constructs `xv6.img` |

---

# 22. The Most Important Dependency Chain

If you want to understand how a command such as `ls` actually works:

```text
ls.c
 │
 ├── user.h
 │
 └── system-call API
        │
        ↓
      usys.S
        │
        ↓
    trap mechanism
        │
        ↓
      trap.c
        │
        ↓
    syscall.c
        │
        ↓
    sysfile.c
        │
        ↓
      file.c
        │
        ↓
       fs.c
        │
        ↓
      bio.c
        │
        ↓
      ide.c
        │
        ↓
       Disk
```

---

# 23. Process Creation Dependency Chain

For:

```c
fork();
```

the conceptual path is:

```text
User program
    ↓
user.h
    ↓
usys.S
    ↓
CPU trap
    ↓
trap.c
    ↓
syscall.c
    ↓
sysproc.c
    ↓
proc.c
    ↓
proc.h
    ↓
kalloc.c
    ↓
vm.c
```

---

# 24. `exec()` Dependency Chain

For:

```c
exec("program", argv);
```

```text
User program
    ↓
user.h
    ↓
usys.S
    ↓
trap.c
    ↓
syscall.c
    ↓
sysproc/syscall dispatch
    ↓
exec.c
    ↓
file system
    ↓
fs.c
    ↓
vm.c
```

`exec.c` loads an ELF executable into a new user address space.

---

# 25. Boot-to-Shell Complete Flow

```text
BIOS
 │
 ↓
bootasm.S
 │
 ↓
bootmain.c
 │
 │ reads kernel from xv6.img
 ↓
entry.S
 │
 ↓
main.c
 │
 ├── kinit()
 ├── tvinit()
 ├── binit()
 ├── fileinit()
 ├── iinit()
 ├── pinit()
 ├── picinit()
 ├── ioapicinit()
 ├── consoleinit()
 ├── ideinit()
 ├── startothers()
 └── userinit()
        │
        ↓
   initcode.S
        │
        ↓
      init.c
        │
        ↓
      sh.c
        │
        ↓
   User commands
```

---

# 26. One Important Correction About "Belongs To"

A file does not necessarily "belong" to exactly one component.

For example:

```text
x86.h
```

is used by several components:

```text
x86.h
 ├── trap.c
 ├── vm.c
 ├── proc.c
 ├── lapic.c
 ├── ioapic.c
 └── other kernel code
```

Likewise:

```text
defs.h
```

contains declarations used throughout the kernel.

Therefore, the table above gives the **primary role**, while the dependency diagrams show how files actually interact.

---

# 27. Quick Component → Files Cheat Sheet

| Component | Main files |
|---|---|
| Bootloader | `bootasm.S`, `bootmain.c`, `elf.h` |
| Kernel entry | `entry.S`, `main.c`, `entryother.S` |
| Process management | `proc.c`, `proc.h`, `sysproc.c` |
| Virtual memory | `vm.c`, `kalloc.c`, `mmu.h`, `memlayout.h` |
| System calls | `syscall.c`, `syscall.h`, `sysproc.c`, `sysfile.c`, `usys.S` |
| Trap handling | `trap.c`, `trapasm.S`, `traps.h`, `vectors.S` |
| Interrupts | `lapic.c`, `ioapic.c`, `picirq.c` |
| File abstraction | `file.c`, `file.h` |
| File system | `fs.c`, `fs.h`, `log.c` |
| Buffer cache | `bio.c`, `buf.h` |
| Disk | `ide.c`, `memide.c` |
| Pipes | `pipe.c` |
| Locks | `spinlock.c/.h`, `sleeplock.c/.h` |
| Console | `console.c` |
| Keyboard | `kbd.c`, `kbd.h` |
| Serial | `uart.c` |
| User library | `ulib.c`, `umalloc.c`, `user.h`, `usys.S` |
| Shell | `sh.c` |
| User commands | `cat.c`, `echo.c`, `ls.c`, `grep.c`, etc. |
| User testing | `usertests.c`, `forktest.c`, `stressfs.c`, `zombie.c` |
| FS image creation | `mkfs.c` |
| Build helpers | `vectors.pl`, Makefile |

---

# 28. How to Verify the Mapping Yourself

The mapping should not be learned only from a diagram. You can verify it directly from the source.

Useful commands:

```bash
grep -R "struct proc" .
grep -R "sys_open" .
grep -R "sys_fork" .
grep -R "bread(" .
grep -R "ideinit" .
grep -R "kalloc(" .
grep -R "setupkvm" .
grep -R "exec(" .
```

To see which files are compiled into the kernel:

```bash
grep -n "OBJS" Makefile
```

To see generated dependencies:

```bash
cat *.d
```

To see symbols in the final kernel:

```bash
objdump -t kernel
```

To see the final kernel disassembly:

```bash
objdump -S kernel
```

---

# 29. Key Idea

Think of xv6 as several layers rather than a flat list of files:

```text
                 USER PROGRAMS
                       │
                       ↓
              USER LIBRARY / API
                       │
                       ↓
                 SYSTEM CALLS
                       │
                       ↓
                KERNEL SERVICES
        ┌──────────────┼──────────────┐
        ↓              ↓              ↓
     Process         Memory       File System
        │              │              │
        ↓              ↓              ↓
      proc.c          vm.c           fs.c
        │              │              │
        └──────────────┼──────────────┘
                       ↓
                 DEVICE DRIVERS
                       │
                       ↓
                    HARDWARE
```

And before all of this:

```text
BIOS
 ↓
bootasm.S
 ↓
bootmain.c
 ↓
kernel
```

This is the mental model that makes the xv6-public source tree much easier to navigate.
