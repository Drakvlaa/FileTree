# FileTree

## Overview

 FileTree is a lightweight C-based utility that recursively scans a specified directory to list all files and subdirectories. It navigates through each subdirectory, providing a comprehensive list of all files and their paths. This tool is useful for tasks such as directory analysis, file management, and creating inventories of file systems.

## Features

- **Recursive Scanning:** Scans the given directory and all its subdirectories.
- **File Listing:** Outputs a list of files with subdirectories
- **Efficiency:** Lightweight and efficient, ideal for large directory structures.
- **Cross-Platform:** Works on Linux, macOS, and Windows (via Cygwin or MinGW).

## Requirements

- GCC compiler (for compiling the code)

## Compilation

### Using GCC

To compile the program using GCC, open your terminal and navigate to the directory containing the source code. Run the following command:

```bash
gcc -o filetree main.c
```
After compiling the program, you can run it with following command:
```bash
filetree <Path>
```
* Replace <Path> with directory you want to scan or provide no arguments to scan current directory.
* You can also use the following options
    * `-h` or `--help` to display help instructions.
    * `-v` or `--version` to display version information.
## Example
```bash
filetree /home/user/weave
```
<img src="assets/filetreeExample.gif">
