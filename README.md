# LLVM Pass for Tracking Memory Write Operations

This project contains source code files and an LLVM pass for tracking memory write operations in C++ programs.

## Files

- **sample.cpp:** An example source code file that contains NVM writes. This file can be used to test the LLVM pass.
- **llvm.cpp:** This file contains the implementation of the LLVM pass that instruments the original code to track memory write operations.
- **writeNVM.cpp:** This file contains the implementation of a runtime library function called writeNVM() that logs NVM write operations to a log file.
- **llvm_pass.sh:** This is a shell script that automates the process of running the LLVM pass on the original source code, linking it with the writeNVM() function, and running the resulting executable to log NVM write operations.
- **nvm_write.log:** This file is generated by the llvm_pass.sh script and contains the log of NVM write operations.

## How to Use

To use the LLVM pass to track memory write operations, follow these steps:

1. Ensure that LLVM is installed on your system.

2. Compile the LLVM pass by running the following command in the terminal:
   ```bash
   clang++ -shared -fPIC llvm.cpp -o libNVMInstrumentPass.so
   ```
3. Compile the source code to LLVM IR using Clang, by running the following command:

   ```bash
   clang++ -S -emit-llvm sample.cpp -o sample.ll
   ```
4. Run the LLVM pass on the LLVM IR generated in the previous step, to instrument the NVM write instructions:
   ```bash
   opt -load ./libNVMInstrumentPass.so -NVMInstrumentPass -S sample.ll -o sample.instrumented.ll
   ```
5. Compile the writeNVM() function to a shared object file, by running the following command:
   ```bash
   clang++ -shared -fPIC writeNVM.cpp -o libwriteNVM.so
   ```
6. Link the instrumented LLVM IR with the writeNVM() function using a runtime library, by running the following command:
   ```bash
   clang++ sample.instrumented.ll -L. -lwriteNVM -o a.out
   ```
7. Run the resulting executable to log NVM write operations:
   ```bash
   ./a.out > nvm_write.log
   ```

* Please ensure that you adjust the commands and file paths according to your environment and project structure.

* By following these instructions, you'll be able to utilize the provided LLVM pass to track memory write operations effectively in your C++ programs.
