#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/Pass.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include <memory>

using namespace llvm;
    
static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

static cl::opt<std::string>
OutputFilename("o", cl::desc("Output filename"), cl::value_desc("filename"));


std::unique_ptr<Module> makeLLVMModule(char *inputfile, LLVMContext &Context);

int main( int argc, char **argv) {

    LLVMContext &Context = getGlobalContext();
    std::unique_ptr<Module> M = makeLLVMModule(argv[1], Context);

//    verifyModule(*Mod, PrintMessageAction);

    return 0;

}

std::unique_ptr<Module> makeLLVMModule(char* inputfile, LLVMContext &Context) {
    SMDiagnostic Err;
    std::unique_ptr<Module> M;

    M = parseIRFile(inputfile, Err, Context);

    legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));
    for(auto f : M.getFunctionList()){

}
    //PM.run(*M);
    return M; 
}
