	.text
	.file	"t3.bc"
	.globl	anotherfoo
	.p2align	4, 0x90
	.type	anotherfoo,@function
anotherfoo:                             # @anotherfoo
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
	movq	%rdi, -8(%rbp)
	movq	%rsi, -24(%rbp)
	addq	-8(%rbp), %rsi
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	addq	-24(%rbp), %rax
	addq	%rsi, %rax
	movq	%rax, -32(%rbp)
	movq	-16(%rbp), %rax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	anotherfoo, .Lfunc_end0-anotherfoo
	.cfi_endproc

	.globl	foo
	.p2align	4, 0x90
	.type	foo,@function
foo:                                    # @foo
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -32(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -48(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rsi
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	callq	anotherfoo
	movq	%rax, -40(%rbp)
	movq	-8(%rbp), %rcx
	addq	-16(%rbp), %rcx
	addq	%rcx, %rax
	addq	$48, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	foo, .Lfunc_end1-foo
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp6:
	.cfi_def_cfa_offset 16
.Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp8:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	$0, -16(%rbp)
	movq	$2, -32(%rbp)
	movq	-16(%rbp), %rax
	addq	$2, %rax
	movq	%rax, -8(%rbp)
	addq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rdx
	addq	-32(%rbp), %rdx
	movq	%rdx, -48(%rbp)
	movq	-8(%rbp), %rdi
	movq	-24(%rbp), %rsi
	callq	foo
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
