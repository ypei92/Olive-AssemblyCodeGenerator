	.text
	.file	"condition2.bc"
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
	movl	$0, -20(%rbp)
	movq	$3, -16(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$9, -16(%rbp)
	jg	.LBB0_2
# BB#1:                                 # %if.then
	incq	-8(%rbp)
.LBB0_2:                                # %if.end
	cmpq	$3, -16(%rbp)
	jl	.LBB0_4
# BB#3:                                 # %if.then2
	incq	-8(%rbp)
.LBB0_4:                                # %if.end4
	cmpq	$3, -16(%rbp)
	jl	.LBB0_6
# BB#5:                                 # %if.then6
	incq	-8(%rbp)
.LBB0_6:                                # %if.end8
	cmpq	$3, -16(%rbp)
	jg	.LBB0_8
# BB#7:                                 # %if.then10
	incq	-8(%rbp)
.LBB0_8:                                # %if.end12
	cmpq	$4, -16(%rbp)
	jg	.LBB0_10
# BB#9:                                 # %if.then14
	incq	-8(%rbp)
.LBB0_10:                               # %if.end16
	cmpq	$2, -16(%rbp)
	jl	.LBB0_12
# BB#11:                                # %if.then18
	incq	-8(%rbp)
.LBB0_12:                               # %if.end20
	cmpq	$3, -16(%rbp)
	jne	.LBB0_14
# BB#13:                                # %if.then22
	incq	-8(%rbp)
.LBB0_14:                               # %if.end24
	cmpq	$2, -16(%rbp)
	je	.LBB0_16
# BB#15:                                # %if.then26
	incq	-8(%rbp)
.LBB0_16:                               # %if.end28
	cmpq	$2, -16(%rbp)
	je	.LBB0_18
# BB#17:                                # %if.then30
	incq	-8(%rbp)
.LBB0_18:                               # %if.end32
	movl	-8(%rbp), %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"
	.section	".note.GNU-stack","",@progbits
