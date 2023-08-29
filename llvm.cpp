#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace
{
    struct NVMInstrumentPass : public FunctionPass
    {
        static char ID;
        NVMInstrumentPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override
        {
            LLVMContext &ctx = F.getContext();

            Function *writeNVMFn = F.getParent()->getFunction("writeNVM");

            if (!writeNVMFn)
            {
                errs() << "Error: function writeNVM() not found\n";
                return false;
            }

            if (!writeNVMFn->getReturnType()->isVoidTy() || writeNVMFn->arg_size() != 1 || !writeNVMFn->getArg(0)->getType()->isPointerTy())
            {
                errs() << "Error: function writeNVM() has incorrect signature\n";
                return false;
            }

            for (auto &BB : F)
            {
                for (auto &I : BB)
                {
                    if (auto *store = dyn_cast<StoreInst>(&I))
                    {

                        IRBuilder<> builder(store);
                        builder.CreateCall(writeNVMFn, store->getPointerOperand());
                    }
                }
            }

            return true;
        }
    };
}

char NVMInstrumentPass::ID = 0;
static llvm::RegisterPass<NVMInstrumentPass> X(
    "nvm-instrument", "NVM Instrumentation Pass",
    false /* Only looks at CFG */,
    false /* Analysis Pass */);
