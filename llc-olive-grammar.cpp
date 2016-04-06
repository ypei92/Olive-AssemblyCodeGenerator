#include "llc-olive-grammar.h"
#define burm_stmt_NT 1
#define burm_reg_NT 2
#define burm_mem_NT 3
#define burm_imm_NT 4
#define burm___NT 5
extern int burm_max_nt;


int stmt_action(struct burm_state *_s, 

int indent);


int reg_action(struct burm_state *_s, 

int indent);


int mem_action(struct burm_state *_s, 

int indent);


int imm_action(struct burm_state *_s, 

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
#define burm___NT 5
extern int burm_max_nt;
int burm_max_nt = 5;

std::string burm_ntname[] = {
  "",
  "stmt",
  "reg",
  "mem",
  "imm",
  "_",
  ""
};

static short burm_nts_0[] = { burm___NT, burm___NT, burm___NT, 0 };
static short burm_nts_1[] = { burm_reg_NT, 0 };
static short burm_nts_2[] = { burm_mem_NT, 0 };
static short burm_nts_3[] = { burm_reg_NT, burm_reg_NT, 0 };
static short burm_nts_4[] = { burm_imm_NT, burm_reg_NT, 0 };
static short burm_nts_5[] = { burm_imm_NT, 0 };
static short burm_nts_6[] = { burm_imm_NT, burm_imm_NT, 0 };
static short burm_nts_7[] = { 0 };

short *burm_nts[] = {
  burm_nts_0,  /* 0 */
  burm_nts_1,  /* 1 */
  burm_nts_2,  /* 2 */
  burm_nts_1,  /* 3 */
  burm_nts_3,  /* 4 */
  burm_nts_4,  /* 5 */
  burm_nts_5,  /* 6 */
  burm_nts_6,  /* 7 */
  burm_nts_7,  /* 8 */
};

char burm_arity[] = {
  3,  /* 0=BURP */
  1,  /* 1=RET */
  2,  /* 2=ADD */
  1,  /* 3=LOAD */
  2,  /* 4=STORE */
  0,  /* 5=IMM */
};

std::string burm_opname[] = {
  /* 0 */  "BURP",
  /* 1 */  "RET",
  /* 2 */  "ADD",
  /* 3 */  "LOAD",
  /* 4 */  "STORE",
  /* 5 */  "IMM",
};


std::string burm_string[] = {
  /* 0 */  "stmt: BURP(_,_,_)",
  /* 1 */  "stmt: reg",
  /* 2 */  "stmt: mem",
  /* 3 */  "reg: RET(reg)",
  /* 4 */  "reg: ADD(reg,reg)",
  /* 5 */  "reg: ADD(LOAD(imm),reg)",
  /* 6 */  "reg: LOAD(imm)",
  /* 7 */  "mem: STORE(imm,imm)",
  /* 8 */  "imm: IMM",
};


std::string burm_files[] = {
"llc-olive-grammar.brg",
"llc-olive-grammar.brg.cpp",
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
};

int burm_line_numbers[] = {
  /* 0 */  87,
  /* 1 */  93,
  /* 2 */  100,
  /* 3 */  108,
  /* 4 */  119,
  /* 5 */  128,
  /* 6 */  137,
  /* 7 */  145,
  /* 8 */  154,
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
};

static short burm_decode_mem[] = {
   -1,
  7,
};

static short burm_decode_imm[] = {
   -1,
  8,
};

static short burm_decode__[] = {
   -1,
};

int burm_rule(struct burm_state *state, int goalnt) {
  burm_assert(goalnt >= 1 && goalnt <= 5,
        PANIC("Bad goal nonterminal %d in burm_rule\n", goalnt));
  if (!state)
    return 0;
  switch (goalnt) {
  case burm_stmt_NT:  return burm_decode_stmt[((struct burm_state *)state)->rule.burm_stmt];
  case burm_reg_NT:  return burm_decode_reg[((struct burm_state *)state)->rule.burm_reg];
  case burm_mem_NT:  return burm_decode_mem[((struct burm_state *)state)->rule.burm_mem];
  case burm_imm_NT:  return burm_decode_imm[((struct burm_state *)state)->rule.burm_imm];
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


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+1;
}
  break;
  case 4:
{


 (*_c).cost=_s->kids[0]->cost[burm_reg_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 5:
{


 (*_c).cost=_s->kids[0]->kids[0]->cost[burm_imm_NT].cost+_s->kids[1]->cost[burm_reg_NT].cost+1; 
}
  break;
  case 6:
{


 (*_c).cost=_s->kids[0]->cost[burm_imm_NT].cost+1; 
}
  break;
  case 7:
{


 (*_c).cost=_s->kids[0]->cost[burm_imm_NT].cost+_s->kids[1]->cost[burm_imm_NT].cost+1; 
}
  break;
  case 8:
{


 (*_c).cost=0; 
}
  break;
  }
  return 1;
}


int stmt_action(struct burm_state *_s, 

int indent);


int reg_action(struct burm_state *_s, 

int indent);


int mem_action(struct burm_state *_s, 

int indent);


int imm_action(struct burm_state *_s, 

int indent);


#include <stdarg.h>

void burm_exec(struct burm_state *state, int nterm, ...) 
{
  va_list(ap);
  va_start(ap,nterm);

  burm_assert(nterm >= 1 && nterm <= 5,
        PANIC("Bad nonterminal %d in $exec\n", nterm));

  if (state)
    switch (nterm) {
    case burm_stmt_NT:
      PANIC("$exec cannot take non-void functions as arguments\n");
      break;
    case burm_reg_NT:
      PANIC("$exec cannot take non-void functions as arguments\n");
      break;
    case burm_mem_NT:
      PANIC("$exec cannot take non-void functions as arguments\n");
      break;
    case burm_imm_NT:
      PANIC("$exec cannot take non-void functions as arguments\n");
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
  PANIC("Bad nonterminal %d in $exec\n", n))

struct burm_state *burm_immed(struct burm_state *s,int n);
#ifndef NO_ACTION
#define NO_ACTION assert(0)
#endif


int stmt_action(struct burm_state *_s, 

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



        reg_action(_s,0);
        return 0;
    
}
  break;
  case 2:
{



        mem_action(_s,0);
        return 0;
    
}
  break;
  }
}


int reg_action(struct burm_state *_s, 

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



		int op0 = reg_action(_s->kids[0],0);
        printf("    mov %%%d, %%rax\n", op0);
        printf("    mov %%rbp, %%rsp\n");
        printf("    pop %%rbp\n");
        printf("    ret\n");
        return 0;
    
}
  break;
  case 4:
{



		int op0 = reg_action(_s->kids[0],0);
		int op1 = reg_action(_s->kids[1],0);
        printf("    add %%%d, %%%d\n", op0, op1 );
        return op1;
	
}
  break;
  case 5:
{



        int off = imm_action(_s->kids[0]->kids[0],0);
		int op1 = reg_action(_s->kids[1],0);
        printf("    add %d(%%rbp), %%%d\n", off, op1 );
        return op1;
    
}
  break;
  case 6:
{



	    int off = imm_action(_s->kids[0],0);
        printf("    mov %d(%%rbp) , %%%d\n", off, registerCounter);
        return registerCounter++;
	
}
  break;
  }
}


int mem_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_mem[_s->rule.burm_mem];
  NODEPTR *_children;
  if(_s->rule.burm_mem==0)
    NO_ACTION(mem);
  switch(_ern){
  case 7:
{



		int imm    = imm_action(_s->kids[0],0);
		int offset = imm_action(_s->kids[1],0);
        printf("    mov $%d , %d(%%rbp)\n", imm, offset);
        return offset;
	
}
  break;
  }
}


int imm_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_imm[_s->rule.burm_imm];
  NODEPTR *_children;
  if(_s->rule.burm_imm==0)
    NO_ACTION(imm);
  switch(_ern){
  case 8:
{



        return _s->node->val;
    
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
  p->rule.burm__ =
    0;
  p->cost[1] =
  p->cost[2] =
  p->cost[3] =
  p->cost[4] =
  p->cost[5] =
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
  case 1:		/* RET */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: RET(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,3,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 3, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 1;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 2:		/* ADD */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: ADD(LOAD(imm),reg) */
      k[0]->op == 3 && 	/* LOAD */
      k[0]->kids[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,5,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 5, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 3;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: ADD(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,4,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 4, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 2;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 3:		/* LOAD */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: LOAD(imm) */
      k[0]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,6,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 6, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 4;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 4:		/* STORE */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* mem: STORE(imm,imm) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,7,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 7, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 1;
        burm_closure_mem(s, c );
      }
    }
    break;
  case 5:		/* IMM */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {  		/* imm: IMM */
      if(burm_cost_code(&c,8,s) && COST_LESS(c,s->cost[burm_imm_NT])) {
burm_trace(burm_np, 8, c);         s->cost[burm_imm_NT] = c ;
        s->rule.burm_imm = 1;
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
  case 6: /* reg: LOAD(imm) */
  case 3: /* reg: RET(reg) */
    kids[0] = burm_child(p,0);
    break;
  case 7: /* mem: STORE(imm,imm) */
  case 4: /* reg: ADD(reg,reg) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    break;
  case 5: /* reg: ADD(LOAD(imm),reg) */
    kids[0] = burm_child(burm_child(p,0),0);
    kids[1] = burm_child(p,1);
    break;
  case 8: /* imm: IMM */
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

static Tree tree(int op, Tree l, Tree r) {
	Tree t = (Tree) malloc(sizeof *t);

	t->op = op;
	t->kids[0] = l; t->kids[1] = r;
	t->val = 0;
	t->x.state = 0;
	return t;
}

/*
int main(int argc, char *argv[]) {
	Tree t;
	int i;

	for (i = 1; i < argc ; ++i) {
		if (strcmp(argv[i], "--cover") == 0){
			shouldCover = 1;
		}
		if (strcmp(argv[i], "--trace") == 0){
			shouldTrace = 1;
		}
	}
	//printf("a = a + b;\n");

	Tree t0= (Tree) malloc(sizeof *t0);
	Tree t1= (Tree) malloc(sizeof *t1);
	Tree t2= (Tree) malloc(sizeof *t2);
	Tree t3= (Tree) malloc(sizeof *t3);

    t0 -> op = IMM;
    t0 -> val = 1;
    t0 ->kids[0] = 0;
    t0 ->kids[1] = 0;
	t0->x.state = 0;

    t1 -> op = IMM;
    t1 -> val = 0;
    t1 ->kids[0] = 0;
    t1 ->kids[1] = 0;
	t1->x.state = 0;

    t2 -> op = IMM;
    t2 -> val = 2;
    t2 ->kids[0] = 0;
    t2 ->kids[1] = 0;
	t2->x.state = 0;

    t3 -> op = IMM;
    t3 -> val = -4;
    t3 ->kids[0] = 0;
    t3 ->kids[1] = 0;
	t3->x.state = 0;


	t = tree(ADD, 
             tree(LOAD,
                  tree(STORE, t0, t1 ),
                  0),
             tree(LOAD,
                  tree(STORE, t2, t3 ),
                  0)
		);
    Tree t5 = tree(RET,t,0);

    printf("    .text\n");

	gen(t5);

    printf("\n");
    printf("    .global main\n");
    printf("main:\n");
    printf("    push %%rbp\n");
    printf("    mov %%rsp, %%rbp\n");
    printf("    call _Your_main\n");
    printf("    mov %%rbp, %%rsp\n");
    printf("    pop %%rbp\n");
    printf("    ret\n");

    printf("\n");
    printf("    .data\n");
    // traverse the table for global value
    // for printf("g_%s: .qual 0\n", g->val);
	return 0;
}
*/
