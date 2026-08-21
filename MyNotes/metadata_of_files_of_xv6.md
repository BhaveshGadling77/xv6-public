### this is temporary 

```sh
xv6-public
│
├── 01. Bootloader
│   ├── bootasm.S
│   └── bootmain.c
│
├── 02. Kernel Startup
│   ├── entry.S
│   └── main.c
│
├── 03. Process Management
│   ├── proc.c
│   ├── proc.h
│   └── swtch.S
│
├── 04. System Calls
│   ├── syscall.c
│   ├── syscall.h
│   ├── sysproc.c
│   ├── sysfile.c
│   ├── usys.S
│   └── user.h
│
├── 05. Memory Management
│   ├── kalloc.c
│   ├── vm.c
│   ├── vm.h
│   └── mmu.h
│
├── 06. Traps & Interrupts
│   ├── trap.c
│   ├── trapasm.S
│   ├── vectors.S
│   └── vectors.pl
│
├── 07. File System
│   ├── fs.c
│   ├── fs.h
│   ├── file.c
│   ├── file.h
│   ├── sysfile.c
│   ├── bio.c
│   ├── log.c
│   └── log.h
│
├── 08. Process Communication
│   └── pipe.c
│
├── 09. Device Drivers
│   ├── console.c
│   ├── uart.c
│   ├── kbd.c
│   ├── ide.c
│   └── memide.c
│
├── 10. Synchronization
│   ├── spinlock.c
│   ├── spinlock.h
│   ├── sleeplock.c
│   └── sleeplock.h
│
├── 11. CPU / Hardware
│   ├── x86.h
│   ├── mp.c
│   ├── mp.h
│   ├── lapic.c
│   ├── lapic.h
│   ├── ioapic.c
│   └── picirq.c
│
└── 12. Common / User / Build
    ├── defs.h
    ├── types.h
    ├── param.h
    ├── string.c
    ├── ulib.c
    ├── umalloc.c
    ├── user programs
    ├── mkfs.c
    └── Makefile
```


## 1. Bootloader 
what we have learned so far. 

