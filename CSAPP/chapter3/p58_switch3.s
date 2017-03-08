# gcc -S -O0 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables p58_switch3.c
	.file	"p58_switch3.c"
	.text
	.globl	switch3
	.type	switch3, @function
switch3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	$-1, %ebx
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	.L3
	cmpl	$1, %eax
	jb	.L4
	cmpl	$2, %eax
	je	.L5
	cmpl	$3, %eax
	je	.L6
	jmp	.L2
.L4:
	movl	8(%ebp), %eax
	movl	(%eax), %ebx
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	jmp	.L2
.L3:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	(%edx,%eax), %ebx
	movl	12(%ebp), %eax
	movl	%ebx, (%eax)
	jmp	.L2
.L5:
	movl	12(%ebp), %eax
	movl	$15, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %ebx
	jmp	.L2
.L6:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	$17, %ebx
.L2:
	movl	%ebx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	switch3, .-switch3
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
