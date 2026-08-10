# Steps

## Step 1: 
add the prototype of the sys call in *user.h*

## Step 2:
add the Macro in *usys.S* such as 
```c 
SYSCALL(<syscall name>)
```

## Step 3: 
write the code in some file for that purposes. 
maybe we can write code sysfile.c 

Whenever a system call is made the Interrupt handler is being called and then it goes to *vector.S* 
and there it goes to vector 64 after that it goes to *trapasm.S* 
from alltraps it goes to *trap.c* 
and then in syscall function call it calls the system calls using the array. 

you need to add [SYS_CALL] sys_hello, in the array of syscalls. 
so for this you need to define what is SYS_CALL in the syscall.h SYS_hello you can define it like or the count of next number defined in the syscall.h 

you need to add the extern <return type> sys_<sys call name>(args...);


## Step 4: 
Change the make file to add that in the UPARGS;
