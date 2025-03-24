# IPC

## Overview  

[Assignment Spec](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-4%20IPC/Resources/IPC%20Offline%20Specification-v.2.pdf)

This assignment simulates the movement of visitors in a **museum** using **synchronization and inter-process communication (IPC) mechanisms**. 

A group of **N friends** visits a museum, each purchasing a **standard ticket**, while **M other visitors** have **premium tickets**. The goal is to manage their movements efficiently using synchronization mechanisms.  



## Tasks  

### Task 1: Visitor Movements with Synchronization  
- Implements visitor movements using **locking mechanisms** to prevent race conditions.  
- Prints every move of each visitor along with **timing information**.  

### Task 2: Ensuring Visitors Enter Gallery 2  
- Ensures that every visitor **must enter Gallery 2** at some point during their visit.  
- Prints every visitor’s movement along with **timing information**.  

### Task 3: Implementing the Reader-Writer Problem  
- Models visitor entry and movement using the **reader-writer problem construct**.  
- Ensures proper synchronization while allowing concurrent access.  
- Prints movement details with **timing information**.  


## How to Run the Program

The program must be compiled and run in **Linux** or **WSL**.  
You can compile the program using either [Make](#using-make) or [Manual Compilation](#manual-compilation).

### Using Make

- **Compile and Run the program**
    ```bash
    make run
    ```
- **Clean up the compiled binary**
    ```bash
    make clean
    ```

### Manual Compilation

- **Compile the program**
    ```bash
    g++ -o ipc ipc.cpp -pthread
    ```
- **Run the program**
    ```bash
    ./ipc
    ```

## Resource Materials
- [Thread Resources](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-4%20IPC/Resources/Thread_Resources)
- [Demo IPC Codes](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-4%20IPC/Resources/Template_Ipc)
