	.text
	.file	"global_variableO0.bc"
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
	subq	$16, %rsp
	movl	$0, -12(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -4(%rbp)
	movl	-12(%rbp), %eax
	addl	%eax, d(%rip)
	movslq	-8(%rbp), %rax
	addq	%rax, e(%rip)
	movslq	-4(%rbp), %rcx
	addq	f(%rip), %rcx
	movq	%rcx, f(%rip)
	movl	d(%rip), %esi
	movq	e(%rip), %rdx
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	d,@object               # @d
	.data
	.globl	d
	.p2align	2
d:
	.long	20                      # 0x14
	.size	d, 4

	.type	e,@object               # @e
	.globl	e
	.p2align	3
e:
	.quad	30                      # 0x1e
	.size	e, 8

	.type	f,@object               # @f
	.globl	f
	.p2align	3
f:
	.quad	40                      # 0x28
	.size	f, 8

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d %ld %lld\n"
	.size	.L.str, 13


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
