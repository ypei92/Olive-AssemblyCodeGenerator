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
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
//#include "/home1/04012/ypei/llvm/include/llvm/IR/Instruction.h"
//#include "/home1/04012/ypei/llvm/include/llvm/IR/Instructions.h"

enum {
    RET=1,
	ADD=11,
    LOAD=30,
    STORE=31,
    IMM=996
};

typedef struct tree {
	int op;
	struct tree *kids[2];
	int val;
    llvm::Instruction *I;
    char datatype;
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

typedef struct LoadedMem {
    char* UnderFunName;
    int Offset;
    int TargetReg;
    struct LoadedMem *next;
} LoadedMem;

/*static char* burm_string = "FOO";*/
static int _ern = 0;

static int shouldTrace = 0;
static int shouldCover = 0;
static int registerCounter = 0;
static LoadedMem *LoadedMemHead = NULL;

int OP_LABEL(NODEPTR p) {
	switch (p->op) {
	//case IMM:  if (p->val == 0) return 661;
    case RET: return 1; 
    case LOAD: return 3;
    case ADD: return 2;
    case STORE: return 4;
    case IMM: return 5;
	default:     return p->op;
	}
}

static void burm_trace(NODEPTR, int, COST);

#define BURP 0
#define RET 1
#define ADD 2
#define LOAD 3
#define STORE 4
#define IMM 5

struct burm_state {
  int op;
  NODEPTR node;
  struct burm_state **kids;
  COST cost[6];
  struct {
    unsigned burm_stmt:2;
    unsigned burm_reg:3;
    unsigned burm_mem:2;
    unsigned burm_imm:1;
    unsigned burm__:1;
  } rule;
};


struct burm_state *burm_label(NODEPTR);
struct burm_state *burm_label1(NODEPTR);

void dumpCover(NODEPTR,int,int);

#endif
