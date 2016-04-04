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
#include "olive.cpp"
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
struct SymbolTable{
    char* name;
    int addrCount;
    SymbolTable* next;

    SymbolTable(){
        name = NULL;
        addrCount = -4;
        next = NULL;
    }

};
void addSymbolTable(SymbolTable* ST, const char* name){
    if(ST->name == NULL){
        ST->name = (char *) name;
        ST->addrCount = -4;
        return ;
    }
    
    SymbolTable* p = new SymbolTable;
    p->name = (char *)name;
    p->next = ST;
    p->addrCount = ST->addrCount - 4;// #define size_int 4
    ST = p;

}

struct TreeList{
    TreeList* next;
    Tree tptr;
    
    TreeList(){
        tptr = NULL;
        next = NULL;
    }
};
void addTree(TreeList* &TL, Tree t){
    if(TL->tptr == NULL){
        TL->tptr = t;
        return;
    }
    TreeList* p = new TreeList;
    p->tptr = t;
    p->next = TL;
    TL = p;
}


bool removeTree(TreeList* &TL, Tree t){
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        if(temp->tptr == t){
            for(TreeList* pre = TL; pre != temp; pre = pre->next){
                if(pre->next == temp){
                    pre->next = temp->next;
                    return true;
                }
            }
        }
    }
    return false;
}


bool mergeTree(TreeList* &TL, Tree root, Tree t){//merge two children
    bool tag = false;
    auto I = t->I;
    auto rootI = root->I;
    for(unsigned int i = 0; i < I->getNumOperands(); i++){
        auto operand = I->getOperand(i);
        if((Value *)operand == (Value*) rootI){
            tag = true;
            t->kids[i] = root;
            addTree(TL, t);
            removeTree(TL, root);
            return true;
        }
    }
    if(root->kids[0])
        tag |= mergeTree(TL, root->kids[0], t);
    if(root->kids[1] && !tag)
        tag |= mergeTree(TL, root->kids[1], t);
    return tag;
}

bool mergeTreeList(TreeList* &TL, Tree t){ // merge two children
    bool tag = false;
    for(auto temp = TL; temp != NULL; temp = temp->next){
        if(temp->tptr)
            tag |= mergeTree( TL, temp->tptr, t);        
    }
    return tag;
}

bool mergeTreeLeft(TreeList* &TL, Tree root, Tree t, Value* operand){//only merge 1st children
    bool tag = false;
    Instruction* rootI = root->I;
    errs() << " merge left?\n";
    if(operand == (Value*)rootI ){
        t->kids[0] = root;
        errs() << "yes merge left!\n";
        if(t->op < 500) // #define *** 99*
            addTree(TL, t);
        removeTree(TL, root);
        return true;
    }
    if(root->kids[0])
        tag |= mergeTreeLeft(TL, root->kids[0], t, operand);
    if(root->kids[1] && !tag)
        tag |= mergeTreeLeft(TL, root->kids[1], t, operand);
    return tag;
}

bool mergeTreeListLeft(TreeList* &TL, Tree t, Value* operand){ // only merge 1st children
    bool tag = false;
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        //if(temp->tptr)
            tag |= mergeTreeLeft( TL, temp->tptr, t, operand);       
    } 
    return tag;
}
void printTree(Tree t, int depth){
    errs() << depth << ' '<< t->op << ' ';
    if(t->op != 998 && t->op != 999)
        for(int i = 0; i < t->I->getNumOperands(); i++){
            errs() << t->I->getOperand(i)->getName();
            errs() << " ";
        }
    errs()<<"\n";
    if(t->kids[0])
        printTree(t->kids[0], depth + 1);
    if(t->kids[1])
        printTree(t->kids[1], depth + 1);
}

void printTreeList(TreeList* &TL){
    errs() << "this is the output\n";
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
            printTree(temp->tptr, 0);
        //errs() << temp->tptr->op <<'\n';
    } 
}

std::unique_ptr<Module> makeLLVMModule(char* inputfile, LLVMContext &Context) {
    SMDiagnostic Err;
    std::unique_ptr<Module> M;

    M = parseIRFile(inputfile, Err, Context);

    legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));

    //PM.run(*M);
    //FunctionListType &FunctionList = M.getFunctionList();
    TreeList* TL = new TreeList;
    SymbolTable* ST = new SymbolTable;
    for(auto &f:M->getFunctionList())
        for(auto &bb:f.getBasicBlockList())
            for( auto &I: bb.getInstList()) {
                errs() << '\n';
                I.print(errs());
                errs() << "\n" 
                       << "  opcode = " << I.getOpcode() << "\n"
                       << "  isBinary = " << I.isBinaryOp() << "\n"
                       ;
                
                errs() << "  instruction name:"<< I.getName()<< "\n";
                errs() << "  instruction value:" << &I <<"\n";
                errs() << "  Number of Operands = " << I.getNumOperands() << "\n" ;
                for(unsigned int i = 0; i < I.getNumOperands(); i++){
                    auto operand = I.getOperand(i);
                    errs() << "  operand value = " <<operand << " " 
                           << "  name = " << operand->getName() << "\n";
                    errs() << "  ";
                    operand->print(errs());
                    errs()<<'\n';
                }  
                if(I.getOpcode() != 29 && I.getOpcode() != 54) {// #define alloca 29
                    Tree t = tree(I.getOpcode(), 0, 0);
                    t->I = &I;
                    if(I.isBinaryOp() && I.hasName()){
                        Tree t_mov = tree(999, 0, 0); //#define MOV 999
                        Tree t_reg = tree(998, 0, 0); //#define REG 998
                        t->kids[1] = t_mov;
                        t_mov->kids[1] = t_reg;
                        bool temp1 = mergeTreeListLeft(TL, t, I.getOperand(0));
                        bool temp2 = mergeTreeListLeft(TL, t_mov, I.getOperand(1));
                        if(!temp1){ 
                            errs()<<"merge tree error!\n";
                            addTree(TL, t);
                        }
                    }
                    else if(!mergeTreeList(TL, t)){
                        addTree(TL, t);
                    }
                }
                else{
                    addSymbolTable(ST, I.getName().data());
                }
            }
    printTreeList(TL);
    //legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));
    //PM.run(*M);
    return M;
}
