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
#include "olive.h"
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

    //PM.run(*M);
    //FunctionListType &FunctionList = M.getFunctionList();

    for(auto &f:M->getFunctionList())
        for(auto &bb:f.getBasicBlockList())
            for( auto &I: bb.getInstList()) {
                I.print(errs());
                errs() << "\n" 
                       //<< "  opcode = " << I.getOpcode() << "\n"
                       //<< "  isAdd = " << I.isBinaryOp() << "\n"
                       ;
                
                errs() << "Number of Operands = " << I.getNumOperands() << "\n" ;
                for(unsigned int i = 0; i < I.getNumOperands(); i++){
                    auto operand = I.getOperand(i);
                    /*if(operand->getValueName())
                    errs() << "Valuename = " <<operand->getValueName()->getValue()->getName() << "\n" 
                           << "name = " << operand->getName() << "\n";*/
                    errs() <<"!!!!!!!!!!!" <<  i << " ";
                    operand->print(errs());
                }
                errs() << "\n\n"; 
            }

    //legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));
    //PM.run(*M);
    return M;
}
