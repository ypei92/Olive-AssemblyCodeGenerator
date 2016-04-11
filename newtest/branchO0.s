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
	subq	$16, %rsp
	movl	$0, -16(%rbp)
	movl	$1, -8(%rbp)
	movl	$2, -4(%rbp)
	movl	$0, -12(%rbp)
	movl	-8(%rbp), %eax
	addl	-4(%rbp), %eax
	cmpl	$2, %eax
	jl	.LBB0_2
# BB#1:                                 # %if.then
	movl	-8(%rbp), %eax
	imull	-4(%rbp), %eax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movl	-4(%rbp), %eax
	cltd
	idivl	-8(%rbp)
.LBB0_3:                                # %if.end
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %esi
	movl	-4(%rbp), %edx
	movl	-12(%rbp), %ecx
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	movl	-16(%rbp), %eax
	addq	$16, %rsp
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
