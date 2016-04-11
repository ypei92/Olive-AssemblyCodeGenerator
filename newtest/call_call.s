	.text
	.file	"call_call.bc"
	.globl	foo
	.p2align	4, 0x90
	.type	foo,@function
foo:                                    # @foo
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
	movq	32(%rbp), %r10
	movq	24(%rbp), %r11
	movq	16(%rbp), %rax
	movq	%rdi, -64(%rbp)
	movq	%rsi, -56(%rbp)
	movq	%rdx, -48(%rbp)
	movq	%rcx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	movq	%rax, -16(%rbp)
	movq	%r11, -8(%rbp)
	movq	%r10, -72(%rbp)
	movq	-64(%rbp), %rax
	addq	-56(%rbp), %rax
	addq	-48(%rbp), %rax
	addq	-40(%rbp), %rax
	addq	-32(%rbp), %rax
	addq	-24(%rbp), %rax
	addq	-16(%rbp), %rax
	addq	-8(%rbp), %rax
	addq	%r10, %rax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	foo, .Lfunc_end0-foo
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
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
	subq	$112, %rsp
	movq	$1, -64(%rbp)
	movq	$2, -56(%rbp)
	movq	$3, -48(%rbp)
	movq	$4, -40(%rbp)
	movq	$5, -32(%rbp)
	movq	$6, -24(%rbp)
	movq	$7, -16(%rbp)
	movq	$8, -8(%rbp)
	movq	$9, -72(%rbp)
	movq	-64(%rbp), %rdi
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %r8
	movq	-24(%rbp), %r9
	movq	-16(%rbp), %r10
	movq	-8(%rbp), %rax
	movq	%rax, 8(%rsp)
	movq	%r10, (%rsp)
	movq	$9, 16(%rsp)
	callq	foo
	movq	%rax, -88(%rbp)
	movq	-72(%rbp), %rdi
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %r8
	movq	-40(%rbp), %r9
	movq	-48(%rbp), %r10
	movq	-56(%rbp), %r11
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rsp)
	movq	%r11, 8(%rsp)
	movq	%r10, (%rsp)
	callq	foo
	movq	%rax, -80(%rbp)
	xorl	%eax, %eax
	addq	$112, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
