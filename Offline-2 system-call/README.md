# xv6- System Call
[Assignment Spec](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/Offline-02-system-call.pdf)

This assignment implements new system calls to xv6.

Three tasks are implemented:
- **Task 1: Trace**

    Implemention a new system call `trace` that controls program tracing. It takes one argument, an
    integer `syscall number` which denotes the system call number to trace for a user program. 
    
    For example, to
    trace the `fork` system call, a user program calls `trace(SYS fork)`, where `SYS fork` is the syscall number of `fork`
    from `kernel/syscall.h`.

- **Task 2: Reporting process related information**

    Addition a system call, `info`,that returns the aggregated information of currently running processes as struct
 of `procInfo`.
    ```c
    struct procInfo {
        int activeProcess;  // # of processes in RUNNABLE and RUNNING state
        int totalProcess;   // # of total possible processes
        int memsize;        // in bytes; summation of all active process
        int totalMemSize;   // in bytes; all available physical Memory
    };
    ```

- **Task 3: !!**

    Implementation `!!` command of **bash** in xv6.

## How to Run ??

1. [clone xv6 codebase](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_installation.md).
2. download the `2005036.patch` file and put outside `xv6-riscv`.
3. apply the patch
    ```bash
      git apply --whitespace=fix ../2005036.patch
    ```
4. run qemu (from inside `xv6-riscv`)
    ```bash
      make qemu
    ```

## Resources

- [adding a user program](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_%20Adding%20a%20user%20program.pdf)

- [adding a system call](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_%20Adding%20a%20system%20call.pdf)

- [xv6 installation](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_installation.md)