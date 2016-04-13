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
	subq	$32, %rsp
	movl	$0, -28(%rbp)
	movq	$1, -24(%rbp)
	movq	$2, -16(%rbp)
	movq	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jle	.LBB0_2
# BB#1:                                 # %if.then
	movq	-16(%rbp), %rax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	-24(%rbp), %rax
.LBB0_3:                                # %if.end
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rsi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%lld\n"
	.size	.L.str, 6


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
