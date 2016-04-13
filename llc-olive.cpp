#include "llc-olive-grammar.h"
#include "llc-olive-grammar_cpp.h"
#include <memory>
#include <list>
using namespace llvm;
    
static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

static cl::opt<std::string>
OutputFilename("o", cl::desc("Output filename"), cl::value_desc("filename"));

static cl::opt<unsigned int>
NumofRegs("num_regs", cl::desc("Number of Registers for Allocation"), cl::init(13));
int NumRegs, GlobalLength;
long long int GlobalArray[100];

std::unique_ptr<Module> makeLLVMModule(cl::opt<std::string> &InputFilename, LLVMContext &Context);


int main( int argc, char **argv) {
    LLVMContext &Context = getGlobalContext();
    cl::ParseCommandLineOptions(argc, argv, "llvm system compiler\n");
    NumRegs = NumofRegs; 
    errs() << "NumofRegs: "<< NumRegs << "\n";
    std::unique_ptr<Module> M = makeLLVMModule(InputFilename, Context);
    
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



struct LiveTable{
    BasicBlock * bb;
    LiveRange* LR;
    LiveRange* argLR;
    int NumVars;
    int bbstart;
    int bbend;
    LiveTable(){
        argLR = NULL;
        bb = NULL;
        LR = NULL;
        NumVars = 0;
        bbstart = 0;
        bbend = 0;
    }
};
#define INT_SIZE 8
void addSymbolTable(SymbolTable* &ST, Value* value){
    /*int temp;
    if(!value->getType()->getPointerElementType()->isPointerTy())
        temp = (value->getType()->getPointerElementType()->getIntegerBitWidth())/8;
    else 
        temp = 8; //#define working on 64bit machinev
<<<<<<< HEAD
        */
    if(ST->v == NULL){
        ST->v = value;
        errs() << "value:" <<  INT_SIZE << '\n';//value->getType()->getTypeAllocSize() << '\n';//(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';
        ST->addrCount = -INT_SIZE;
        return ;
    }
       
    SymbolTable* p = new SymbolTable;
    p->v = value;
    p->next = ST;
    p->M = p->next->M; 
    errs() << "value:" << INT_SIZE << '\n';
        //(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';//value->getType()->getPrimitiveSizeInBits() << '\n';//value->getType()->getTypeAllocSize() << '\n';//(value->getType()->getPointerElementType()->getIntegerBitWidth()) << '\n';
    if(ST->addrCount > 0) 
        p->addrCount = 0 - INT_SIZE;// #define size_int 4
    else
        p->addrCount = ST->addrCount - INT_SIZE;// #define size_int 4
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
    p->M = p->next->M;
    //errs() << "value:" << n << '\n';
    p->addrCount = n;// #define size_int 4
    ST = p;
}
bool findSymbolTable(SymbolTable *ST, Value* val, Tree t){
    for(SymbolTable* temp = ST; temp != NULL; temp = temp->next){
        if(temp->v == val){
            t->val = temp->addrCount;
            errs() << "find from synmboltable : " << t->val <<'\n';
            if(t->val > 0 && t->val <= 6)
                t->op = 998;//#define ARG 998
            return true;
        }
    }
    Module* M = ST->M;
    int i = 0;
    for(auto& globalVar : M->getGlobalList()){
        if(val == &globalVar){
            errs() << "global in find symboltable\n";
            t->op = 994;
            t->val = i;
            return true;
        }
        i++;
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
            //addTree(TL, t);
            removeTree(TL, root);
            return true;
        }
        else if((t->I) && t->I->getNumOperands() && t->I->getOperand(i)->getType()->isIntegerTy()){
            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(i));
            if(CI) {
                Tree imm = tree(996, 0, 0, t->ST);//#define IMM 996  
                t->kids[i] = imm;
                            //errs() << "store left\n";
                errs() << "CI exists!\n";
                errs() << CI->getValue() << '\n';
                imm->val = CI->getSExtValue();
                return true;
            }
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
        //errs() << "yes merge left!" << operand->getName() << root->I->getOpcode() << '\n';
        removeTree(TL, root);
        return true;
    }
    else if((t->I) && t->I->getNumOperands() && t->I->getOperand(0)->getType()->isIntegerTy()){
        ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
        if(CI) {
        Tree imm_l = tree(996, 0, 0, t->ST);//#define IMM 996  
        t->kids[0] = imm_l;
                            //errs() << "store left\n";
        errs() << "CI exists!\n";
        errs() << CI->getValue() << '\n';
        imm_l->val = CI->getSExtValue();
        return true;
        }
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
    //errs() << "yes merge list left!" << operand->getName() << '\n';
    return tag;
}

bool mergeTreeRight(TreeList* &TL, Tree root, Tree t, Value* operand){//only merge 2nd children
    bool tag = false;
    Instruction* rootI = root->I;
    if(operand == (Value*)rootI ){
        t->kids[1] = root;
        //errs() << "yes merge right!" << operand->getName() << '\n';
        removeTree(TL, root);
        return true;
    }
    else if( (t->I) && t->I->getNumOperands() && t->I->getOperand(1)->getType()->isIntegerTy()){
        ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(1));
        if(CI) {
        Tree imm_r = tree(996, 0, 0, t->ST);//#define IMM 996  
        t->kids[1] = imm_r;
                            //errs() << "store left\n";
        errs() << "CI exists!\n";
        errs() << CI->getValue() << '\n';
        imm_r->val = CI->getSExtValue();
        return true;
        }
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
        errs() << "merge tree right : " << tag << '\n';
        if(!tag)
            tag |= mergeTreeRight( TL, temp->tptr, t, operand);       
    }
    return tag;
}

void printTree(Tree t, int depth){
    errs() << depth << ' '<< t->op << ' ';
    if(t->LR) errs() << "LR : " << t->LR->start << " "<< t->LR->end << " ";
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
        if(LR[i].v)
            LR[i].v->print(errs());
        errs() << "\n";
        errs() << "var "<< i << ": "<< LR[i].start << " "<< LR[i].end<< '\n';
    }
}

void printGlobalEntry() {
    int i = 0;
    printf("\n");
    printf("    .global main\n");
    printf("main:\n");
    printf("    pushq %%rbp\n");
    printf("    movq %%rsp, %%rbp\n");
    printf("    callq _Your_main\n");
    printf("    movq %%rbp, %%rsp\n");
    printf("    popq %%rbp\n");
    printf("    ret\n");

    printf("\n");
    printf("    .data\n");
    for(i = 0 ; i < GlobalLength; ++i) {
        printf("g_%d:\n", i);
        printf("    .quad   %d\n", GlobalArray[i]);
        printf("    .size   g_%d, 8\n\n", i);
    }
    printf(".prt:\n");
    printf("    .asciz  \"%%lld\\n\"\n", GlobalArray[i]);
    printf("    .size   .ptr, 6\n\n");
    // traverse the table for global value
    // for printf("g_%s: .qual 0\n", g->val);
}

void printTreeList(TreeList* TL, LiveRange* LR, int n){
    errs() << "this is the output\n";
    for(TreeList* temp = TL; temp != NULL; temp = temp->next){
        if(temp->tptr)
            printTree(temp->tptr, 0);
        //errs() << temp->tptr->op <<'\n';
        gen(temp->tptr);
        //errs()<<"\n";
    }
    
    //printLR(LR, n);
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
    for(int i = 0; i < LT[0].NumVars; i++){
        if(succ_LR[i].end > bb_LR[i].end){
            bb_LR[i].end = succ_LR[i].end;
            changed = true;
        }
        if(succ_LR[i].start < bb_LR[i].start && succ_LR[i].start != -1){
            bb_LR[i].start = succ_LR[i].start;
            changed = true;
        }
        bb_LR[i].live = succ_LR[i].live;
    }
    return changed;
    
}

bool addRangeIfLive(Value *Operand, LiveTable* LT, InstMap* IM){
    int NumVars = LT->NumVars;
    LiveRange* LR = LT->LR;
    int bbend = LT->bbend;
    
    int bbstart = LT->bbstart;
    bool changed = false;
    for(int i = 0; i < NumVars; i++){
        if(LR[i].live){
            if(LR[i].end < bbend){
                errs() << "here";
                changed = true;
                LR[i].end = bbend;
            }
            if(LR[i].start > bbstart){
                errs() << "there";
                LR[i].start = bbstart;
                changed = true;
            }
        }
    }
    return changed;
}
bool addRange(Value* operand, Instruction * I, LiveTable* LT, SymbolTable* ST){
    LiveRange* LR = LT->LR;
    int NumVars = LT->NumVars;
    bool changed = false;
    int opd_ID = -1, I_ID = -1;
    for(int i = 0; i < NumVars; i++){
        if(LR[i].v == operand){
            opd_ID = i;
        }
        if(LR[i].v == (Value*)I){
            //LR[i].v->print(errs());
            //errs() << '\n';
            //I->print(errs());
            //errs() << '\n';
            I_ID = i;
        }
    }
    //errs() << opd_ID << " " << I_ID << '\n';
    Tree temp = tree(0, 0, 0, ST);
    if(opd_ID == -1 && findSymbolTable(ST, operand, temp)){
        int i = 0;
        for(auto& arg : I->getFunction()->getArgumentList()){
            Value* v = (Value *) &arg;
            if(operand == v){
                opd_ID = i;
                LR = LT->argLR;
                break;
            }
            i++;
        }
        if(opd_ID != -1 && LR[opd_ID].end < I_ID){
            LR[opd_ID].end = I_ID;
            changed = true;
        }
        //errs() << " found symboltable: " << opd_ID << " " << I_ID << "\n";
    }
    else if((opd_ID != -1) && LR[opd_ID].end < I_ID){
        LR[opd_ID].end = I_ID;
        LR[opd_ID].live = true; 
        changed = true;
    }
        free(temp);
    return changed;
}
bool setStart(Instruction* I, LiveTable* LT){
    LiveRange* LR = LT->LR;
    int NumVars = LT->NumVars;
    bool changed = false;
    int I_ID = -1;
    for(int i = 0; i < NumVars; i++){
        if(LR[i].v == (Value*)I){
            I_ID = i;
        }
    }
    if(LR[I_ID].start < I_ID ){
        //errs() << "set start: " << I_ID << '\n';
        LR[I_ID].start = I_ID;
        LR[I_ID].live = false;
        changed = true;
    }
    return changed;
}
std::unique_ptr<Module> makeLLVMModule(cl::opt<std::string>& inputfile, LLVMContext &Context) {
    SMDiagnostic Err;
    std::unique_ptr<Module> M;

    M = parseIRFile(inputfile, Err, Context);

    legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));

    //PM.run(*M);
    //FunctionListType &FunctionList = M.getFunctionList();
    printf("    .text\n");
    GlobalLength = 0;
    auto& globalList = M->getGlobalList();
    errs() << globalList.size() << '\n';
    for(auto &globalVar: M->getGlobalList()){
        Instruction * temp = (Instruction *) &globalVar;
        temp->print(errs());
        if(globalVar.hasInitializer() && temp->getNumOperands()){
            ConstantInt *CI = dyn_cast<ConstantInt> (temp->getOperand(0));
            if(CI){
                GlobalArray[GlobalLength] = CI->getSExtValue();
                GlobalLength++;
            }

        }
        else
            GlobalArray[GlobalLength] = 0;
        errs() << GlobalArray[GlobalLength] << '\n';
    }
    errs() << "num of global var: " << GlobalLength << '\n';
    errs() << "num if functions : " << M->getFunctionList().size() << '\n';
    for(auto &f:M->getFunctionList()){
      
        int NumInst = 0, NumBB = 0;
        for(auto I = inst_begin(f); I != inst_end(f); I++){
            NumInst++;
        }
        for(auto &bb : f.getBasicBlockList()){
            NumBB++;
        }
        if(NumInst == 0) continue;
        LiveTable* LiveIn  = new LiveTable [NumBB];//LiveIn[a] get live in of BacisBlock a
        InstMap* IM = new InstMap [NumInst];
        int j = 0;
        for(auto I = inst_begin(f); I != inst_end(f); I++, j++){
            IM[j].I = &*I;
            IM[j].N = j;
        }
        int i = 0;
        errs() << "number of instructions : " << NumInst << '\n';
        errs() << "number of bb: " << NumBB <<'\n';
        auto& bbList = f.getBasicBlockList();
        for(auto bb = bbList.begin(); bb != bbList.end(); bb++, i++){
            errs() << "number of var in function: " << NumInst + f.getArgumentList().size() << "\n";
            LiveIn[i].NumVars = NumInst + f.getArgumentList().size();
            LiveIn[i].LR = new LiveRange [LiveIn[i].NumVars];
            LiveIn[i].bb = &*bb;
            LiveIn[i].argLR = LiveIn[i].LR + NumInst;
            j = 0;
            for(auto I = inst_begin(&f), E = inst_end(&f); I != E; j++, I++){
                LiveIn[i].LR[j].v = (Value*) &*I;
                LiveIn[i].LR[j].start = -1;
                LiveIn[i].LR[j].end = -1;
                if((&*I) == (&* (LiveIn[i].bb->begin()))){
                    LiveIn[i].bbstart = j;
                }
                if((&*I) == (&* (LiveIn[i].bb->end()))){
                    LiveIn[i].bbend = j;
                }

                //errs() << "what tf?\n";
            }
          
 
        }
            
        TreeList* TL = new TreeList;
        SymbolTable* ST = new SymbolTable(&*M);
        int instCount = -1;
        for(auto &arg: f.getArgumentList()){
            if(arg.getArgNo() < 6)
                addArg2SymbolTable(ST,(Value* ) &arg, arg.getArgNo() + 1);
            else
            {
                
                addArg2SymbolTable(ST,(Value* ) &arg, 8* (f.getArgumentList().size() - arg.getArgNo()+1) );

            }
        }
        for(auto &bb:f.getBasicBlockList())
            for( auto &I: bb.getInstList()) {
                //errs() << "===================start of an instruction===========================\n"; 
                //printTreeList(TL, NULL, 0);
                instCount++;
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
                    if(!isa<Function>(*operand))
                        operand->print(errs());
                    errs()<<'\n';
                } 
                Tree t = tree(I.getOpcode(), 0, 0, ST);
                t->I = &I;

                t->LR = &(LiveIn[0].LR[instCount]);
                if(I.getOpcode() != 29)
                    addTree(TL ,t);
                switch(I.getOpcode()){
                    case 29: {// #define alloca 29
                        addSymbolTable(ST, (Value* )&I);
                        break;
                    }
                    case 13: t->opop = 1;// define sub 11.1
                    case 15: t->opop = 2;//define mul 11.2
                    case 11: {//define add 11.0
                        t->opop = 0;
                        if(I.isBinaryOp() && I.hasName()){
                            
                            Tree t_mov = tree(30, 0, 0, ST); //#define LOAD 30
                            t->kids[1] = t_mov;
                            bool temp1 = mergeTreeListLeft(TL, I.getOperand(0), t);
                            bool temp2 = mergeTreeListLeft(TL, I.getOperand(1), t_mov);
                            t_mov->LR = t->LR;
                            if(!temp1){ 
                                errs()<<"merge tree error!\n";
                                exit(1);//addTree(TL, t);
                            }
                        }
                        break;
                    }
                    case 31: {//#define store 31
                        Tree offset_r = tree(999, 0, 0, ST);//#define OFFSET 999
                        t->kids[1] = offset_r;
                        if(t->I->getOperand(0)->getType()->isIntegerTy()){
                            errs() << " store an integer\n";
                            errs() << *(t->I->getOperand(0)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
                            Tree imm_l = tree(999, 0, 0, ST);//#define OFFSET 999
                            t->kids[0] = imm_l;
                            //errs() << "store left\n";
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
                            Tree offset = tree(999, 0, 0, ST);
                            t->kids[0] = offset;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }
                        //printTreeList(TL);   
                        if(!(mergeTreeListRight(TL, I.getOperand(1), t)||findSymbolTable(ST, I.getOperand(1),offset_r))){
                            errs() << "find symboltable error!\n";
                            exit(1);
                        }
                        break;
                    }
                    case 30: {//#define load 30
                        Tree offset = tree(999, 0, 0, ST);// #define OFFSET 999
                        t->kids[0] = offset;
                        if(I.getOperand(0)->getType()->getPointerElementType()->isPointerTy()){
                            errs() << "load from a pointer!\n";
                            if(!findSymbolTable(ST, I.getOperand(0), offset)){
                                errs() << "merg tree list & find ST error!\n";
                                exit(1);
                            }
                        }
                        else if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0),offset))){
                            errs() << "merge tree list & find symboltable error!\n";
                            exit(1);
                        }
                        break;
                    }
                    case 54: { // #define call 54
                        Tree tmp = t;
                        if(strcmp(I.getOperand(I.getNumOperands() - 1)->getName().data() , "printf") == 0){
                            errs() << " isprintf \n"; 
                            t->op = 993; //#define printf 993
                            Value* operand = I.getOperand(1); 
                            mergeTreeListLeft(TL, operand, t);
                            break;
                        }
                        if(I.getNumOperands() > 1){
                            t->kids[0] = tree(997, 0, 0, ST);// #define ARGLIST 997
                            tmp = t->kids[0];
                            t->val = I.getNumOperands() - 1;
                        }
                        for(int i = I.getNumOperands() - 2; i >= 0; i--){
                            Tree t_arglist = tree(997, 0, 0, ST); // #define ARGLIST 997                            
                            tmp->kids[1] = t_arglist;
                            mergeTreeListLeft(TL, I.getOperand(i), tmp);
                            if(i == 0){
                                t_arglist->op = 995;//#define ARGEND 995
                            }
                            tmp = t_arglist;
                        }
                    
                        break;
                    }
                    case 1: { //#define ret 1
                        if(t->I->getOperand(0)->getType()->isIntegerTy()){
                            errs() << " find new constant\n";
                            errs() << *(t->I->getOperand(0)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
                            Tree imm_l = tree(996, 0, 0, ST);//#define IMM 996
                            t->kids[0] = imm_l;
                            //errs() << "store left\n";
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
                            Tree offset = tree(999, 0, 0, ST);
                            t->kids[0] = offset;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }

                        break;
                    }
                    case 2: {//#define br 2
                        if(I.getNumOperands() == 3){
                            Tree offset = tree(999, 0, 0, ST);
                            t->kids[0] = offset;
                            t->op = 2;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }
                        else if(I.getNumOperands() == 1){
                            t->op = 800;
                        }
                        else errs() << "unknown branck num of operands\n";
                                
                       
                        break;
                    }
                    case 51: {//#define cmp 51
                        if(t->I->getOperand(0)->getType()->isIntegerTy()){
                            errs() << " find new constant\n";
                            errs() << *(t->I->getOperand(0)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(0));
                            Tree imm_l = tree(996, 0, 0, ST);//#define IMM 996
                            t->kids[0] = imm_l;
                            //errs() << "store left\n";
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
                            Tree offset = tree(999, 0, 0, ST);
                            t->kids[0] = offset;
                            if(!(mergeTreeListLeft(TL, I.getOperand(0), t) || findSymbolTable(ST, I.getOperand(0), offset)))
                                errs() << "find symboltable &&! merge tree left error\n";
                        }
                        else errs() << "unknown cmp left opd\n";

                       if(t->I->getOperand(1)->getType()->isIntegerTy()){
                            errs() << " find new constant\n";
                            errs() << *(t->I->getOperand(1)->getType()) << '\n';
                            ConstantInt* CI = dyn_cast<ConstantInt>(t->I->getOperand(1));
                            Tree imm_r = tree(996, 0, 0, ST);//#define IMM 996
                            t->kids[1] = imm_r;
                            //errs() << "store right\n";
                            if(CI) {
                                errs() << "CI exists!\n";
                                errs() << CI->getValue() << '\n';
                                imm_r->val = CI->getSExtValue();
                            }
                            else {
                                if(TL->tptr == NULL){
                                    if(!findSymbolTable(ST, I.getOperand(1), imm_r))
                                        errs() << "unable to recognize right kids of store!\n";
                                }
                                else if(!mergeTreeListRight(TL, I.getOperand(1), t)){
                                    if(!findSymbolTable(ST, I.getOperand(1), imm_r))
                                        errs() << " unable to recognize right kids of store!\n";
                                }
                            }

                        }
                        else if(I.getOperand(1)->getType()->isPointerTy()){
                            errs() << "store from a pointer!\n";
                            Tree offset = tree(999, 0, 0, ST);
                            t->kids[1] = offset;
                            if(!(mergeTreeListRight(TL, I.getOperand(1), t) || findSymbolTable(ST, I.getOperand(1), offset)))
                                errs() << "find symboltable &&! merge tree Right error\n";
                        }
                        else errs() << "unknown cmp right opd\n";
                        CmpInst* cmpI = (CmpInst* ) (t->I);
                        ICmpInst::Predicate predicate = cmpI->getPredicate();
                        switch(predicate){
                            case ICmpInst::ICMP_SGT: t->val = 0; break;
                            case ICmpInst::ICMP_SGE: t->val = 1; break;
                            case ICmpInst::ICMP_SLT: t->val = 2; break;
                            case ICmpInst::ICMP_SLE: t->val = 3; break;
                            case ICmpInst::ICMP_NE: t->val = 4; break;
                            case ICmpInst::ICMP_EQ: t->val = 5; break;
                            default: errs() << "unknown predicate of cmp\n"; break;
                        }
                        //reverse
                        Tree temp;
                        temp = t->kids[0];
                        t->kids[0] = t->kids[1];
                        t->kids[1] = temp;
                        break; 

                    }
                    default: errs() << "unknown operation\n";break;
                }
            }

       
        //printTreeList(TL, LiveIn[0].LR, LiveIn[0].NumVars);
        bool changed = false;
        do
        {
            //errs() << "not fixed!" << NumBB <<" \n";
            i = NumBB - 1;
            changed = false;
            auto& bbList = f.getBasicBlockList();
            for(auto bb = bbList.rbegin(); bb != bbList.rend() ,i >= 0; i--, bb++){
                errs() << "basic block: " << NumBB - 1 - i << "\n";
                
                BasicBlock* B = &*bb;
                for(auto bb_succ = succ_begin(B); bb_succ!= succ_end(B); bb_succ++){
                    BasicBlock* B_succ = *bb_succ;
                    changed |= LiveUnion(B, B_succ, LiveIn, NumBB); 
                }
                auto& instList = B->getInstList();
                //errs() << "changed before before: " << changed << '\n';
                for(auto I = instList.begin(), E = instList.end(); I != E; I++){
                    changed |= addRangeIfLive(&*I, &(LiveIn[i]), IM);
                    if(changed) errs() << "1" ;
                }
                //errs() << "changed before:" << changed << '\n';
                for(auto I = instList.rbegin() , E = instList.rend(); I != E; I++){
                    changed |= setStart(&*I, &(LiveIn[i]));
                    //errs() << I->getOpcode() << '\n';
                    //LiveIn[0].LR[0].v->print(errs());
                    //errs() << "changed mid: " << changed << '\n';
                    for(int j = 0; j < I->getNumOperands(); j++){
                        Value* operand = I->getOperand(j);
                        changed |= addRange(operand, &*I, &(LiveIn[i]), ST);
                    }
                    //errs() << "changed after: "<< changed <<'\n';
                }
                if(i != 0){
                    for(int k = 0; k < LiveIn[i].NumVars; k++)
                        LiveIn[i - 1].LR[k].live = LiveIn[i].LR[k].live;

                }
                else{
                    for(int k = 0; k < LiveIn[i].NumVars; k++)
                        LiveIn[NumBB - 1].LR[k].live = LiveIn[i].LR[k].live;


                }
            }
            //errs() << changed <<'\n';
            printLR(LiveIn[0].LR, LiveIn[0].NumVars);
        }
        while(changed);
        i = 0;
        j = 0;
        for(auto bb = bbList.begin(); bb != bbList.end(), i <= NumBB; i++, bb++){
            BasicBlock* B = &*bb;
            auto& instList = B->getInstList();
            for(auto I = instList.begin(); I != instList.end(); I++){
                if(I->getParent() == B){
                    LiveIn[0].LR[j] = LiveIn[i].LR[j];
                    //errs() << "equals!" << j << "\n";
                    j++;
                }
            }
        }
        
        
        printTreeList(TL, LiveIn[0].LR, LiveIn[0].NumVars);
        delete TL;
        delete ST;
    }

    printGlobalEntry();

    //legacy::PassManager PM;
    //PM.add(new PrintModulePass(&llvm::cout));
    //PM.run(*M);
    return M;
}
