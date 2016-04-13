#ifndef __OLIVE_HEADER_INCLUDED__
#define __OLIVE_HEADER_INCLUDED__
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
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
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/InstrTypes.h"
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
    BRC=2,
    GLOBAL=994,
    PRINTF=993
};

//static char ArgRegs[6][5] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
//static char CalleeRegs[5][5] = {"%rbx", "%r12", "%r13", "%r14", "%r15"};
//static char CallerRegs[2][5] = {"%r10", "%r11"};
static char Regs[13][5] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%rbx", "%r12", "%r13", "%r14", "%r15", "%r10", "%r11"}; 
static bool IfRegAvailable[13] = {0};
extern int NumRegs;
extern int GlobalLength;
extern long long GlobalArray[100];
static int LocalVarStack = 0;
static int AliasArgReg = 0;

struct LiveRange{
    Value *v;
    int start;
    int end;
    bool live;
    LiveRange(){
        v = NULL;
        start = -1;
        end = -1;
        live = false;
    }
};

struct SymbolTable{
    Value* v;
    int addrCount;
    SymbolTable* next;
    Module* M;
    SymbolTable(){
        v = NULL;
        addrCount = 0;
        next = NULL;
    }
    SymbolTable(Module* module){
        v = NULL;
        addrCount = 0;
        next = NULL;
        M = module;
    }
};

typedef struct tree {
	int op;
	struct tree *kids[2];
	int val;
    SymbolTable* ST;
    llvm::Instruction *I;
    int valtype;
    int opop;
    LiveRange* LR;
    bool marked;
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
    globalvaR=5,
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
        if( p->End >= cur_point ) 
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
    for( int i = 0 ; i < NumRegs; i++)
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
    for( int i = 0 ; i < NumRegs; i++)
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
    
    int NumSlots = NumRegs - NumNodes;
    int NumUnassigned = NumSpilled + 1; 
    int NumofAssign = (NumSlots > NumUnassigned)?NumUnassigned:NumSlots;

    int addr = -1;
    if( NumNodes == NumRegs) {
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
        for(i = NumRegs-1; i >= 0  ; i--)
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
    expireOldIntervals(start);

    if( NumNodes == NumRegs) {
        //never spill in our program.....
    }
    else {
        for(i = NumRegs-1; i >= 0  ; i--)
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
static llvm::Function* PreFun = NULL;
static llvm::BasicBlock* PreBB = NULL;
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
        case GLOBAL:return 14;
        case PRINTF:return 15;
	    default: return p->op;
	}
}

static void burm_trace(NODEPTR, int, COST);

#define BURP 0
#define CALL 1
#define RET 2
#define ADD 3
#define MERGE 4
#define LOAD 5
#define STORE 6
#define IMM 7
#define ARG 8
#define OFFSET 9
#define ARGEND 10
#define CMP 11
#define BR 12
#define BRC 13
#define GLOBAL 14
#define PRINTF 15

struct burm_state {
  int op;
  NODEPTR node;
  struct burm_state **kids;
  COST cost[9];
  struct {
    unsigned burm_stmt:2;
    unsigned burm_reg:5;
    unsigned burm_mem:3;
    unsigned burm_imm:1;
    unsigned burm_arglist:3;
    unsigned burm_argend:1;
    unsigned burm_globalvar:2;
    unsigned burm__:1;
  } rule;
};


struct burm_state *burm_label(NODEPTR);
struct burm_state *burm_label1(NODEPTR);

void dumpCover(NODEPTR,int,int);

#endif
