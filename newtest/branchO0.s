	.text
	.file	"branchO0.bc"
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
	movl	$0, -20(%rbp)
	movq	$1, -16(%rbp)
	movq	$2, -8(%rbp)
	movq	$0, -32(%rbp)
	movq	-16(%rbp), %rax
	addq	-8(%rbp), %rax
	cmpq	$2, %rax
	jl	.LBB0_2
# BB#1:                                 # %if.then
	movq	-16(%rbp), %rax
	imulq	-8(%rbp), %rax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	-16(%rbp), %rax
	addq	-8(%rbp), %rax
.LBB0_3:                                # %if.end
	movq	%rax, -32(%rbp)
	movl	-20(%rbp), %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
