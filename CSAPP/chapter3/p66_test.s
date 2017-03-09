# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables -fno-inline-functions-called-once p66_test.c
	.file	"p66_test.c"
	.text
	.globl	test
	.type	test, @function
test:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %ecx   # ECX <- i
	movl	12(%ebp), %edx  # EDX <- bp
	imull	$28, %ecx, %ebx # EBX <- 28i
	leal	0(,%ecx,8), %eax    # EAX <- 8i
	subl	%ecx, %eax          # EAX <- 7i
	addl	4(%edx,%ebx), %eax  # ap->idx @EAX <- *(bp+4+28i) + 7i
	movl	200(%edx), %ecx     # ECX <- bp->right
	addl	(%edx), %ecx        # n@ECX
	movl	%ecx, 8(%edx,%eax,4)    # *(bp + 8 + ap->idx) = n
	popl	%ebx
	popl	%ebp
	ret
	.size	test, .-test
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
