# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables -fno-inline-functions-called-once p65_setVal.c
	.file	"p65_setVal.c"
	.text
	.globl	setVal
	.type	setVal, @function
setVal:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	28(%edx), %eax
	addl	8(%edx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 44(%edx)
	popl	%ebp
	ret
	.size	setVal, .-setVal
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
