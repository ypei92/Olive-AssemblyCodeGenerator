	.text
	.file	"condition1.bc"
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	$0, -28(%rbp)
	movq	$3, -16(%rbp)
	movq	$4, -24(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$9, -16(%rbp)
	jg	.LBB0_2
# BB#1:                                 # %if.then
	movq	$4, -8(%rbp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	$2, -8(%rbp)
.LBB0_3:                                # %if.end
	cmpq	$6, -24(%rbp)
	jl	.LBB0_5
# BB#4:                                 # %if.then2
	incq	-8(%rbp)
	jmp	.LBB0_8
.LBB0_5:                                # %if.else3
	cmpq	$4, -24(%rbp)
	jl	.LBB0_7
# BB#6:                                 # %if.then5
	addq	$4, -8(%rbp)
	jmp	.LBB0_8
.LBB0_7:                                # %if.else6
	movq	$7, -8(%rbp)
.LBB0_8:                                # %if.end8
	cmpq	$9, -16(%rbp)
	jg	.LBB0_11
# BB#9:                                 # %land.lhs.true
	cmpq	$4, -24(%rbp)
	jl	.LBB0_11
# BB#10:                                # %if.then11
	incq	-8(%rbp)
.LBB0_11:                               # %if.end13
	cmpq	$11, -16(%rbp)
	jl	.LBB0_13
# BB#12:                                # %if.then15
	movq	$-90, -8(%rbp)
	jmp	.LBB0_14
.LBB0_13:                               # %if.else16
	movq	-16(%rbp), %rax
	addq	%rax, -8(%rbp)
.LBB0_14:                               # %if.end18
	movl	-8(%rbp), %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
