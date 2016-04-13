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
	subq	$32, %rsp
	movq	$2, -24(%rbp)
	movq	$3, -16(%rbp)
	movq	$4, -8(%rbp)
	movq	-24(%rbp), %rax
	addq	%rax, d(%rip)
	movq	-16(%rbp), %rax
	addq	%rax, e(%rip)
	movq	-8(%rbp), %rax
	addq	%rax, f(%rip)
	movq	d(%rip), %rsi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	movq	e(%rip), %rsi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	movq	f(%rip), %rsi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	d,@object               # @d
	.data
	.globl	d
	.p2align	3
d:
	.quad	20                      # 0x14
	.size	d, 8

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
	.asciz	"%lld\n"
	.size	.L.str, 6


	.ident	"clang version 3.9.0 "
	.section	".note.GNU-stack","",@progbits
