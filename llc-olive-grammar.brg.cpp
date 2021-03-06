%{
/*
   FILE: llc-olive-grammar.brg
  
   Copyright (c) 1997 Princeton University

   All rights reserved.

   This software is to be used for non-commercial purposes only,
   unless authorized permission to do otherwise is obtained.  
   For more information, contact spam@ee.princeton.edu
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <llvm/IR/Instruction.h>
//#include <llvm/IR/Instructions.h>
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
#include "llvm/IR/Constants.h"
#include "llvm/IR/Constant.h"

using namespace llvm;

enum {
    CALL=54,
    RET=1,
	ADD=11,
    MERGE=997,
    LOAD=30,
    STORE=31,
    IMM=996,
    ARG=998,
    OFFSET=999,
    ARGEND=995,
    CMP=51,
    BR=800,
    BRC=2
};

static char ArgRegs[6][5] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
static char CalleeRegs[5][5] = {"%rbx", "%r12", "%r13", "%r14", "%r15"};
static char CallerRegs[2][5] = {"%r10", "%r11"};
static char Regs[13][5] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%rbx", "%r12", "%r13", "%r14", "%r15", "%r10", "%r11"}; 
static bool IfRegAvailable[13] = {0};
extern int NumofRegs;
static int LocalVarStack = 0;

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
//struct LiveRange

typedef struct tree {
	int op;
	struct tree *kids[2];
	int val;
    SymbolTable* ST;
    llvm::Instruction *I;
    int valtype;
    //LiveRange* LR;
	struct { struct burm_state *state; } x;
} *NODEPTR, *Tree;

#define GET_KIDS(p)	((p)->kids)
#define PANIC printf
#define STATE_LABEL(p) ((p)->x.state)
#define SET_STATE(p,s) (p)->x.state=(s)
#define DEFAULT_COST	break
#define NO_ACTION(x)

typedef struct COST {
    int cost;
} COST;
#define COST_LESS(a,b) ((a).cost < (b).cost)
static COST COST_INFINITY = { 32767 };
static COST COST_ZERO     = { 0 };

enum {
    reG=0,
    meM=1,
    imM=2,
    arglisT=3,
    pointeR=4,
    nontypE = 999
};

enum {
    SGT = 0,
    SGE = 1,
    SLT = 2,
    SLE = 3,
    NEQ = 4,
    EQ = 5
};

struct LoadedMem {
    char* UnderFunName;
    int Offset;
    int TargetReg;
    LoadedMem *next;

    LoadedMem(){
        UnderFunName = NULL;
        Offset = 0;
        TargetReg = 0;
        next = NULL;
    }

    LoadedMem( char* name, int off, int tarreg, LoadedMem *n ) {
        UnderFunName = name;
        Offset = off;
        TargetReg = tarreg;
        next = n;
    }
};

static LoadedMem *LoadedMemHead = new LoadedMem;
bool findLoadedMem(char* name, int off) {
    LoadedMem *p = LoadedMemHead->next;
    while(p != NULL) {
        if( p->UnderFunName == name || p->Offset == off )
            return true;
        p = p->next;
    }
    return false;
}

void insertLoadedMem(char* name, int off, int tarreg) {
    LoadedMem *lmem = new LoadedMem(name, off, tarreg, LoadedMemHead->next);
    LoadedMemHead->next = lmem;   
}

struct ActiveNode {
    int Start;
    int End;
    int OccupiedReg;
    ActiveNode* next;
    
    ActiveNode() {
        Start = 0;
        End = 0;
        OccupiedReg = -1;
        next = NULL;
    }

    ActiveNode( int s, int e, int o, ActiveNode* p = NULL) {
        Start = s;
        End = e;
        OccupiedReg = o;
        next = p;
    }
};

static ActiveNode *ActiveNodeHead = new ActiveNode;
void expireOldIntervals(int cur_point) {
    ActiveNode *p = ActiveNodeHead->next;
    while(p != NULL){
        if( p->End > cur_point ) 
            break;
        p = p->next;
    }
    ActiveNode *q = ActiveNodeHead->next;
    ActiveNodeHead->next = p;
    while( q != p ) {
        IfRegAvailable[q->OccupiedReg] = 1;        
        ActiveNode *tmp = q->next;
        delete q;
        q = tmp;
    }
}

int lengthActiveNodeList() {
    ActiveNode *p = ActiveNodeHead->next;
    int counter = 0;
    while(p!=NULL) {
        p = p->next;
        counter ++;
    }
    return counter;
}

void insertActiveNode(int start, int end, int target) {
    if(IfRegAvailable[target] == 0) {
        printf("already used, abort\n");
        return;
    }
    IfRegAvailable[target] = 0;
    ActiveNode *p = ActiveNodeHead->next;
    ActiveNode *q = ActiveNodeHead;
    while(p != NULL) {
        if( p->End >= end )
            break;
        q = p;
        p = p->next;
    }
    q -> next = new ActiveNode(start, end, target, p);
}

void clearActiveNodeList() {
    ActiveNode *p = ActiveNodeHead->next;
    while(p != NULL) {
        ActiveNodeHead->next = p -> next;
        delete p;
        p = ActiveNodeHead->next;
    }
    for( int i = 0 ; i < NumofRegs; i++)
        IfRegAvailable[i] = 1;
}

void printActiveNodeList() {
    ActiveNode *p = ActiveNodeHead->next;
    while(p != NULL) {
        printf("Start = %d, End = %d, TargetReg = %d\n", p->Start, p->End, p->OccupiedReg);
        p = p->next;
    }
}

ActiveNode* findEndlast(){
    ActiveNode *p = ActiveNodeHead->next;
    while(p != NULL) {
        p = p -> next;
    }
    return p;
}


struct SpilledNode {
    int Start;
    int End;
    int Offset;
    SpilledNode *next;

    SpilledNode() {
        Start = 0;
        End = 0;
        Offset = -1;
        next = NULL;
    }

    SpilledNode( int s, int e, int off, SpilledNode* p = NULL) {
        Start = s;
        End = e;
        Offset = off;
        next = p;
    }
};

static SpilledNode *SpilledNodeHead = new SpilledNode;

int insertSpilledNode( int start, int end) {
    SpilledNode *p = SpilledNodeHead->next;
    SpilledNode *q = SpilledNodeHead;
    while(p != NULL) {
        if( p->End >= end )
            break;
        q = p;
        p = p->next;
    }
    int offset = LocalVarStack+8*(++SpilledNodeHead->Start);
    q -> next = new SpilledNode(start, end, offset, p);
    return offset; 
}

int lengthSpilledNodeList() {
    SpilledNode *p = SpilledNodeHead->next;
    int counter = 0;
    while( p!= NULL) {
        p = p->next;
        counter++;
    }
    return counter;
}

bool removeSpilledNode(int end) {
    SpilledNode *p = SpilledNodeHead->next;
    SpilledNode *q = SpilledNodeHead;
    while( p!=NULL ) {
        if( p->End == end )
            break;
        q = p;
        p = p->next;
    }

    if(p == NULL) {
        printf("nomatch\n");
        return false;
    }
    else {
        q->next = p->next;
        delete p;
        return true;
    }
}

void clearSpilledNodeList() {
    SpilledNode *p = SpilledNodeHead->next;
    while(p != NULL) {
        SpilledNodeHead->next = p -> next;
        delete p;
        p = SpilledNodeHead->next;
    }
    for( int i = 0 ; i < NumofRegs; i++)
        IfRegAvailable[i] = 1;

    SpilledNodeHead->Start = 0;
}

/*
int RegAllocation(int start, int end) {
    int i = 0;
    ActiveNode *p;

    expireOldIntervals(start);
    int NumNodes = lengthActiveNodeList();
    int NumSpilled=lengthSpilledNodeList();
    
    int NumSlots = NumofRegs - NumNodes;
    int NumUnassigned = NumSpilled + 1; 
    int NumofAssign = (NumSlots > NumUnassigned)?NumUnassigned:NumSlots;

    int addr = -1;
    if( NumNodes == NumofRegs) {
        p = findEndlast();
        if( p->End > end) { //spill the last one
            printf("    push %s\n", Regs[p->OccupiedReg])
            insertActiveNode(start, end, p->OccupiedReg);
            insertSpilledNode(p->Start, p->End);
            return p->OccupiedReg;
        }
        else {
            i = insertSpilledNode(start, end);
            return i;
        }
    }
    else {
        for(i = NumofRegs; i > 0  ; i--)
            if(IfRegAvailable[i] == 1)
                break;
        insertActiveNode(start, end, i); 
        return i;
    }
}
*/

int RegAllocation(int start, int end) {
    int i = 0;
    int NumNodes = lengthActiveNodeList();

    if( NumNodes == NumofRegs) {
        //spill
    }
    else {
        for(i = NumofRegs; i > 0  ; i--)
            if(IfRegAvailable[i] == 1)
                break;
        insertActiveNode(start, end, i); 
        return i;
    }
}

/*static char* burm_string = "FOO";*/
static int _ern = 0;

static int shouldTrace = 0;
static int shouldCover = 0;
//static int RegCounter = 1;
static llvm::Function* PreFun = NULL;

int OP_LABEL(NODEPTR p) {
	switch (p->op) {
	    //case IMM:  if (p->val == 0) return ZERO;
        case CALL: return 1;
        case RET: return 2; 
        case ADD: return 3;
        case MERGE: return 4;
        case LOAD: return 5;
        case STORE: return 6;
        case IMM: return 7;
        case ARG: return 8;
        case OFFSET: return 9;
        case ARGEND: return 10;
        case CMP: return 11;
        case BR: return 12;
        case BRC:return 13;
	    default: return p->op;
	}
}

static void burm_trace(NODEPTR, int, COST);

%}
%term BURP=0 CALL=54 RET=1 ADD=11 MERGE=997 LOAD=30 STORE=31
%term IMM=996 ARG=998 OFFSET=999 ARGEND=995 CMP=51 BR=800 BRC=2
%declare<void> stmt<int indent>;
%declare<void> reg<int indent>;
%declare<void> mem<int indent>;
%declare<void> imm<int indent>;
%declare<void> arglist<int indent>;
%declare<void> argend<int indent>;
%%

stmt:	BURP(_,_,_)
	{ return 1; }
	= {
		$immed[2,stmt](10);
	};


stmt:   reg
    { $cost[0].cost=$cost[1].cost; }
    = {
        llvm::Function* CurFun = $0->I->getFunction();
        int LocalVarStore = 0; 
        if( CurFun != PreFun ) {
            PreFun = CurFun;
            clearActiveNodeList();
            clearSpilledNodeList();
            printf("_Your_%s:\n",CurFun->getName().data());
            printf("    pushq %%rbp\n");
            printf("    movq %%rsp, %%rbp\n");
            if($0->ST!=NULL) {
                LocalVarStore = $0->ST->addrCount;
                LocalVarStack = LocalVarStore;
                printf("    subq $%d, %%rsp\n", LocalVarStore);
            }
            else
                LocalVarStack = 0;
        }
        $action[1](0);
    };

stmt:   mem
    { $cost[0].cost=$cost[1].cost; }
    = {
        llvm::Function* CurFun = $0->I->getFunction();
        int LocalVarStore = 0; 
        if( CurFun != PreFun ) {
            PreFun = CurFun;
            clearActiveNodeList();
            clearSpilledNodeList();
            printf("_Your_%s:\n",CurFun->getName().data());
            printf("    pushq %%rbp\n");
            printf("    movq %%rsp, %%rbp\n");
            if($0->ST!=NULL) {
                LocalVarStore = $0->ST->addrCount;
                LocalVarStack = LocalVarStore;
                printf("    subq $%d, %%rsp\n", LocalVarStore);
            }
            else
                LocalVarStack = 0;
        }
        $action[1](0);
    };

reg:   BR
    { $cost[0].cost=0;}
    = {
        llvm::Function* CurFun = $0->I->getFunction();
        printf("    jmp LABEL\n");
        printf("%s_LABEL:\n", CurFun->getName().data());
    };

reg:   BRC(CMP(reg, reg))
    { $cost[0].cost=$cost[3].cost+$cost[4].cost+1; }
    = {
        $action[3](0);
        $action[4](0);
        BasicBlock* opd1 = (BasicBlock*) $0->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) $0->I->getOperand(2);
        const char* thenlabel = opd1->getName().data();
        const char* elselabel = opd2->getName().data();
        const char* funcname = $0->I->getFunction()->getName().data();
        
        printf("    cmpq %%%d, %%%d\n", $3->val, $4->val);
        switch($0->val){
            case SGT:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        printf("%s_%s:\n",funcname, thenlabel);
    };

reg:   BRC(CMP(LOAD(mem), reg))
    { $cost[0].cost=$cost[4].cost+$cost[5].cost+1; }
    = {
        $action[4](0);
        $action[5](0);
        BasicBlock* opd1 = (BasicBlock*) $0->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) $0->I->getOperand(2);
        const char* thenlabel = opd1->getName().data();
        const char* elselabel = opd2->getName().data();
        const char* funcname = $0->I->getFunction()->getName().data();
        
        printf("    cmpq %d(%%rbp), %%%d\n", $4->val, $5->val);
        switch($0->val){
            case SGT:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        printf("%s_%s:\n",funcname, thenlabel);
    };

reg:   BRC(CMP(reg, LOAD(mem)))
    { $cost[0].cost=$cost[3].cost+$cost[5].cost+1; }
    = {
        $action[3](0);
        $action[5](0);
        BasicBlock* opd1 = (BasicBlock*) $0->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) $0->I->getOperand(2);
        const char* thenlabel = opd1->getName().data();
        const char* elselabel = opd2->getName().data();
        const char* funcname = $0->I->getFunction()->getName().data();
        
        printf("    cmpq %%%d, %d(%%rbp)\n", $3->val, $5->val);
        switch($0->val){
            case SGT:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        printf("%s_%s:\n",funcname, thenlabel);
    };

reg:    RET(imm)
    { $cost[0].cost=$cost[2].cost+1;}
    = {
        $action[2](0);
        printf("    movq $%d, %%rax\n", $2->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    ret\n\n");

        $0->val = $2->val;
        $0->valtype = imM;
    };

reg:    RET(reg)
    { $cost[0].cost=$cost[2].cost+1;}
    = {
        $action[2](0);
        printf("    movq %%%d, %%rax\n", $2->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    ret\n\n");

        $0->val = $2->val;
        $0->valtype = reG;
    };

reg:    RET(mem)
    { $cost[0].cost=$cost[2].cost+1;}
    = {
        $action[2](0);
        printf("    movq %d(%%rbp), %%rax\n", $2->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    ret\n");

        $0->val = $2->val;
        $0->valtype = meM;
    };

reg:    CALL(arglist)
    { $cost[0].cost=$cost[2].cost+1; }
    = {
        if( $0->val != 0 )
            $action[2](0);

        unsigned int NumOperands = $0->I->getNumOperands();
        llvm::Value* FunValue = $0->I->getOperand(NumOperands - 1);
        int tar = RegAllocation($0->LiveRange->start, $0->LiveRange->end);

        printf("    call %s\n", FunValue -> getName().data());
        printf("    movq %%rax, %s\n", Regs[tar]);

        $0->val = tar;
        $0->valtype = reG;
    };

reg:    ADD(reg, reg)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    addq %%%d, %%%d\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = reG;
    };


reg:    ADD(imm, reg)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    addq $%d, %%%d\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = reG;
    };

reg:    ADD(mem, reg)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    addq %d(%%rbp), %%%d\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = reG;
    };

reg:    ADD(LOAD(mem), reg)
    { $cost[0].cost=$cost[3].cost+$cost[4].cost+1; }
    = {
        $action[3](0);
        $action[4](0);

        printf("    addq %d(%%rbp), %%%d\n", $3->val, $4->val);

        $0->val = $4->val;
        $0->valtype = reG;
    };

reg:   CMP(reg, reg)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);
        printf("    cmpq %%%d, %%%d\n", $2->val, $3->val);
    };

reg:    LOAD(reg)
    { $cost[0].cost=$cost[2].cost+1; }
    = {
        $action[2](0);

        // printf("    movq %%%d, %%%d\n", $2->val, RegCounter);
        int tar = RegAllocation($0->LiveRange->start, $0->LiveRange->end);
        printf("    movq %d(%%rbp), %s\n", $2->val, Regs[tar]);

        $0->val = tar;
        $0->valtype = reG;
    };

reg:    LOAD(mem)
    { $cost[0].cost=$cost[2].cost+1; }
    = {
        $action[2](0);

        //Function* CurFun = $0->I->getFunction();
        //char* name = (char*)CurFun->getName().data;
        //if(findLoadedMem(name, $2->val))
        //insertLoadedMem(name, $2->val, RegCounter);

        int tar = RegAllocation($0->LiveRange->start, $0->LiveRange->end);
        printf("    movq %d(%%rbp), %s\n", $2->val, Regs[tar]);

        $0->val = tar;
        $0->valtype = reG;
    };

reg:    LOAD(LOAD(mem))
    { $cost[0].cost=$cost[3].cost+1; }
    = {
        $action[3](0);

        //printf("    movq %d(%%rbp), %%%d\n", $3->val, RegCounter);

        int tar = RegAllocation($0->LiveRange->start, $0->LiveRange->end);
        printf("    movq %d(%%rbp), %s\n", $3->val, Regs[tar]);

        $0->val = tar;
        $0->valtype = reG;
    };

reg:    LOAD(LOAD(LOAD(mem)))
    { $cost[0].cost=$cost[4].cost+1; }
    = {
        $action[4](0);

        //printf("    movq %d(%%rbp), %%%d\n", $4->val, RegCounter);

        int tar = RegAllocation($0->LiveRange->start, $0->LiveRange->end);
        printf("    movq %d(%%rbp), %s\n", $4->val, Regs[tar]);

        $0->val = tar;
        $0->valtype = reG;
    };

reg:    ARG
    { $cost[0].cost = 0; }
    = {
        $0->val = -1;
    };

mem:    ADD(reg, mem)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    addq %%%d, %d(%%rbp)\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = meM;
    };

mem:    ADD(reg, LOAD(mem))
    { $cost[0].cost=$cost[2].cost+$cost[4].cost+1; }
    = {
        $action[2](0);
        $action[4](0);

        printf("    addq %%%d, %d(%%rbp)\n", $2->val, $4->val);

        $0->val = $4->val;
        $0->valtype = meM;
    };


mem:    STORE(imm, mem)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    movq $%d, %d(%%rbp)\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = meM;
    };


mem:    STORE(reg, mem)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    movq %%%d, %d(%%rbp)\n", $2->val, $3->val);

        $0->val = $3->val;
        $0->valtype = meM;
    };

mem:    STORE(mem, mem)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    leaq %d(%%rbp), %%rax\n", $2->val);    
        printf("    movq %%rax, %d(%%rbp)\n", $3->val);

        $0->val = $3->val;
        $0->valtype = meM;
    };

mem:    OFFSET
    { $cost[0].cost=0; }
    = {
        return;
    };

arglist:    MERGE(reg, arglist)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        if( $3->val < 7 )
            printf("    movq %%%d, %s\n", $2->val, ArgRegs[$3->val]);
        else
            printf("    movq %%%d, %d(%%rsp)\n", $2->val, 8*($3->val-6));

        $0->val = $3->val+1;
        $0->valtype = arglisT;
    };

arglist:    MERGE(LOAD(mem), arglist)
    { $cost[0].cost=$cost[3].cost+$cost[4].cost+1; }
    = {
        $action[3](0);
        $action[4](0);

        if( $4->val < 7 )
            printf("    movq %d(%%rbp), %s\n", $3->val, ArgRegs[$4->val]);
        else
            printf("    movq %d(%%rbp), %d(%%rsp)\n", $3->val, 8*($4->val-6));

        $0->val = $4->val+1;
        $0->valtype = arglisT;
 
    };

arglist:    MERGE(reg, argend)
    { $cost[0].cost=$cost[2].cost+$cost[3].cost+1; }
    = {
        $action[2](0);
        $action[3](0);

        printf("    movq %%%d, %s\n", $2->val, ArgRegs[0]);

        $0->val = 1;
        $0->valtype = arglisT;
    };

arglist:    MERGE(LOAD(mem), argend)
    { $cost[0].cost=$cost[3].cost+$cost[4].cost+1; }
    = {
        $action[3](0);
        $action[4](0);

        printf("    movq %d(%%rbp), %s\n", $3->val, ArgRegs[0]);

        $0->val = 1;
        $0->valtype = arglisT;
    };

argend:     ARGEND
    { $cost[0].cost=0; }
    = {
        return;
    };

imm:    IMM
    { $cost[0].cost=0; }
    = {
        return;
    };

%%

/* burm_trace - print trace message for matching p */
static void burm_trace(NODEPTR p, int eruleno, COST cost) {
	if (shouldTrace)
		std::cerr << "0x" << p << " matched " << burm_string[eruleno] << " = " << eruleno << " with cost " << cost.cost << "\n";
}

static void gen(NODEPTR p) {
	if (burm_label(p) == 0)
		std::cerr << "no cover\n";
	else {
		stmt_action(p->x.state,0);
		if (shouldCover != 0)
			dumpCover(p, 1, 0);
	}
}

static Tree tree(int op, Tree l, Tree r, SymbolTable* ST) {
	Tree t = (Tree) malloc(sizeof *t);

	t->op = op;
	t->kids[0] = l; t->kids[1] = r;
	t->val = 0;
    t->valtype = nontypE;
	t->x.state = 0;
    t->I = 0;
    t->ST = ST;
	return t;
}
