## xv6 Insallation
- Download the [prerequisite tools](https://pdos.csail.mit.edu/6.828/2022/tools.html)

- Clone the codebase
    ```bash
    git clone https://github.com/shuaibw/xv6-riscv --depth=1
    ```
## Compile and run xv6
Use the commands from inside `xv6-riscv` directory

- run xv6
    ```bash
       make qemu
    ```
- quit xv6/qemu
    ```bash
       Press Ctrl+a then x
    ```
- clean compilation
    ```bash
       make clean
    ```

## Patch Files

- creating patch
    ```bash
      git add --all; 
      git diff HEAD > <patch file name>
    ```
- appling patch
    ```bash
      git apply --whitespace=fix <patch file name>
    ```

## Cleanup git Directory
 ```bash
 git clean-fdx;
 git reset--hard
 ```

## Resources
- [xv6 book]()

- [Explanation of source code](https://www.youtube.com/watch?v=fWUJKH0RNFE&list=PLbtzT1TYeoMhTPzyTZboW_j7TPAnjv9XB)
 