# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables -fno-inline-functions-called-once p67_proc.c
	.file	"p67_proc.c"
	.text
	.globl	proc
	.type	proc, @function
proc:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	4(%ecx), %edx
	movl	(%edx), %eax
	movl	(%eax), %eax
	subl	(%ecx), %eax
	movl	%eax, 4(%edx)
	popl	%ebp
	ret
	.size	proc, .-proc
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
