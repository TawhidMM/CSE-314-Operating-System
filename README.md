# OS Assignments Repository  

## Overview  
This repository contains five assignments focused on operating systems concepts, including shell scripting, system calls, scheduling, threading, and synchronization in xv6, along with a concurrency problem modeled as a reader-writer problem. Each assignment is implemented in its respective folder.  

## Assignments  

### [Assignment 1: Shell Script](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-1%20shell-script)  
Implements an **autograder** to evaluate student assignments submitted as ZIP files. The autograder processes submissions, runs the code, compares outputs, and generates reports while organizing files systematically.  

### [Assignment 2: xv6 - System Calls](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-2%20system-call)  
Extends xv6 by implementing new system calls:  
- **Trace**: Enables syscall tracing for a specific system call.  
- **Process Info**: Returns aggregated information about running processes.  
- **!! Command**: Implements the `!!` command from Bash in xv6.  

### [Assignment 3: xv6 - Scheduling](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-3%20Scheduling)  
Implements an **MLFQ (Multilevel Feedback Queue) scheduling** algorithm with an aging mechanism. It features two queues—one using **lottery scheduling** and the other following a **Round-Robin** approach.  

### [Assignment 4: Inter Process Communication](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-4%20IPC)  
Simulates visitor movements in a **museum** using **synchronization and locking mechanisms**.  
- **Task 1**: Implements visitor movements with proper synchronization and prints movements with timing info.  
- **Task 2**: Ensures all visitors enter **Gallery 2**, enforcing movement constraints.  
- **Task 3**: Models visitor movement using the **reader-writer problem** construct with timing details.  

### [Assignment 5: xv6 - Threading & Synchronization](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-5%20Threads4)  
Adds **thread support** in xv6, along with a **user-level thread library**. It also implements **POSIX-like synchronization primitives** to handle concurrency issues.  
