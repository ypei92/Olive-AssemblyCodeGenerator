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
#include "llvm/Analysis/Interval.h"
#include "llvm/IR/User.h"
#include "llvm/Pass.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/InstIterator.h"
#include "llc-olive-grammar.h"
#include "llc-olive-grammar_cpp.h"
#include <memory>
#include <list>
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


//typedef std::map<Instruction *, int> InstMap;
struct InstMap{
    Instruction* I;
    int N;
    InstMap(){
        I = NULL;
        N = 0;
    }
};

struct LiveRange{
    Value *v;
    int start;
    int end;
    LiveRange(){
        v = NULL;
        start = 0;
        end = 0;
    }
};
struct LiveTable{
    BasicBlock * bb;
    LiveRange* LR;
    int NumVar;
    int bbstart;
    LiveTable(){
        bb = NULL;
        LR = NULL;
        NumVar = 0;
        bbstart = 0;
    }
};
struct SymbolTable{
    Value* v;
    int addrCount;
    SymbolTable* next;

    SymbolTable(){
        v = NULL;
        addrCount = 0;
        next = NULL;
    }

};
void addSymbolTable(SymbolTable* &ST, Value* value){
    int temp;
    if(!value->getType()->getPointerElementType()->isPointerTy())
        temp = (value->getType()->getPointerElementType()->getIntegerBitWidth())/8;
    else 
        temp = 8; //#define working on 64bit machinev
    if(ST->v == NULL){
        ST->v = value;
        errs() << "value:" <<  temp << '\n';//value->getType()->getTypeAllocSize() << '\n';//(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';
        ST->addrCount = -temp;
        return ;
    }
       
    SymbolTable* p = new SymbolTable;
    p->v = value;
    p->next = ST;
     
    errs() << "value:" << temp << '\n';
        //(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';//value->getType()->getPrimitiveSizeInBits() << '\n';//value->getType()->getTypeAllocSize() << '\n';//(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';
    if(ST->addrCount > 0) 
        p->addrCount = 0 - temp;// #define size_int 4
    else
        p->addrCount = ST->addrCount - temp;// #define size_int 4
    ST = p;
}
void addArg2SymbolTable(SymbolTable* &ST, Value* value, int n){
    if(ST->v == NULL){
        ST->v = value;
        ST->addrCount = n;
        return ;
    }
       
    SymbolTable* p = new SymbolTable;
    p->v = value;
    p->next = ST;
    errs() << "value:" << n << '\n';
    p->addrCount = n;// #define size_int 4
    ST = p;
}
bool findSymbolTable(SymbolTable *ST, Value* val, Tree t){
    for(SymbolTable* temp = ST; temp != NULL; temp = temp->next){
        if(temp->v == val){
            t->val = temp->addrCount;
            if(t->val > 0 && t->val <= 6)
                t->op = 998;//#define ARG 998
            return true;
        }
    }
    return false;
}
struct TreeList{
    TreeList* next;
    Tree tptr;
    
    TreeList(){
        tptr = NULL;
        next = NULL;
    }
};
//typedef TreeList std::list<Tree>;
void addTree(TreeList* &TL, Tree t){
    if(TL->tptr == NULL){
        TL->tptr = t;
        return;
    }
    TreeList* temp;
    for(temp = TL; temp != NULL; temp = temp->next){
        if(temp->next == NULL)
            break;
    }
    TreeList* p = new TreeList;
    p->tptr = t;
    p->next = NULL;
    temp->next = p;
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
        if(temp->tptr && !tag)
            tag |= mergeTree( TL, temp->tptr, t);        
    }
    return tag;
}

bool mergeTreeLeft(TreeList* &TL, Tree root, Tree t, Value* operand){//only merge 1st children
    bool tag = false;
    Instruction* rootI = root->I;
    if(operand == (Value*)rootI ){
        t->kids[0] = root;
        errs() << "yes merge left!" << operand->getName() << root->I->getOpcode() << '\n';
        removeTree(TL, root);
        return true;
    }
    if(root->kids[0])
        tag |= mergeTreeLeft(TL, root->kids[0], t, operand);
    if(root->kids[1] && !tag)
        tag |= mergeTreeLeft(TL, root->kids[1], t, operand);
    return tag;
}

bool mergeTreeListLeft(TreeList* &TL, Value* operand, Tree t){ // only merge 1st children
    bool tag = false;
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        if(!tag)
            tag |= mergeTreeLeft( TL, temp->tptr, t, operand);       
    }
    errs() << "yes merge list left!" << operand->getName() << '\n';
    return tag;
}

bool mergeTreeRight(TreeList* &TL, Tree root, Tree t, Value* operand){//only merge 2nd children
    bool tag = false;
    Instruction* rootI = root->I;
    if(operand == (Value*)rootI ){
        t->kids[1] = root;
        errs() << "yes merge right!" << operand->getName() << '\n';
        removeTree(TL, root);
        return true;
    }
    if(root->kids[0])
        tag |= mergeTreeRight(TL, root->kids[0], t, operand);
    if(root->kids[1] && !tag)
        tag |= mergeTreeRight(TL, root->kids[1], t, operand);
    return tag;
}

bool mergeTreeListRight(TreeList* &TL, Value* operand, Tree t){ // only merge 2nd children
    bool tag = false;
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        if(!tag)
            tag |= mergeTreeRight( TL, temp->tptr, t, operand);       
    } 
    return tag;
}

void printTree(Tree t, int depth){
    errs() << depth << ' '<< t->op << ' ';
    if(t->op < 500){
        if(!(t->op == 30 && !(t->I))){
            errs() << t->I->getOpcodeName() << ' ';
            for(int i = 0; i < t->I->getNumOperands(); i++){
                errs() << "operand" << i << ":" <<t->I->getOperand(i)->getName();
                errs() << " ";
            }
        }
    }
    else if(t->op == 996 || t->op == 999)
        errs() << t->val;
    errs() << '\n';
    if(t->kids[0])
        printTree(t->kids[0], depth + 1);
    if(t->kids[1])
        printTree(t->kids[1], depth + 1);
}

void printLR(LiveRange* LR, int n){
    for(int i = 0; i < n; i++){
        LR[i].v->print(errs());
        errs() << "\n";
        errs() << "var "<< i << ": "<< LR[i].start << " "<< LR[i].end<< '\n';
    }
}

void printTreeList(TreeList* TL, LiveRange* LR, int n){
    errs() << "this is the output\n";
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        //printTree(temp->tptr, 0);
        //errs() << temp->tptr->op <<'\n';
        //gen(temp->tptr);
        errs()<<"\n";
    }
    printLR(LR, n);
}

bool LiveUnion(BasicBlock* bb, BasicBlock* succ, LiveTable* LT, int NumBB){
    LiveRange* bb_LR = NULL;
    LiveRange* succ_LR = NULL;
    bool changed  = false;
    int bb_ID = 0, succ_ID = 0;
    for(int i = 0; i < NumBB; i++){
        if(bb == LT[i].bb){
            bb_LR = LT[i].LR;
            bb_ID = i;
        }
        if(succ == LT[i].bb){
            succ_LR = LT[i].LR;
            succ_ID = i;
        }
    }    
    for(int i = 0; i < LT[0].NumVar; i++){
        if(succ_LR[i].end > bb_LR[i].end){
            bb_LR[i].end = succ_LR[i].end;
            changed = true;
        }
    }
    return changed;
    
}
bool addRange(Value* operand, Instruction * I, LiveTable* LT){
    LiveRange* LR = LT->LR;
    int NumVar = LT->NumVar;
    bool changed = false;
    int opd_ID = 0, I_ID = 0;
    for(int i = 0; i < NumVar; i++){
        if(LR[i].v == operand){
            opd_ID = i + 1;
        }
        if(LR[i].v == (Value*)I){
            //LR[i].v->print(errs());
            //errs() << '\n';
            //I->print(errs());
            //errs() << '\n';
            I_ID = i + 1;
        }
    }
    errs() << opd_ID << " " << I_ID << '\n';
    if(LR[opd_ID].end < I_ID && opd_ID != 0){
        LR[opd_ID].end = I_ID;
        changed = true;
    }
    return changed;


}
/*bool setStart(Instruction* I, LiveTable* LT){
    LiveRange* LR = LT->LR;
    int NumVar = LT->NumVar;
    bool changed = false;
    int I_ID = 0;
    for(int i = 0; i < NumVar; i++){
        if(LR[i].v == (Value*)I){
            I_ID = i;
        }
    }
    if(LR[I_ID].start < I_ID && I_ID != 0){
        LR[I_ID].start = I_ID;
        changed = true;
    }
    return changed;
}*/
std::unique_ptr<Module> makeLLVMModule(char* inputfile, LLVMContext &Context) {
    SMDiagnostic Err;
    std::unique_ptr<Module> M;

    M = parseIRFile(inputfile, Err, Context);

    legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));

    //PM.run(*M);
    //FunctionListType &FunctionList = M.getFunctionList();
    for(auto &f:M->getFunctionList()){
        
        TreeList* TL = new TreeList;
        SymbolTable* ST = new SymbolTable;
        for(auto &arg: f.getArgumentList()){
            if(arg.getArgNo() < 6)
                addArg2SymbolTable(ST,(Value* ) &arg, arg.getArgNo() + 1);
            else
                addArg2SymbolTable(ST,(Value* ) &arg, 8* (arg.getArgNo() - 5));
        }
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
                if(I.getOpcode() != 29) {// #define alloca 29
                    Tree t = tree(I.getOpcode(), 0, 0);
                    t->I = &I;
                    addTree(TL ,t);
                    if(I.isBinaryOp() && I.hasName()){
                        Tree t_mov = tree(30, 0, 0); //#define LOAD 30
                        t->kids[1] = t_mov;
                        bool temp1 = mergeTreeListLeft(TL, I.getOperand(0), t);
                        bool temp2 = mergeTreeListLeft(TL, I.getOperand(1), t_mov);
                        if(!temp1){ 
                            errs()<<"merge tree error!\n";
                            exit(1);//addTree(TL, t);
                        }
                    }
                    else if(I.getOpcode() == 31 ){//#define store 31
                        Tree offset_r = tree(999, 0, 0);//#define OFFSET 999
                        t->kids[1] = offset_r;
                        if(t->I->getOperand(0)->getType()->isIntegerTy()){
                            errs() << " store an integer\n";
                            errs() << *(t->I->getOperand(0)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
                            Tree imm_l = tree(999, 0, 0);//#define OFFSET 999
                            t->kids[0] = imm_l;
                            errs() << "store left\n";
                            if(CI) {
                                errs() << "CI exists!\n";
                                errs() << CI->getValue() << '\n';
                                imm_l->val = CI->getSExtValue();
                                imm_l->op = 996;
                            }
                            else {
                                if(TL->tptr == NULL){
                                    if(!findSymbolTable(ST, I.getOperand(0), imm_l))
                                        errs() << "unable to recognize left kids of store!\n";
                                }
                                else if(!mergeTreeListLeft(TL, I.getOperand(0), t)){
                                    if(!findSymbolTable(ST, I.getOperand(0), imm_l))
                                        errs() << " unable to recognize left kids of store!\n";
                                }
                            }

                        }
                        else if(I.getOperand(0)->getType()->isPointerTy()){
                            errs() << "store from a pointer!\n";
                            Tree offset = tree(999, 0, 0);
                            t->kids[0] = offset;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }
                        //printTreeList(TL);   
                        if(!(mergeTreeListRight(TL, I.getOperand(1), t)||findSymbolTable(ST, I.getOperand(1),offset_r))){
                            errs() << "find symboltable error!\n";
                            exit(1);
                        }
                    }
                    else if(I.getOpcode() == 30){//#define load 30
                        Tree offset = tree(999, 0, 0);// #define OFFSET 999
                        t->kids[0] = offset;
                        if(I.getOperand(0)->getType()->getPointerElementType()->isPointerTy()){
                            errs() << "load from a pointer!\n";
                            findSymbolTable(ST, I.getOperand(0), t);
                        }
                        else if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0),offset))){
                            errs() << "merge tree list & find symboltable error!\n";
                            exit(1);
                        }

                    }
                    else if(I.getOpcode() == 54){ // #define call 54
                        Tree tmp = t;
                        if(I.getNumOperands() > 1){
                            t->kids[0] = tree(997, 0, 0);// #define ARGLIST 997
                            tmp = t->kids[0];
                            t->val = I.getNumOperands() - 1;
                        }
                        for(int i = I.getNumOperands() - 2; i >= 0; i--){
                            Tree t_arglist = tree(997, 0, 0); // #define ARGLIST 997                            
                            tmp->kids[1] = t_arglist;
                            mergeTreeListLeft(TL, I.getOperand(i), tmp);
                            if(i == 0){
                                t_arglist->op = 995;//#define ARGEND 995
                            }
                            tmp = t_arglist;
                        }
                    
                    
                    }
                    else if(I.getOpcode() == 1){

                        if(t->I->getOperand(0)->getType()->isIntegerTy()){
                            errs() << " find new constant\n";
                            errs() << *(t->I->getOperand(0)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
                            Tree imm_l = tree(996, 0, 0);//#define IMM 996
                            t->kids[0] = imm_l;
                            errs() << "store left\n";
                            if(CI) {
                                errs() << "CI exists!\n";
                                errs() << CI->getValue() << '\n';
                                imm_l->val = CI->getSExtValue();
                            }
                            else {
                                if(TL->tptr == NULL){
                                    if(!findSymbolTable(ST, I.getOperand(0), imm_l))
                                        errs() << "unable to recognize left kids of store!\n";
                                }
                                else if(!mergeTreeListLeft(TL, I.getOperand(0), t)){
                                    if(!findSymbolTable(ST, I.getOperand(0), imm_l))
                                        errs() << " unable to recognize left kids of store!\n";
                                }
                            }

                        }
                        else if(I.getOperand(0)->getType()->isPointerTy()){
                            errs() << "store from a pointer!\n";
                            Tree offset = tree(999, 0, 0);
                            t->kids[0] = offset;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }

                    }
                    else if(!mergeTreeList(TL, t)){
                        errs() << "independent tree!\n";
                        //addTree(TL, t);
                    }
                    else errs() << "unknown operation\n";
                }
                else{
                    addSymbolTable(ST, (Value* )&I);
                }
            }

        int NumInst = 0, NumBB = 0;
        for(auto I = inst_begin(f); I != inst_end(f); I++){
            NumInst++;
        }
        for(auto &bb : f.getBasicBlockList()){
            NumBB++;
        }
        LiveTable* LiveIn  = new LiveTable [NumBB];//LiveIn[a] get live in of BacisBlock a
        InstMap* IM = new InstMap [NumInst];
        int j = 0;
        for(auto I = inst_begin(f); I != inst_end(f); I++, j++){
            IM[j].I = &*I;
            IM[j].N = j + 1;
        }
        int i = 0;
        errs() << "number of instructions : " << NumInst << '\n';
        errs() << "number of bb: " << NumBB <<'\n';
        auto& bbList = f.getBasicBlockList();
        for(auto bb = bbList.begin(); bb != bbList.end(); bb++, i++){
            LiveIn[i].LR = new LiveRange [NumInst];
            LiveIn[i].bb = &*bb;
            LiveIn[i].NumVar = NumInst;
            j = 0;
            for(auto I = inst_begin(&f), E = inst_end(&f); I != E; j++, I++){
                LiveIn[i].LR[j].v = (Value*) &*I;
                LiveIn[i].LR[j].start = j + 1;
                LiveIn[i].LR[j].end = 0;
                if((&*I) == (&* (LiveIn[i].bb->begin()))){
                    LiveIn[i].bbstart = j;
                }
                //errs() << "what tf?\n";
            }
          
 
        }
        bool changed = false;
        do
        {
            errs() << "not fixed!\n";
            i = NumBB - 1;
            changed = false;
            auto& bbList = f.getBasicBlockList();
            for(auto bb = bbList.rbegin(); bb != bbList.rend() ,i >= 0; i--, bb++){
                BasicBlock* B = &*bb;
                for(auto bb_succ = succ_begin(B); bb_succ!= succ_end(B); bb_succ++){
                    BasicBlock* B_succ = *bb_succ;
                    changed |= LiveUnion(B, B_succ, LiveIn, NumBB); 
                }
                auto& instList = B->getInstList();
                for(auto I = instList.begin(), E = instList.end(); I != E; I++){
                    //changed != addRange(NULL, &*I, &(LiveIn[i]));
                }
                for(auto I = instList.rbegin() , E = instList.rend(); I != E; I++){
                    //changed |= setStart(I, &(LiveIn[i]));
                    //errs() << I->getOpcode() << '\n';
                    //LiveIn[0].LR[0].v->print(errs());
                    for(int j = 0; j < I->getNumOperands(); j++){
                        Value* operand = I->getOperand(j);
                        changed |= addRange(operand, &*I, &(LiveIn[i]));
                    }
                }
            }
            errs() << changed <<'\n';
        }
        while(changed);

        printTreeList(TL, LiveIn[0].LR, LiveIn[0].NumVar);
    }




    //legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));
    //PM.run(*M);
    return M;
}
