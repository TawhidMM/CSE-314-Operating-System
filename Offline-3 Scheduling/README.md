# xv6 Scheduling
[Assignment Spec](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-3%20Scheduling/CSE314-scheduling-Jan2024.pdf)


This assignment implements an [MLFQ (Multilevel Feedback Queue)](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf) scheduling algorithm with the aging mechanism.
There are two queues– one with [lottery scheduling](https://en.wikipedia.org/wiki/Lottery_scheduling) and the other working in a Round-Robin fashion.

**Processes are scheduled according to the following rules:**
- A newprocess is always placed at the topmost queue (queue 0).
- The scheduler searches the queues starting from the top most one for scheduling processes.
 
- When a process is assigned to the CPU,
    - If it is completed within the time limit of its queue, it exits as usual.
    - If it consumes all the time slice allocated for that queue, it is preempted and inserted at the next lower level  queue.
    - If it voluntarily gives up the control of the CPU before consuming all its time slices (due to waiting for I/O, or sleeping), it is moved to the immediate higher level queue.
- Processes that have been waiting too long in the lower-priority `queue 1` will be promoted to the
 higher priority `queue 0` to reduce the risk of being starved.

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

- [spec declaration video](https://www.youtube.com/watch?v=gVopuaywmIU)

- [xv6 installation](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/xv6_installation.md)