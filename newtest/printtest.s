    .text
    .global main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq	$1, -8(%rbp)
	movq	$2, -16(%rbp)
    movq    -8(%rbp), %rsi
    movq    $.L.str, %rdi
    xorq    %rax, %rax
    callq   printf
    xorq    %rax, %rax
    movq    %rbp, %rsp
    popq    %rbp
    retq

.L.str:
	.asciz	"%lld\n"
	.size	.L.str, 6
