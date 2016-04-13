	.text
	.file	"fabO0.bc"
	.globl	fact
	.p2align	4, 0x90
	.type	fact,@function
fact:                                   # @fact
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
	pushq	%rbx
	subq	$24, %rsp
.Ltmp3:
	.cfi_offset %rbx, -24
	movq	%rdi, -16(%rbp)
	testq	%rdi, %rdi
	je	.LBB0_1
# BB#2:                                 # %if.else
	cmpq	$1, -16(%rbp)
	jne	.LBB0_4
# BB#3:                                 # %if.then2
	movq	$1, -24(%rbp)
	jmp	.LBB0_5
.LBB0_1:                                # %if.then
	movq	$1, -24(%rbp)
	jmp	.LBB0_5
.LBB0_4:                                # %if.end3
	movq	-16(%rbp), %rdi
	decq	%rdi
	callq	fact
	movq	%rax, %rbx
	movq	-16(%rbp), %rdi
	addq	$-2, %rdi
	callq	fact
	addq	%rbx, %rax
	movq	%rax, -24(%rbp)
.LBB0_5:                                # %return
	movq	-24(%rbp), %rax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end0:
	.size	fact, .Lfunc_end0-fact
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp4:
	.cfi_def_cfa_offset 16
.Ltmp5:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp6:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	$4, -16(%rbp)
	movl	$4, %edi
	callq	fact
	movq	%rax, %rcx
	movq	%rcx, -8(%rbp)
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movq	%rcx, %rsi
	callq	printf
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%lld\n"
	.size	.L.str, 6


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
