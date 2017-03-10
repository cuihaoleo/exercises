# gcc -S -O1 -m64 -fno-asynchronous-unwind-tables p69_trace.c
	.file	"p69_trace.c"
	.text
	.globl	trace
	.type	trace, @function
trace:
	testq	%rdi, %rdi
	je	.L4
.L5:
	movq	16(%rdi), %rax
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L5
	rep ret
.L4:
	movl	$0, %eax
	ret
	.size	trace, .-trace
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
