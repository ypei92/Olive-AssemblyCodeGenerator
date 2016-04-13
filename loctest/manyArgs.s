	.text
	.file	"manyArgs.bc"
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
	subq	$48, %rsp
	movl	$0, -12(%rbp)
	movq	$2, 16(%rsp)
	movq	$2, 8(%rsp)
	movq	$2, (%rsp)
	movl	$1, %edi
	movl	$1, %esi
	movl	$1, %edx
	movl	$1, %ecx
	movl	$1, %r8d
	movl	$1, %r9d
	callq	stuff
	movq	%rax, -8(%rbp)
	movl	-8(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
