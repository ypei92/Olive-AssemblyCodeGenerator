	.text
	.file	"t1.bc"
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
	movl	%edi, -8(%rbp)
	movl	%esi, -4(%rbp)
	movl	%edx, -12(%rbp)
	movl	-8(%rbp), %eax
	addl	-4(%rbp), %eax
	subl	%edx, %eax
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
	subq	$32, %rsp
	movl	$0, -8(%rbp)
	movl	$2, -16(%rbp)
	movl	-8(%rbp), %eax
	addl	$2, %eax
	movl	%eax, -4(%rbp)
	addl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-4(%rbp), %edx
	addl	-16(%rbp), %edx
	movl	%edx, -24(%rbp)
	movl	-4(%rbp), %edi
	movl	-12(%rbp), %esi
	callq	foo
	movl	%eax, -20(%rbp)
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
