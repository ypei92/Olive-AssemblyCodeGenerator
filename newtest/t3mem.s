	.text
	.file	"t3mem.bc"
	.globl	anotherfoo
	.p2align	4, 0x90
	.type	anotherfoo,@function
anotherfoo:                             # @anotherfoo
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
	leaq	(%rdi,%rsi), %rax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	anotherfoo, .Lfunc_end0-anotherfoo
	.cfi_endproc

	.globl	foo
	.p2align	4, 0x90
	.type	foo,@function
foo:                                    # @foo
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
	pushq	%r14
	pushq	%rbx
.Ltmp6:
	.cfi_offset %rbx, -32
.Ltmp7:
	.cfi_offset %r14, -24
	movq	%rsi, %r14
	movq	%rdi, %rbx
	callq	anotherfoo
	leaq	(%rbx,%r14), %rcx
	addq	%rcx, %rax
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
.Lfunc_end1:
	.size	foo, .Lfunc_end1-foo
	.cfi_endproc

	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp8:
	.cfi_def_cfa_offset 16
.Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp10:
	.cfi_def_cfa_register %rbp
	movl	$2, %edi
	movl	$2, %esi
	movl	$4, %edx
	callq	foo
	xorl	%eax, %eax
	popq	%rbp
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
