# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables p60_store_ele.c
	.file	"p60_store_ele.c"
	.text
	.globl	store_ele
	.type	store_ele, @function
store_ele:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	leal	(%eax,%eax,8), %edx
	movl	%ecx, %eax
	sall	$6, %eax
	subl	%ecx, %eax
	addl	%edx, %eax
	addl	16(%ebp), %eax
	movl	A(,%eax,4), %edx
	movl	20(%ebp), %eax
	movl	%edx, (%eax)
	movl	$2772, %eax
	popl	%ebp
	ret
	.size	store_ele, .-store_ele
	.comm	A,2772,32
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
