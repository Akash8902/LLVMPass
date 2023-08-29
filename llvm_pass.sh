#!/bin/bash
# This script runs the LLVM pass to track memory write operations

# Step 1: Start with the original source code that contains NVM writes.
SRC_FILE="sample.cpp"

# Step 2: Write LLVM Pass
LLVM_PASS_FILE="llvm.cpp"
clang++ -shared -fPIC $LLVM_PASS_FILE -o libNVMInstrumentPass.so

# Step 3: Compile to LLVM IR
clang++ -S -emit-llvm $SRC_FILE -o sample.ll

# Step 4: Run LLVM Pass
opt -load ./libNVMInstrumentPass.so -NVMInstrumentPass -S sample.ll -o sample.instrumented.ll

# Step 5: WriteNVM Function
WRITE_NVM_FILE="writeNVM.cpp"
clang++ -shared -fPIC $WRITE_NVM_FILE -o libwriteNVM.so

# Step 6: Link with Runtime Library
clang++ sample.instrumented.ll -L. -lwriteNVM -o a.out

# Step 7: Track Write Operations
./a.out > nvm_write.log
