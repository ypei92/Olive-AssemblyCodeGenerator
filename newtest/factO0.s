	.text
	.file	"factO0.bc"
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
	pushq	%rax
.Ltmp3:
	.cfi_offset %rbx, -24
	movl	%edi, -12(%rbp)
	testl	%edi, %edi
	je	.LBB0_1
# BB#2:                                 # %if.else
	cmpl	$1, -12(%rbp)
	jne	.LBB0_4
# BB#3:                                 # %if.then2
	movl	$1, -16(%rbp)
	jmp	.LBB0_5
.LBB0_1:                                # %if.then
	movl	$1, -16(%rbp)
	jmp	.LBB0_5
.LBB0_4:                                # %if.end3
	movl	-12(%rbp), %edi
	decl	%edi
	callq	fact
	movl	%eax, %ebx
	movl	-12(%rbp), %edi
	addl	$-2, %edi
	callq	fact
	addl	%ebx, %eax
	movl	%eax, -16(%rbp)
.LBB0_5:                                # %return
	movl	-16(%rbp), %eax
	addq	$8, %rsp
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
	movl	$4, -8(%rbp)
	movl	$4, %edi
	callq	fact
	movl	%eax, -4(%rbp)
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
