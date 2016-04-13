#include "llc-olive-grammar.h"
#define burm_stmt_NT 1
#define burm_reg_NT 2
#define burm_mem_NT 3
#define burm_imm_NT 4
#define burm_arglist_NT 5
#define burm_argend_NT 6
#define burm_globalvar_NT 7
#define burm___NT 8
extern int burm_max_nt;


void stmt_action(struct burm_state *_s, 

int indent);


void reg_action(struct burm_state *_s, 

int indent);


void mem_action(struct burm_state *_s, 

int indent);


void imm_action(struct burm_state *_s, 

int indent);


void arglist_action(struct burm_state *_s, 

int indent);


void argend_action(struct burm_state *_s, 

int indent);


void globalvar_action(struct burm_state *_s, 

int indent);
#ifndef ALLOC
#define ALLOC(n) malloc(n)
#endif

#ifndef burm_assert
#define burm_assert(x,y) if (!(x)) {  y; abort(); }
#endif

static NODEPTR burm_np;

#define burm_stmt_NT 1
#define burm_reg_NT 2
#define burm_mem_NT 3
#define burm_imm_NT 4
#define burm_arglist_NT 5
#define burm_argend_NT 6
#define burm_globalvar_NT 7
#define burm___NT 8
extern int burm_max_nt;
int burm_max_nt = 8;

std::string burm_ntname[] = {
  "",
  "stmt",
  "reg",
  "mem",
  "imm",
  "arglist",
  "argend",
  "globalvar",
  "_",
  ""
};

static short burm_nts_0[] = { burm___NT, burm___NT, burm___NT, 0 };
static short burm_nts_1[] = { burm_reg_NT, 0 };
static short burm_nts_2[] = { burm_mem_NT, 0 };
static short burm_nts_3[] = { 0 };
static short burm_nts_4[] = { burm_reg_NT, burm_reg_NT, 0 };
static short burm_nts_5[] = { burm_mem_NT, burm_reg_NT, 0 };
static short burm_nts_6[] = { burm_reg_NT, burm_mem_NT, 0 };
static short burm_nts_7[] = { burm_imm_NT, 0 };
static short burm_nts_8[] = { burm_globalvar_NT, 0 };
static short burm_nts_9[] = { burm_arglist_NT, 0 };
static short burm_nts_10[] = { burm_imm_NT, burm_reg_NT, 0 };
static short burm_nts_11[] = { burm_globalvar_NT, burm_reg_NT, 0 };
static short burm_nts_12[] = { burm_reg_NT, burm_globalvar_NT, 0 };
static short burm_nts_13[] = { burm_imm_NT, burm_mem_NT, 0 };
static short burm_nts_14[] = { burm_mem_NT, burm_mem_NT, 0 };
static short burm_nts_15[] = { burm_reg_NT, burm_arglist_NT, 0 };
static short burm_nts_16[] = { burm_mem_NT, burm_arglist_NT, 0 };
static short burm_nts_17[] = { burm_reg_NT, burm_argend_NT, 0 };
static short burm_nts_18[] = { burm_mem_NT, burm_argend_NT, 0 };

short *burm_nts[] = {
  burm_nts_0,  /* 0 */
  burm_nts_1,  /* 1 */
  burm_nts_2,  /* 2 */
  burm_nts_3,  /* 3 */
  burm_nts_4,  /* 4 */
  burm_nts_5,  /* 5 */
  burm_nts_6,  /* 6 */
  burm_nts_7,  /* 7 */
  burm_nts_1,  /* 8 */
  burm_nts_2,  /* 9 */
  burm_nts_8,  /* 10 */
  burm_nts_9,  /* 11 */
  burm_nts_1,  /* 12 */
  burm_nts_2,  /* 13 */
  burm_nts_8,  /* 14 */
  burm_nts_4,  /* 15 */
  burm_nts_10,  /* 16 */
  burm_nts_5,  /* 17 */
  burm_nts_11,  /* 18 */
  burm_nts_5,  /* 19 */
  burm_nts_4,  /* 20 */
  burm_nts_1,  /* 21 */
  burm_nts_8,  /* 22 */
  burm_nts_8,  /* 23 */
  burm_nts_2,  /* 24 */
  burm_nts_2,  /* 25 */
  burm_nts_2,  /* 26 */
  burm_nts_3,  /* 27 */
  burm_nts_12,  /* 28 */
  burm_nts_6,  /* 29 */
  burm_nts_13,  /* 30 */
  burm_nts_6,  /* 31 */
  burm_nts_2,  /* 32 */
  burm_nts_12,  /* 33 */
  burm_nts_14,  /* 34 */
  burm_nts_3,  /* 35 */
  burm_nts_12,  /* 36 */
  burm_nts_15,  /* 37 */
  burm_nts_16,  /* 38 */
  burm_nts_17,  /* 39 */
  burm_nts_18,  /* 40 */
  burm_nts_3,  /* 41 */
  burm_nts_3,  /* 42 */
  burm_nts_3,  /* 43 */
};

char burm_arity[] = {
  3,  /* 0=BURP */
  1,  /* 1=CALL */
  1,  /* 2=RET */
  2,  /* 3=ADD */
  2,  /* 4=MERGE */
  1,  /* 5=LOAD */
  2,  /* 6=STORE */
  0,  /* 7=IMM */
  0,  /* 8=ARG */
  0,  /* 9=OFFSET */
  0,  /* 10=ARGEND */
  2,  /* 11=CMP */
  0,  /* 12=BR */
  1,  /* 13=BRC */
  0,  /* 14=GLOBAL */
  1,  /* 15=PRINTF */
};

std::string burm_opname[] = {
  /* 0 */  "BURP",
  /* 1 */  "CALL",
  /* 2 */  "RET",
  /* 3 */  "ADD",
  /* 4 */  "MERGE",
  /* 5 */  "LOAD",
  /* 6 */  "STORE",
  /* 7 */  "IMM",
  /* 8 */  "ARG",
  /* 9 */  "OFFSET",
  /* 10 */  "ARGEND",
  /* 11 */  "CMP",
  /* 12 */  "BR",
  /* 13 */  "BRC",
  /* 14 */  "GLOBAL",
  /* 15 */  "PRINTF",
};


std::string burm_string[] = {
  /* 0 */  "stmt: BURP(_,_,_)",
  /* 1 */  "stmt: reg",
  /* 2 */  "stmt: mem",
  /* 3 */  "reg: BR",
  /* 4 */  "reg: BRC(CMP(reg,reg))",
  /* 5 */  "reg: BRC(CMP(LOAD(mem),reg))",
  /* 6 */  "reg: BRC(CMP(reg,LOAD(mem)))",
  /* 7 */  "reg: RET(imm)",
  /* 8 */  "reg: RET(reg)",
  /* 9 */  "reg: RET(mem)",
  /* 10 */  "reg: RET(globalvar)",
  /* 11 */  "reg: CALL(arglist)",
  /* 12 */  "reg: PRINTF(reg)",
  /* 13 */  "reg: PRINTF(LOAD(mem))",
  /* 14 */  "reg: PRINTF(LOAD(globalvar))",
  /* 15 */  "reg: ADD(reg,reg)",
  /* 16 */  "reg: ADD(imm,reg)",
  /* 17 */  "reg: ADD(mem,reg)",
  /* 18 */  "reg: ADD(globalvar,reg)",
  /* 19 */  "reg: ADD(LOAD(mem),reg)",
  /* 20 */  "reg: CMP(reg,reg)",
  /* 21 */  "reg: LOAD(reg)",
  /* 22 */  "reg: LOAD(globalvar)",
  /* 23 */  "reg: LOAD(LOAD(globalvar))",
  /* 24 */  "reg: LOAD(mem)",
  /* 25 */  "reg: LOAD(LOAD(mem))",
  /* 26 */  "reg: LOAD(LOAD(LOAD(mem)))",
  /* 27 */  "reg: ARG",
  /* 28 */  "globalvar: ADD(reg,globalvar)",
  /* 29 */  "mem: ADD(reg,mem)",
  /* 30 */  "mem: STORE(imm,mem)",
  /* 31 */  "mem: STORE(reg,mem)",
  /* 32 */  "mem: STORE(ARG,mem)",
  /* 33 */  "mem: STORE(reg,globalvar)",
  /* 34 */  "mem: STORE(mem,mem)",
  /* 35 */  "mem: OFFSET",
  /* 36 */  "globalvar: STORE(reg,globalvar)",
  /* 37 */  "arglist: MERGE(reg,arglist)",
  /* 38 */  "arglist: MERGE(LOAD(mem),arglist)",
  /* 39 */  "arglist: MERGE(reg,argend)",
  /* 40 */  "arglist: MERGE(LOAD(mem),argend)",
  /* 41 */  "argend: ARGEND",
  /* 42 */  "globalvar: GLOBAL",
  /* 43 */  "imm: IMM",
};


std::string burm_files[] = {
"llc-olive-grammar.brg",
"llc-olive-grammar.cpp",
"/home1/04012/ypei/llvm/include",
};

int burm_file_numbers[] = {
  /* 0 */  0,
  /* 1 */  0,
  /* 2 */  0,
  /* 3 */  0,
  /* 4 */  0,
  /* 5 */  0,
  /* 6 */  0,
  /* 7 */  0,
  /* 8 */  0,
  /* 9 */  0,
  /* 10 */  0,
  /* 11 */  0,
  /* 12 */  0,
  /* 13 */  0,
  /* 14 */  0,
  /* 15 */  0,
  /* 16 */  0,
  /* 17 */  0,
  /* 18 */  0,
  /* 19 */  0,
  /* 20 */  0,
  /* 21 */  0,
  /* 22 */  0,
  /* 23 */  0,
  /* 24 */  0,
  /* 25 */  0,
  /* 26 */  0,
  /* 27 */  0,
  /* 28 */  0,
  /* 29 */  0,
  /* 30 */  0,
  /* 31 */  0,
  /* 32 */  0,
  /* 33 */  0,
  /* 34 */  0,
  /* 35 */  0,
  /* 36 */  0,
  /* 37 */  0,
  /* 38 */  0,
  /* 39 */  0,
  /* 40 */  0,
  /* 41 */  0,
  /* 42 */  0,
  /* 43 */  0,
};

int burm_line_numbers[] = {
  /* 0 */  461,
  /* 1 */  468,
  /* 2 */  500,
  /* 3 */  532,
  /* 4 */  545,
  /* 5 */  569,
  /* 6 */  593,
  /* 7 */  617,
  /* 8 */  630,
  /* 9 */  643,
  /* 10 */  656,
  /* 11 */  669,
  /* 12 */  690,
  /* 13 */  703,
  /* 14 */  717,
  /* 15 */  731,
  /* 16 */  745,
  /* 17 */  758,
  /* 18 */  771,
  /* 19 */  784,
  /* 20 */  797,
  /* 21 */  806,
  /* 22 */  821,
  /* 23 */  835,
  /* 24 */  849,
  /* 25 */  869,
  /* 26 */  895,
  /* 27 */  915,
  /* 28 */  922,
  /* 29 */  936,
  /* 30 */  951,
  /* 31 */  963,
  /* 32 */  977,
  /* 33 */  989,
  /* 34 */  1001,
  /* 35 */  1028,
  /* 36 */  1034,
  /* 37 */  1048,
  /* 38 */  1071,
  /* 39 */  1094,
  /* 40 */  1110,
  /* 41 */  1126,
  /* 42 */  1132,
  /* 43 */  1138,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static short burm_decode_stmt[] = {
   -1,
  0,
  1,
  2,
};

static short burm_decode_reg[] = {
   -1,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
};

static short burm_decode_mem[] = {
   -1,
  29,
  30,
  31,
  32,
  33,
  34,
  35,
};

static short burm_decode_imm[] = {
   -1,
  43,
};

static short burm_decode_arglist[] = {
   -1,
  37,
  38,
  39,
  40,
};

static short burm_decode_argend[] = {
   -1,
  41,
};

static short burm_decode_globalvar[] = {
   -1,
  28,
  36,
  42,
};

static short burm_decode__[] = {
   -1,
};

int burm_rule(struct burm_state *state, int goalnt) {
  burm_assert(goalnt >= 1 && goalnt <= 8,
        PANIC("Bad goal nonterminal %d in burm_rule\n", goalnt));
  if (!state)
    return 0;
  switch (goalnt) {
  case burm_stmt_NT:  return burm_decode_stmt[((struct burm_state *)state)->rule.burm_stmt];
  case burm_reg_NT:  return burm_decode_reg[((struct burm_state *)state)->rule.burm_reg];
  case burm_mem_NT:  return burm_decode_mem[((struct burm_state *)state)->rule.burm_mem];
  case burm_imm_NT:  return burm_decode_imm[((struct burm_state *)state)->rule.burm_imm];
  case burm_arglist_NT:  return burm_decode_arglist[((struct burm_state *)state)->rule.burm_arglist];
  case burm_argend_NT:  return burm_decode_argend[((struct burm_state *)state)->rule.burm_argend];
  case burm_globalvar_NT:  return burm_decode_globalvar[((struct burm_state *)state)->rule.burm_globalvar];
  case burm___NT:  return burm_decode__[((struct burm_state *)state)->rule.burm__];
  default:
    burm_assert(0, PANIC("Bad goal nonterminal %d in burm_rule\n", goalnt));
  }
  return 0;
}


struct burm_action {
  int nt;
  struct burm_state* st;
};

#ifndef RULE
#define RULE(n,s) \
    (act = (burm_action*) malloc(sizeof(struct burm_action)),act->nt=n,act->st=s,act)
#endif

int burm_cost_code(COST *_c, int _ern,struct burm_state *_s)
{
  NODEPTR *_children;
  struct burm_action *act;
  switch(_ern){
  default:
    DEFAULT_COST;
  case 0:
    _children = GET_KIDS(_s->node);
{


 return 1; 
}
  break;
  case 1:
{


 (*_c).cost=_s->cost[burm_reg_NT].cost; 
}
  break;
  case 2:
{


 (*_c).cost=_s->cost[burm_mem_NT].cost; 
}
  break;
  case 3:
{


 (*_c).cost=0;
}
  break;
  case 4:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_reg_NT].cost+_s->kids[0]->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 5:
{


 (*_c).cost=_s->kids[0]->kids[0]->kids[0]->cost[burm_mem_NT].cost+_s->kids[0]->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 6:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_reg_NT].cost+_s->kids[0]->kids[1]->kids[0]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 7:
{


 (*_c).cost=_s->kids[0]->cost[burm_imm_NT].cost+1;
}
  break;
  case 8:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+1;
}
  break;
  case 9:
{


 (*_c).cost=_s->kids[0]->cost[burm_mem_NT].cost+1;
}
  break;
  case 10:
{


 (*_c).cost=_s->kids[0]->cost[burm_globalvar_NT].cost+1;
}
  break;
  case 11:
{


 (*_c).cost=_s->kids[0]->cost[burm_arglist_NT].cost+1; 
}
  break;
  case 12:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 13:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 14:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 15:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 16:
{


 (*_c).cost=_s->kids[0]->cost[burm_imm_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 17:
{


 (*_c).cost=_s->kids[0]->cost[burm_mem_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 18:
{


 (*_c).cost=_s->kids[0]->cost[burm_globalvar_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 19:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_mem_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 20:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 21:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 22:
{


 (*_c).cost=_s->kids[0]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 23:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 24:
{


 (*_c).cost=_s->kids[0]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 25:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 26:
{


 (*_c).cost=_s->kids[0]->kids[0]->kids[0]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 27:
{


 (*_c).cost = 0; 
}
  break;
  case 28:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 29:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 30:
{


 (*_c).cost=_s->kids[0]->cost[burm_imm_NT].cost+_s->kids[1]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 31:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 32:
{


 (*_c).cost=_s->kids[1]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 33:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 34:
{


 (*_c).cost=_s->kids[0]->cost[burm_mem_NT].cost+_s->kids[1]->cost[burm_mem_NT].cost+1; 
}
  break;
  case 35:
{


 (*_c).cost=0; 
}
  break;
  case 36:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_globalvar_NT].cost+1; 
}
  break;
  case 37:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_arglist_NT].cost+1; 
}
  break;
  case 38:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_mem_NT].cost+_s->kids[1]->cost[burm_arglist_NT].cost+1; 
}
  break;
  case 39:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_argend_NT].cost+1; 
}
  break;
  case 40:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_mem_NT].cost+_s->kids[1]->cost[burm_argend_NT].cost+1; 
}
  break;
  case 41:
{


 (*_c).cost=0; 
}
  break;
  case 42:
{


 (*_c).cost=0; 
}
  break;
  case 43:
{


 (*_c).cost=0; 
}
  break;
  }
  return 1;
}


void stmt_action(struct burm_state *_s, 

int indent);


void reg_action(struct burm_state *_s, 

int indent);


void mem_action(struct burm_state *_s, 

int indent);


void imm_action(struct burm_state *_s, 

int indent);


void arglist_action(struct burm_state *_s, 

int indent);


void argend_action(struct burm_state *_s, 

int indent);


void globalvar_action(struct burm_state *_s, 

int indent);


#include <stdarg.h>

void burm_exec(struct burm_state *state, int nterm, ...) 
{
  va_list(ap);
  va_start(ap,nterm);

  burm_assert(nterm >= 1 && nterm <= 8,
        PANIC("Bad nonterminal %d in $exec\n", nterm));

  if (state)
    switch (nterm) {
    case burm_stmt_NT:
      stmt_action(state,va_arg(ap,int));
      break;
    case burm_reg_NT:
      reg_action(state,va_arg(ap,int));
      break;
    case burm_mem_NT:
      mem_action(state,va_arg(ap,int));
      break;
    case burm_imm_NT:
      imm_action(state,va_arg(ap,int));
      break;
    case burm_arglist_NT:
      arglist_action(state,va_arg(ap,int));
      break;
    case burm_argend_NT:
      argend_action(state,va_arg(ap,int));
      break;
    case burm_globalvar_NT:
      globalvar_action(state,va_arg(ap,int));
      break;
    default:
      PANIC("Bad nonterminal %d in $exec\n", nterm);
      break;
    }
  else
    PANIC("Bad state for $exec in nonterminal %d \n",nterm);
  va_end(ap);
}

#define EXEC(s,n,a) ( \
  (n == burm_stmt_NT)? burm_exec(s,n,a): \
  (n == burm_reg_NT)? burm_exec(s,n,a): \
  (n == burm_mem_NT)? burm_exec(s,n,a): \
  (n == burm_imm_NT)? burm_exec(s,n,a): \
  (n == burm_arglist_NT)? burm_exec(s,n,a): \
  (n == burm_argend_NT)? burm_exec(s,n,a): \
  (n == burm_globalvar_NT)? burm_exec(s,n,a): \
  PANIC("Bad nonterminal %d in $exec\n", n))

struct burm_state *burm_immed(struct burm_state *s,int n);
#ifndef NO_ACTION
#define NO_ACTION assert(0)
#endif


void stmt_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_stmt[_s->rule.burm_stmt];
  NODEPTR *_children;
  if(_s->rule.burm_stmt==0)
    NO_ACTION(stmt);
  switch(_ern){
  case 0:
    _children = GET_KIDS(_s->node);
{



		stmt_action(burm_immed(_s,0),10);
	
}
  break;
  case 1:
{



        llvm::Function* CurFun = _s->node->I->getFunction();
        llvm::BasicBlock* CurBB = _s->node->I->getParent();
        int LocalVarStore = 0; 
        if( CurFun != PreFun ) {
            PreFun = CurFun;
            PreBB = CurBB;
            clearActiveNodeList();
            clearSpilledNodeList();
            //initialize the activelist
            printf("_Your_%s:\n",CurFun->getName().data());
            printf("    pushq %%rbp\n");
            printf("    movq %%rsp, %%rbp\n");
            if(_s->node->ST!=NULL) {
                LocalVarStore = _s->node->ST->addrCount;
                LocalVarStack = LocalVarStore;
                printf("    subq $%d, %%rsp\n", -LocalVarStore);
            }
            else
                LocalVarStack = 0;
        }
        
        if( CurBB != PreBB ) {
            PreBB = CurBB;
            printf("\n%s_%s:\n",CurFun->getName().data(), CurBB->getName().data());
        }

        reg_action(_s,0);
    
}
  break;
  case 2:
{



        llvm::Function* CurFun = _s->node->I->getFunction();
        llvm::BasicBlock* CurBB = _s->node->I->getParent();
        int LocalVarStore = 0; 
        if( CurFun != PreFun ) {
            PreFun = CurFun;
            PreBB = CurBB;
            clearActiveNodeList();
            clearSpilledNodeList();
            //initialize the activelist
            printf("_Your_%s:\n",CurFun->getName().data());
            printf("    pushq %%rbp\n");
            printf("    movq %%rsp, %%rbp\n");
            if(_s->node->ST!=NULL) {
                LocalVarStore = _s->node->ST->addrCount;
                LocalVarStack = LocalVarStore;
                printf("    subq $%d, %%rsp\n", -LocalVarStore);
            }
            else
                LocalVarStack = 0;
        }

        if( CurBB != PreBB ) {
            PreBB = CurBB;
            printf("\n%s_%s:\n",CurFun->getName().data(), CurBB->getName().data());
        }

        mem_action(_s,0);
    
}
  break;
  }
}


void reg_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_reg[_s->rule.burm_reg];
  NODEPTR *_children;
  if(_s->rule.burm_reg==0)
    NO_ACTION(reg);
  switch(_ern){
  case 3:
{



        llvm::Function* CurFun = _s->node->I->getFunction();

        BasicBlock* opd1 = (BasicBlock*) _s->node->I->getOperand(0);
        const char* jmplabel = opd1->getName().data();
        const char* funcname = _s->node->I->getFunction()->getName().data();
        
        printf("    jmp %s_%s\n",funcname, jmplabel);
        //printf("\n%s_%s:\n", funcname, jmplabel);
    
}
  break;
  case 4:
{



        reg_action(_s->kids[0]->kids[0],0);
        reg_action(_s->kids[0]->kids[1],0);
        BasicBlock* opd1 = (BasicBlock*) _s->node->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) _s->node->I->getOperand(2);
        const char* elselabel = opd1->getName().data();
        const char* thenlabel = opd2->getName().data();
        const char* funcname = _s->node->I->getFunction()->getName().data();
        
        printf("    cmpq %%%d, %%%d\n", _s->kids[0]->kids[0]->node->val, _s->kids[0]->kids[1]->node->val);
        switch(_s->node->val){
            case SGT:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        //printf("\n%s_%s:\n",funcname, thenlabel);
    
}
  break;
  case 5:
{



        mem_action(_s->kids[0]->kids[0]->kids[0],0);
        reg_action(_s->kids[0]->kids[1],0);
        BasicBlock* opd1 = (BasicBlock*) _s->node->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) _s->node->I->getOperand(2);
        const char* elselabel = opd1->getName().data();
        const char* thenlabel = opd2->getName().data();
        const char* funcname = _s->node->I->getFunction()->getName().data();
        
        printf("    cmpq %d(%%rbp), %%%d\n", _s->kids[0]->kids[0]->kids[0]->node->val, _s->kids[0]->kids[1]->node->val);
        switch(_s->node->val){
            case SGT:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        //printf("\n%s_%s:\n",funcname, thenlabel);
    
}
  break;
  case 6:
{



        reg_action(_s->kids[0]->kids[0],0);
        mem_action(_s->kids[0]->kids[1]->kids[0],0);
        BasicBlock* opd1 = (BasicBlock*) _s->node->I->getOperand(1);
        BasicBlock* opd2 = (BasicBlock*) _s->node->I->getOperand(2);
        const char* elselabel = opd1->getName().data();
        const char* thenlabel = opd2->getName().data();
        const char* funcname = _s->node->I->getFunction()->getName().data();
        
        printf("    cmpq %s, %d(%%rbp)\n", Regs[_s->kids[0]->kids[0]->node->val], _s->kids[0]->kids[1]->kids[0]->node->val);
        switch(_s->node->val){
            case SGT:   printf("    jle %s_%s\n", funcname, elselabel);break;
            case SGE:   printf("    jl %s_%s\n", funcname, elselabel);break;
            case SLT:   printf("    jge %s_%s\n", funcname, elselabel);break;
            case SLE:   printf("    jg %s_%s\n", funcname, elselabel);break;
            case NEQ:   printf("    je %s_%s\n", funcname, elselabel);break;
            case EQ:   printf("    jne %s_%s\n", funcname, elselabel);break;
            default:   printf("    nojump %s_%s \n", funcname, elselabel);break;
        }
        //printf("\n%s_%s:\n",funcname, thenlabel);
    
}
  break;
  case 7:
{



        imm_action(_s->kids[0],0);
        printf("    movq $%d, %%rax\n", _s->kids[0]->node->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    retq\n\n");

        _s->node->val = _s->kids[0]->node->val;
        _s->node->valtype = imM;
    
}
  break;
  case 8:
{



        reg_action(_s->kids[0],0);
        printf("    movq %s, %%rax\n", Regs[_s->kids[0]->node->val]);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    retq\n\n");

        _s->node->val = _s->kids[0]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 9:
{



        mem_action(_s->kids[0],0);
        printf("    movq %d(%%rbp), %%rax\n", _s->kids[0]->node->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    retq\n\n");

        _s->node->val = _s->kids[0]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 10:
{



        globalvar_action(_s->kids[0],0);
        printf("    movq g_%d(%%rip), %%rax\n", _s->kids[0]->node->val);
        printf("    movq %%rbp, %%rsp\n");
        printf("    popq %%rbp\n");
        printf("    retq\n\n");

        _s->node->val = _s->kids[0]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 11:
{




        if( _s->node->val != 0 )
            arglist_action(_s->kids[0],0);

        unsigned int NumOperands = _s->node->I->getNumOperands();
        llvm::Value* FunValue = _s->node->I->getOperand(NumOperands - 1);
        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);

        printf("    callq _Your_%s\n", FunValue -> getName().data());
        for( int i = 0; i < AliasArgReg; i++ )
            printf("    popq %s\n", Regs[5-i]);
        printf("    movq %%rax, %s\n", Regs[tar]);

        AliasArgReg = 0;
        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 12:
{



        _s->node->I->print(errs());
        printf("    movq %s, %%rsi\n", Regs[_s->kids[0]->node->val]);
        printf("    movq $.prt, %%rdi\n");
        printf("    xorq %rax, %rax\n");
        printf("    callq printf\n");

        _s->node->val = 0;
        _s->node->valtype = reG;
    
}
  break;
  case 13:
{




        _s->node->I->print(errs());
        printf("    movq %d(%%rbp), %%rsi\n", _s->kids[0]->kids[0]->node->val);
        printf("    movq $.prt, %%rdi\n");
        printf("    xorq %rax, %rax\n");
        printf("    callq printf\n");

        _s->node->val = 0;
        _s->node->valtype = reG;
    
}
  break;
  case 14:
{




        _s->node->I->print(errs());
        printf("    movq g_%d(%%rip), %%rsi\n", _s->kids[0]->kids[0]->node->val);
        printf("    movq $.prt, %%rdi\n");
        printf("    xorq %rax, %rax\n");
        printf("    callq printf\n");

        _s->node->val = 0;
        _s->node->valtype = reG;
    
}
  break;
  case 15:
{




        reg_action(_s->kids[0],0);
        reg_action(_s->kids[1],0);

        printf("    %s %s, %s\n",Operation[_s->node->opop], Regs[_s->kids[0]->node->val], Regs[_s->kids[1]->node->val]);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 16:
{




        imm_action(_s->kids[0],0);
        reg_action(_s->kids[1],0);

        printf("    %s $%d, %s\n",Operation[_s->node->opop], _s->kids[0]->node->val, Regs[_s->kids[1]->node->val]);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 17:
{




        mem_action(_s->kids[0],0);
        reg_action(_s->kids[1],0);

        printf("    %s %d(%%rbp), %s\n",Operation[_s->node->opop], _s->kids[0]->node->val, Regs[_s->kids[1]->node->val]);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 18:
{




        globalvar_action(_s->kids[0],0);
        reg_action(_s->kids[1],0);

        printf("    %s g_%d(%%rip), %s\n",Operation[_s->node->opop], _s->kids[0]->node->val, Regs[_s->kids[1]->node->val]);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 19:
{




        mem_action(_s->kids[0]->kids[0],0);
        reg_action(_s->kids[1],0);

        printf("    %s %d(%%rbp), %s\n",Operation[_s->node->opop], _s->kids[0]->kids[0]->node->val, Regs[_s->kids[1]->node->val]);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = reG;
    
}
  break;
  case 20:
{




        reg_action(_s->kids[0],0);
        reg_action(_s->kids[1],0);
        printf("    cmpq %s, %s\n", Regs[_s->kids[0]->node->val], Regs[_s->kids[1]->node->val]);
    
}
  break;
  case 21:
{




        reg_action(_s->kids[0],0);

        //printf("here here!\n");
        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        printf("    movq %s, %s\n", Regs[_s->kids[0]->node->val], Regs[tar]);
        //printActiveNodeList();

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 22:
{




        globalvar_action(_s->kids[0],0);

        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        printf("    movq g_%d(%%rip), %s\n", _s->kids[0]->node->val, Regs[tar]);
        //printActiveNodeList();

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 23:
{




        globalvar_action(_s->kids[0]->kids[0],0);

        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        printf("    movq g_%d(%%rip), %s\n", _s->kids[0]->kids[0]->node->val, Regs[tar]);
        //printActiveNodeList();

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 24:
{




        mem_action(_s->kids[0],0);


        //Function* CurFun = _s->node->I->getFunction();
        //char* name = (char*)CurFun->getName().data;
        //if(findLoadedMem(name, _s->kids[0]->node->val))

        //printf("here!\n");
        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        printf("    movq %d(%%rbp), %s\n", _s->kids[0]->node->val, Regs[tar]);
        //printActiveNodeList();

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 25:
{



        
        mem_action(_s->kids[0]->kids[0],0);

        //printf("    movq %d(%%rbp), %%%d\n", _s->kids[0]->kids[0]->node->val, RegCounter);
        //printf("$0->LR->start = %d, $0->LR->end = %d", _s->node->LR->start, _s->node->LR->end);
        //printf("here or!\n");


        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        if(!_s->node->I){
            printf("    movq %d(%%rbp), %s\n", _s->kids[0]->kids[0]->node->val, Regs[tar]);
        }
        else {
            printf("    movq %d(%%rbp), %rax\n", _s->kids[0]->kids[0]->node->val);
            printf("    movq (%%rax), %s\n", Regs[tar]);
        }

        //printActiveNodeList();

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 26:
{




        mem_action(_s->kids[0]->kids[0]->kids[0],0);

        int tar = RegAllocation(_s->node->LR->start, _s->node->LR->end);
        if(_s->kids[0]->kids[0]->node->I)
            _s->kids[0]->kids[0]->node->I->print(errs());    
        //printf("    movq %d(%%rbp), %s\n", _s->kids[0]->kids[0]->kids[0]->node->val, Regs[tar]);
        //printActiveNodeList();

        //printf("here or or!\n");
        printf("    movq %d(%%rbp), %%rax\n", _s->kids[0]->kids[0]->kids[0]->node->val);
        printf("    movq (%%rax), %s\n", Regs[tar]);

        _s->node->val = tar;
        _s->node->valtype = reG;
    
}
  break;
  case 27:
{




        _s->node->val = -1;
    
}
  break;
  }
}


void mem_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_mem[_s->rule.burm_mem];
  NODEPTR *_children;
  if(_s->rule.burm_mem==0)
    NO_ACTION(mem);
  switch(_ern){
  case 29:
{




        reg_action(_s->kids[0],0);
        mem_action(_s->kids[1],0);

        //printf("    addq %s, %d(%%rbp)\n", Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);
        printf("    %s %s, %d(%%rbp)\n",Operation[_s->node->opop], Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 30:
{



        imm_action(_s->kids[0],0);
        mem_action(_s->kids[1],0);

        printf("    movq $%d, %d(%%rbp)\n", _s->kids[0]->node->val, _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 31:
{



        reg_action(_s->kids[0],0);
        mem_action(_s->kids[1],0);

        if(_s->kids[0]->node->val < 0)
            printf("report reg = $d\n", _s->kids[0]->node->val);
        printf("    movq %s, %d(%%rbp)\n", Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 32:
{



        mem_action(_s->kids[1],0);

        if(_s->kids[0]->node->val <= 6)
            printf("    movq %s, %d(%%rbp)\n", Regs[_s->kids[0]->node->val-1], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 33:
{



        reg_action(_s->kids[0],0);
        globalvar_action(_s->kids[1],0);

        printf("    movq %s, g_%d(%%rip)\n", Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = globalvaR;
    
}
  break;
  case 34:
{



        mem_action(_s->kids[0],0);
        mem_action(_s->kids[1],0);
        
        bool pointer0 = false, pointer1 = false; 
        if(_s->node->I->getOperand(0)->getType()->isPointerTy())
            pointer0 = 
            _s->node->I->getOperand(0)->getType()->getPointerElementType()->isPointerTy();
        if(_s->node->I->getOperand(1)->getType()->isPointerTy())
            pointer1 = 
            _s->node->I->getOperand(1)->getType()->getPointerElementType()->isPointerTy();

        if(pointer0 == 0 && pointer1 == 1){
            printf("    leaq %d(%%rbp), %%rax\n", _s->kids[0]->node->val);    
            printf("    movq %%rax, %d(%%rbp)\n", _s->kids[1]->node->val);
        }
        else {
            //printf("really?");
            printf("    movq %d(%%rbp), %%rax\n", _s->kids[0]->node->val);    
            printf("    movq %%rax, %d(%%rbp)\n", _s->kids[1]->node->val);
        }
        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = meM;
    
}
  break;
  case 35:
{



        return;
    
}
  break;
  }
}


void imm_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_imm[_s->rule.burm_imm];
  NODEPTR *_children;
  if(_s->rule.burm_imm==0)
    NO_ACTION(imm);
  switch(_ern){
  case 43:
{



        return;
    
}
  break;
  }
}


void arglist_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_arglist[_s->rule.burm_arglist];
  NODEPTR *_children;
  if(_s->rule.burm_arglist==0)
    NO_ACTION(arglist);
  switch(_ern){
  case 37:
{



        reg_action(_s->kids[0],0);
        arglist_action(_s->kids[1],0);

        if( _s->kids[1]->node->val < 6 ){
            if( IfRegAvailable[0] == 0 ) {
                AliasArgReg ++;
                printf("    pushq %s\n", Regs[_s->kids[1]->node->val]);
            }
            printf("    movq %s, %s\n",Regs[_s->kids[0]->node->val], Regs[_s->kids[1]->node->val]);
        }
        else {
            printf("    pushq %s\n", Regs[_s->kids[1]->node->val]);
            //printf("    movq %d(%%rbp), %%rax\n", _s->kids[0]->node->val);
            //printf("    movq %%rax, %d(%%rsp)\n", 8*(_s->kids[1]->node->val-5));
        }

        _s->node->val = _s->kids[1]->node->val+1;
        _s->node->valtype = arglisT;
    
}
  break;
  case 38:
{



        mem_action(_s->kids[0]->kids[0],0);
        arglist_action(_s->kids[1],0);

        if( _s->kids[1]->node->val < 6 ){
            if( IfRegAvailable[0] == 0 ) {
                AliasArgReg ++;
                printf("    pushq %s\n", Regs[_s->kids[1]->node->val]);
            }
            printf("    movq %d(%%rbp), %s\n", _s->kids[0]->kids[0]->node->val, Regs[_s->kids[1]->node->val]);
        }
        else{
            printf("    pushq %d(%%rbp)\n", _s->kids[0]->kids[0]->node->val);
            //printf("    movq %d(%%rbp), %%rax\n", _s->kids[0]->kids[0]->node->val);
            //printf("    movq %%rax, %d(%%rsp)\n", 8*(_s->kids[1]->node->val-5));
        }
        _s->node->val = _s->kids[1]->node->val+1;
        _s->node->valtype = arglisT;
 
    
}
  break;
  case 39:
{



        reg_action(_s->kids[0],0);
        argend_action(_s->kids[1],0);

        if( IfRegAvailable[0] == 0 ) {
            AliasArgReg ++;
            printf("    pushq %s\n", Regs[0]);
        }
        printf("    movq %%%d, %s\n", _s->kids[0]->node->val, Regs[0]);

        _s->node->val = 1;
        _s->node->valtype = arglisT;
    
}
  break;
  case 40:
{



        mem_action(_s->kids[0]->kids[0],0);
        argend_action(_s->kids[1],0);

        if( IfRegAvailable[0] == 0 ) {
            AliasArgReg ++;
            printf("    pushq %s\n", Regs[0]);
        }
        printf("    movq %d(%%rbp), %s\n", _s->kids[0]->kids[0]->node->val, Regs[0]);

        _s->node->val = 1;
        _s->node->valtype = arglisT;
    
}
  break;
  }
}


void argend_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_argend[_s->rule.burm_argend];
  NODEPTR *_children;
  if(_s->rule.burm_argend==0)
    NO_ACTION(argend);
  switch(_ern){
  case 41:
{



        return;
    
}
  break;
  }
}


void globalvar_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_globalvar[_s->rule.burm_globalvar];
  NODEPTR *_children;
  if(_s->rule.burm_globalvar==0)
    NO_ACTION(globalvar);
  switch(_ern){
  case 28:
{




        reg_action(_s->kids[0],0);
        globalvar_action(_s->kids[1],0);

        printf("    %s %s, g_%d(%%rip)\n",Operation[_s->node->opop], Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = globalvaR;
    
}
  break;
  case 36:
{



        reg_action(_s->kids[0],0);
        globalvar_action(_s->kids[1],0);

        if(_s->kids[0]->node->val < 0)
            printf("report reg = $d\n", _s->kids[0]->node->val);
        printf("    movq %s, g_%d(%%rip)\n", Regs[_s->kids[0]->node->val], _s->kids[1]->node->val);

        _s->node->val = _s->kids[1]->node->val;
        _s->node->valtype = globalvaR;
    
}
  break;
  case 42:
{



        return;
    
}
  break;
  }
}
static void burm_closure_reg(struct burm_state *, COST);
static void burm_closure_mem(struct burm_state *, COST);

static void burm_closure_reg(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,1,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 1, c);     s->cost[burm_stmt_NT] = c ;
    s->rule.burm_stmt = 2;
  }
}

static void burm_closure_mem(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,2,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 2, c);     s->cost[burm_stmt_NT] = c ;
    s->rule.burm_stmt = 3;
  }
}

struct burm_state *burm_alloc_state(NODEPTR u,int op,int arity)
{
  struct burm_state *p, **k;
  p = (struct burm_state *)ALLOC(sizeof *p);
  burm_assert(p, PANIC("1:ALLOC returned NULL in burm_alloc_state\n"));
    burm_np = u;
  p->op = op;
  p->node = u;
  if(arity){
    k=(struct burm_state **)ALLOC(arity*sizeof (struct burm_state *));
    burm_assert(k, PANIC("2:ALLOC returned NULL in burm_alloc_state\n"));
    p->kids=k;
  }else
    p->kids=0;
  p->rule.burm_stmt =
  p->rule.burm_reg =
  p->rule.burm_mem =
  p->rule.burm_imm =
  p->rule.burm_arglist =
  p->rule.burm_argend =
  p->rule.burm_globalvar =
  p->rule.burm__ =
    0;
  p->cost[1] =
  p->cost[2] =
  p->cost[3] =
  p->cost[4] =
  p->cost[5] =
  p->cost[6] =
  p->cost[7] =
  p->cost[8] =
    COST_INFINITY;
  return p;
}
struct burm_state *burm_label1(NODEPTR u) {
  int op, arity, i, immed_matched=0;
  COST c=COST_ZERO;
  struct burm_state *s,**k;
  NODEPTR *children;
  op=OP_LABEL(u);
  arity=burm_arity[op];
  switch(op){
  case 0:		/* BURP */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
        /*immediate rule: stmt: BURP(_,_,_) */
    if(burm_cost_code(&c,0,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 0, c);       s->cost[burm_stmt_NT] = c ;
      s->rule.burm_stmt = 1;
      immed_matched=1;
    }
    if(immed_matched){
      for(i=0;i<arity;i++)k[i]=0;
      return s;
    }
    break;
  case 1:		/* CALL */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: CALL(arglist) */
      k[0]->rule.burm_arglist
    ) {
      if(burm_cost_code(&c,11,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 11, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 9;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 2:		/* RET */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: RET(globalvar) */
      k[0]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,10,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 10, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 8;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: RET(mem) */
      k[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,9,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 9, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 7;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: RET(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,8,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 8, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 6;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: RET(imm) */
      k[0]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,7,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 7, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 5;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 3:		/* ADD */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* mem: ADD(reg,mem) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,29,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 29, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 1;
        burm_closure_mem(s, c );
      }
    }
    if (   /* globalvar: ADD(reg,globalvar) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,28,s) && COST_LESS(c,s->cost[burm_globalvar_NT])) {
burm_trace(burm_np, 28, c);         s->cost[burm_globalvar_NT] = c ;
        s->rule.burm_globalvar = 1;
      }
    }
    if (   /* reg: ADD(LOAD(mem),reg) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_mem && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,19,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 19, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 17;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: ADD(globalvar,reg) */
      k[0]->rule.burm_globalvar && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,18,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 18, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 16;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: ADD(mem,reg) */
      k[0]->rule.burm_mem && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,17,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 17, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 15;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: ADD(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,16,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 16, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 14;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: ADD(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,15,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 15, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 13;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 4:		/* MERGE */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* arglist: MERGE(LOAD(mem),argend) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_mem && 
      k[1]->rule.burm_argend
    ) {
      if(burm_cost_code(&c,40,s) && COST_LESS(c,s->cost[burm_arglist_NT])) {
burm_trace(burm_np, 40, c);         s->cost[burm_arglist_NT] = c ;
        s->rule.burm_arglist = 4;
      }
    }
    if (   /* arglist: MERGE(reg,argend) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_argend
    ) {
      if(burm_cost_code(&c,39,s) && COST_LESS(c,s->cost[burm_arglist_NT])) {
burm_trace(burm_np, 39, c);         s->cost[burm_arglist_NT] = c ;
        s->rule.burm_arglist = 3;
      }
    }
    if (   /* arglist: MERGE(LOAD(mem),arglist) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_mem && 
      k[1]->rule.burm_arglist
    ) {
      if(burm_cost_code(&c,38,s) && COST_LESS(c,s->cost[burm_arglist_NT])) {
burm_trace(burm_np, 38, c);         s->cost[burm_arglist_NT] = c ;
        s->rule.burm_arglist = 2;
      }
    }
    if (   /* arglist: MERGE(reg,arglist) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_arglist
    ) {
      if(burm_cost_code(&c,37,s) && COST_LESS(c,s->cost[burm_arglist_NT])) {
burm_trace(burm_np, 37, c);         s->cost[burm_arglist_NT] = c ;
        s->rule.burm_arglist = 1;
      }
    }
    break;
  case 5:		/* LOAD */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: LOAD(LOAD(LOAD(mem))) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->kids[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,26,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 26, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 24;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: LOAD(LOAD(mem)) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,25,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 25, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 23;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: LOAD(mem) */
      k[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,24,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 24, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 22;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: LOAD(LOAD(globalvar)) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,23,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 23, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 21;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: LOAD(globalvar) */
      k[0]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,22,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 22, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 20;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: LOAD(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,21,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 21, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 19;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 6:		/* STORE */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* globalvar: STORE(reg,globalvar) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,36,s) && COST_LESS(c,s->cost[burm_globalvar_NT])) {
burm_trace(burm_np, 36, c);         s->cost[burm_globalvar_NT] = c ;
        s->rule.burm_globalvar = 2;
      }
    }
    if (   /* mem: STORE(mem,mem) */
      k[0]->rule.burm_mem && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,34,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 34, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 6;
        burm_closure_mem(s, c );
      }
    }
    if (   /* mem: STORE(reg,globalvar) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,33,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 33, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 5;
        burm_closure_mem(s, c );
      }
    }
    if (   /* mem: STORE(ARG,mem) */
      k[0]->op == 8 && 	/* ARG */
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,32,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 32, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 4;
        burm_closure_mem(s, c );
      }
    }
    if (   /* mem: STORE(reg,mem) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,31,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 31, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 3;
        burm_closure_mem(s, c );
      }
    }
    if (   /* mem: STORE(imm,mem) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,30,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 30, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 2;
        burm_closure_mem(s, c );
      }
    }
    break;
  case 7:		/* IMM */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* imm: IMM */
      if(burm_cost_code(&c,43,s) && COST_LESS(c,s->cost[burm_imm_NT])) {
burm_trace(burm_np, 43, c);         s->cost[burm_imm_NT] = c ;
        s->rule.burm_imm = 1;
      }
    }
    break;
  case 8:		/* ARG */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* reg: ARG */
      if(burm_cost_code(&c,27,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 27, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 25;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 9:		/* OFFSET */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* mem: OFFSET */
      if(burm_cost_code(&c,35,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 35, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 7;
        burm_closure_mem(s, c );
      }
    }
    break;
  case 10:		/* ARGEND */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* argend: ARGEND */
      if(burm_cost_code(&c,41,s) && COST_LESS(c,s->cost[burm_argend_NT])) {
burm_trace(burm_np, 41, c);         s->cost[burm_argend_NT] = c ;
        s->rule.burm_argend = 1;
      }
    }
    break;
  case 11:		/* CMP */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: CMP(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,20,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 20, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 18;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 12:		/* BR */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* reg: BR */
      if(burm_cost_code(&c,3,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 3, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 1;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 13:		/* BRC */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: BRC(CMP(reg,LOAD(mem))) */
      k[0]->op == 11 && 	/* CMP */
      k[0]->kids[0]->rule.burm_reg&&
      k[0]->kids[1]->op == 5 && 	/* LOAD */
      k[0]->kids[1]->kids[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,6,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 6, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 4;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: BRC(CMP(LOAD(mem),reg)) */
      k[0]->op == 11 && 	/* CMP */
      k[0]->kids[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->kids[0]->rule.burm_mem&&
      k[0]->kids[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,5,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 5, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 3;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: BRC(CMP(reg,reg)) */
      k[0]->op == 11 && 	/* CMP */
      k[0]->kids[0]->rule.burm_reg&&
      k[0]->kids[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,4,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 4, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 2;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 14:		/* GLOBAL */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* globalvar: GLOBAL */
      if(burm_cost_code(&c,42,s) && COST_LESS(c,s->cost[burm_globalvar_NT])) {
burm_trace(burm_np, 42, c);         s->cost[burm_globalvar_NT] = c ;
        s->rule.burm_globalvar = 3;
      }
    }
    break;
  case 15:		/* PRINTF */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: PRINTF(LOAD(globalvar)) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_globalvar
    ) {
      if(burm_cost_code(&c,14,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 14, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 12;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: PRINTF(LOAD(mem)) */
      k[0]->op == 5 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,13,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 13, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 11;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: PRINTF(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,12,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 12, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 10;
        burm_closure_reg(s, c );
      }
    }
    break;
  default:
    burm_assert(0, PANIC("Bad operator %d in burm_state\n", op));
  }
  return s;
}

struct burm_state *burm_label(NODEPTR p) {
  burm_label1(p);
  return ((struct burm_state *)STATE_LABEL(p))->rule.burm_stmt ? STATE_LABEL(p) : 0;
}

void burm_free(struct burm_state *s)
{
  int i,arity=burm_arity[s->op];
  if(s->kids==0)
    free(s);
  else {
    for(i=0;i<arity;i++)
      burm_free(s->kids[i]);
    free(s->kids);
  }
}
struct burm_state *burm_immed(struct burm_state *s,int n)
{
  NODEPTR *children = GET_KIDS(s->node);
  if(s->kids[n])
    return s->kids[n];
  else
  return s->kids[n]=burm_label1(children[n]);
}
int burm_op_label(NODEPTR p) {
  burm_assert(p, PANIC("NULL tree in burm_op_label\n"));
  return OP_LABEL(p);
}

struct burm_state *burm_state_label(NODEPTR p) {
  burm_assert(p, PANIC("NULL tree in burm_state_label\n"));
  return STATE_LABEL(p);
}

NODEPTR burm_child(NODEPTR p, int index) {
  NODEPTR *kids;
  burm_assert(p, PANIC("NULL tree in burm_child\n"));
  kids=GET_KIDS(p);
  burm_assert((0<=index && index<burm_arity[OP_LABEL(p)]),
    PANIC("Bad index %d in burm_child\n", index));

  return kids[index];
}
NODEPTR *burm_kids(NODEPTR p, int eruleno, NODEPTR kids[]) {
  burm_assert(p, PANIC("NULL tree in burm_kids\n"));
  burm_assert(kids, PANIC("NULL kids in burm_kids\n"));
  switch (eruleno) {
  case 0: /* stmt: BURP(_,_,_) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    kids[2] = burm_child(p,2);
    break;
  case 2: /* stmt: mem */
  case 1: /* stmt: reg */
    kids[0] = p;
    break;
  case 43: /* imm: IMM */
  case 42: /* globalvar: GLOBAL */
  case 41: /* argend: ARGEND */
  case 35: /* mem: OFFSET */
  case 27: /* reg: ARG */
  case 3: /* reg: BR */
    break;
  case 4: /* reg: BRC(CMP(reg,reg)) */
    kids[0] = burm_child(burm_child(p,0),0);
    kids[1] = burm_child(burm_child(p,0),1);
    break;
  case 5: /* reg: BRC(CMP(LOAD(mem),reg)) */
    kids[0] = burm_child(burm_child(burm_child(p,0),0),0);
    kids[1] = burm_child(burm_child(p,0),1);
    break;
  case 6: /* reg: BRC(CMP(reg,LOAD(mem))) */
    kids[0] = burm_child(burm_child(p,0),0);
    kids[1] = burm_child(burm_child(burm_child(p,0),1),0);
    break;
  case 24: /* reg: LOAD(mem) */
  case 22: /* reg: LOAD(globalvar) */
  case 21: /* reg: LOAD(reg) */
  case 12: /* reg: PRINTF(reg) */
  case 11: /* reg: CALL(arglist) */
  case 10: /* reg: RET(globalvar) */
  case 9: /* reg: RET(mem) */
  case 8: /* reg: RET(reg) */
  case 7: /* reg: RET(imm) */
    kids[0] = burm_child(p,0);
    break;
  case 25: /* reg: LOAD(LOAD(mem)) */
  case 23: /* reg: LOAD(LOAD(globalvar)) */
  case 14: /* reg: PRINTF(LOAD(globalvar)) */
  case 13: /* reg: PRINTF(LOAD(mem)) */
    kids[0] = burm_child(burm_child(p,0),0);
    break;
  case 39: /* arglist: MERGE(reg,argend) */
  case 37: /* arglist: MERGE(reg,arglist) */
  case 36: /* globalvar: STORE(reg,globalvar) */
  case 34: /* mem: STORE(mem,mem) */
  case 33: /* mem: STORE(reg,globalvar) */
  case 31: /* mem: STORE(reg,mem) */
  case 30: /* mem: STORE(imm,mem) */
  case 29: /* mem: ADD(reg,mem) */
  case 28: /* globalvar: ADD(reg,globalvar) */
  case 20: /* reg: CMP(reg,reg) */
  case 18: /* reg: ADD(globalvar,reg) */
  case 17: /* reg: ADD(mem,reg) */
  case 16: /* reg: ADD(imm,reg) */
  case 15: /* reg: ADD(reg,reg) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    break;
  case 40: /* arglist: MERGE(LOAD(mem),argend) */
  case 38: /* arglist: MERGE(LOAD(mem),arglist) */
  case 19: /* reg: ADD(LOAD(mem),reg) */
    kids[0] = burm_child(burm_child(p,0),0);
    kids[1] = burm_child(p,1);
    break;
  case 26: /* reg: LOAD(LOAD(LOAD(mem))) */
    kids[0] = burm_child(burm_child(burm_child(p,0),0),0);
    break;
  case 32: /* mem: STORE(ARG,mem) */
    kids[0] = burm_child(p,1);
    break;
  default:
    burm_assert(0, PANIC("Bad external rule number %d in burm_kids\n", eruleno));
  }
  return kids;
}

void dumpCover(NODEPTR p, int goalnt, int indent)
{
  int eruleno = burm_rule(STATE_LABEL(p), goalnt);
  short *nts = burm_nts[eruleno];
  NODEPTR kids[10];
  int i;

  std::cerr << "\t\t";
  for (i = 0; i < indent; i++)
    std::cerr << " ";
  std::cerr << burm_string[eruleno] << "\n";
  burm_kids(p, eruleno, kids);
  for (i = 0; nts[i]; i++)
    dumpCover(kids[i], nts[i], indent + 1);
}


#pragma GCC diagnostic pop



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
    t->LR = NULL;
    t->opop = 0;
    t->marked = false;
	return t;

}
