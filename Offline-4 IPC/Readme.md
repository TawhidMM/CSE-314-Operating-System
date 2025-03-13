# IPC

This project demonstrates Inter-Process Communication (IPC) using threads in C++. 
It provides example implementations of threading and synchronization.

## Resource Materials
- [Assignment Spec](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-4%20IPC/Resources/IPC%20Offline%20Specification-v.2.pdf)
- [Thread Resources](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-4%20IPC/Resources/Thread_Resources)
- [Demo IPC Codes](https://github.com/TawhidMM/OS-CSE-314/tree/main/Offline-4%20IPC/Resources/Template_Ipc)

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
