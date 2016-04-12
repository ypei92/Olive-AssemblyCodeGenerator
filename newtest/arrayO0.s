	.text
	.file	"arrayO0.bc"
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
	movq	$0, -16(%rbp)
	movq	$2, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-16(%rbp), %rax
	addq	-8(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-16(%rbp), %rax
	subq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
