#ifndef __OLIVE_HEADER_INCLUDED__
#define __OLIVE_HEADER_INCLUDED__
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
/*
   FILE: sample4.brg
  
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
    CMP=800,
    BR=801,
    BRC=802
};

static char ArgRegs[6][6] = {"%%rdi", "%%rsi", "%%rdx", "%%rcx", "%%r8", "%%r9"};
static char CalleeRegs[5][6] = {"%%rbx", "%%r12", "%%r13", "%%r14", "%%r15"};
static char CallerRegs[2][6] = {"%%r10", "%%r11"};
static char Regs[13][6] = {"%%rdi", "%%rsi", "%%rdx", "%%rcx", "%%r8", "%%r9", "%%rbx", "%%r12", "%%r13", "%%r14", "%%r15", "%%r10", "%%r11"}; 

enum {
    RDI = 0,
    RSI = 1,
    RDX = 2,
    RCX = 3,
    R8  = 4,
    R9  = 5,
    RBX = 6,
    R12 = 7,
    R13 = 8,
    R14 = 9,
    R15 = 10,
    R10 = 11,
    R11 = 12
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

typedef struct tree {
	int op;
	struct tree *kids[2];
	int val;
    SymbolTable* ST;
    llvm::Instruction *I;
    int valtype;
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

typedef struct LoadedMem {
    char* UnderFunName;
    int Offset;
    int TargetReg;
    struct LoadedMem *next;
} LoadedMem;

static LoadedMem *LoadedMemHead = NULL;
LoadedMem* findLoadedMem(char* name, int off, int tarreg) {
    LoadedMem *p = LoadedMemHead;
    while(p != NULL) {
        if( p->UnderFunName == name || p->Offset == off || p->TargetReg == tarreg )
            return p;
        p = p->next;
    }

	LoadedMem *lmem = (LoadedMem*) malloc(sizeof(LoadedMem));

    lmem -> UnderFunName = name;
    lmem -> Offset = off;
    lmem -> TargetReg = tarreg;
    
    if( LoadedMemHead != NULL )
        lmem -> next = LoadedMemHead -> next;
    else 
        lmem -> next = NULL;

    LoadedMemHead = lmem;
    return lmem;
}

/*static char* burm_string = "FOO";*/
static int _ern = 0;

static int shouldTrace = 0;
static int shouldCover = 0;
static int RegCounter = 1;
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

struct burm_state {
  int op;
  NODEPTR node;
  struct burm_state **kids;
  COST cost[8];
  struct {
    unsigned burm_stmt:3;
    unsigned burm_reg:4;
    unsigned burm_mem:3;
    unsigned burm_imm:1;
    unsigned burm_arglist:3;
    unsigned burm_argend:1;
    unsigned burm__:1;
  } rule;
};


struct burm_state *burm_label(NODEPTR);
struct burm_state *burm_label1(NODEPTR);

void dumpCover(NODEPTR,int,int);

#endif
