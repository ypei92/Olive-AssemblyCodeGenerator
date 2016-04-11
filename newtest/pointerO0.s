	.text
	.file	"pointerO0.bc"
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
	subq	$48, %rsp
	movl	$1, -8(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	-4(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$2, -4(%rbp)
	movl	-8(%rbp), %eax
	movq	-32(%rbp), %rcx
	addl	(%rcx), %eax
	movl	%eax, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	addl	-4(%rbp), %eax
	movl	%eax, -12(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %ecx
	movq	-32(%rbp), %rax
	imull	(%rax), %ecx
	movl	%ecx, -36(%rbp)
	movl	-16(%rbp), %esi
	movl	-12(%rbp), %edx
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d %d %d\n"
	.size	.L.str, 10


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
