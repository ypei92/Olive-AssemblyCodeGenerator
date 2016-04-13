	.text
	.file	"noArgs.bc"
	.globl	stuff
	.p2align	4, 0x90
	.type	stuff,@function
stuff:                                  # @stuff
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
	movq	$1, -24(%rbp)
	movq	$2, -16(%rbp)
	movq	$3, -8(%rbp)
	movq	-24(%rbp), %rax
	addq	-16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-8(%rbp), %rcx
	leaq	(%rax,%rcx), %rdx
	movq	%rdx, -32(%rbp)
	leaq	7(%rcx,%rax), %rax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	stuff, .Lfunc_end0-stuff
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
	subq	$16, %rsp
	movl	$0, -12(%rbp)
	callq	stuff
	movq	%rax, -8(%rbp)
	movl	-8(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
