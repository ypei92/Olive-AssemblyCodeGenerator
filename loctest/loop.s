	.text
	.file	"loop.bc"
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
	movl	$0, -36(%rbp)
	movq	$3, -32(%rbp)
	movq	$4, -48(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_3:                                # %for.inc
                                        #   in Loop: Header=BB0_1 Depth=1
	incq	-16(%rbp)
.LBB0_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jge	.LBB0_4
# BB#2:                                 # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	addq	$2, -24(%rbp)
	cmpq	$1, -16(%rbp)
	jne	.LBB0_3
.LBB0_4:                                # %for.end
	movq	$0, -8(%rbp)
	jmp	.LBB0_5
	.p2align	4, 0x90
.LBB0_7:                                # %if.end6
                                        #   in Loop: Header=BB0_5 Depth=1
	addq	$3, -24(%rbp)
.LBB0_5:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpq	$3, -8(%rbp)
	jg	.LBB0_8
# BB#6:                                 # %while.body
                                        #   in Loop: Header=BB0_5 Depth=1
	movq	-8(%rbp), %rax
	incq	%rax
	movq	%rax, -8(%rbp)
	cmpq	$3, %rax
	jl	.LBB0_5
	jmp	.LBB0_7
.LBB0_8:                                # %while.end
	movl	-24(%rbp), %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
