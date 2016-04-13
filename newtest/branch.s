	.text
	.file	"branch.bc"
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
	movl	$0, -4(%rbp)
	movq	$1, -32(%rbp)
	movq	$2, -24(%rbp)
	movq	$0, -16(%rbp)
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jle	.LBB0_2
# BB#1:                                 # %if.then
	movq	-24(%rbp), %rax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	-32(%rbp), %rax
.LBB0_3:                                # %if.end
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
