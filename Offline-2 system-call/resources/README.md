## xv6 Insallation
- Download the [prerequisite tools](https://pdos.csail.mit.edu/6.828/2022/tools.html)

> [!NOTE]
> Skip If `prerequisite tools` is already downloaded in the machine.

- Clone the codebase
    ```bash
    git clone https://github.com/shuaibw/xv6-riscv --depth=1
    ```
## Compile and run xv6
Use the commands from inside `xv6-riscv` directory

- Run xv6
    ```bash
       make qemu
    ```
- Quit xv6/QEMU
    ```bash
       Press Ctrl+a then x
    ```
- Clean compilation
    ```bash
       make clean
    ```

## Patch Files

- Creating patch
    ```bash
      git add --all; 
      git diff HEAD > <patch file name>
    ```
- Applying patch
    ```bash
      git apply --whitespace=fix <patch file name>
    ```

## Cleanup git Directory
 ```bash
 git clean-fdx;
 git reset--hard
 ```

## Resources
- [xv6 book](https://github.com/TawhidMM/OS-CSE-314/blob/main/Offline-2%20system-call/resources/book-riscv-rev1.pdf)

- [Explanation of source code](https://www.youtube.com/watch?v=fWUJKH0RNFE&list=PLbtzT1TYeoMhTPzyTZboW_j7TPAnjv9XB)
 