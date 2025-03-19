# xv6 - Threading & Synchronization

[Assignment Spec]()

This assignment implements-

- support for **threads** in xv6. 
- a user-level **thread library** consisting of some system calls related to threads. 
- two POSIX-like **syncronization primitives** in xv6 to solve some syncronization errors.

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

- [xv6 installation](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_installation.md)