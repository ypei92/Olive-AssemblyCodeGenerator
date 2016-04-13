	.text
	.file	"arithmetic.bc"
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
	movl	$0, -44(%rbp)
	movq	$7, -40(%rbp)
	movq	$3, -32(%rbp)
	movq	$8, -24(%rbp)
	movq	$2, -16(%rbp)
	movq	$-9, -8(%rbp)
	movq	-40(%rbp), %rax
	addq	-32(%rbp), %rax
	cqto
	idivq	-16(%rbp)
	imull	-8(%rbp), %eax
	subl	-24(%rbp), %eax
	movl	$4, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
