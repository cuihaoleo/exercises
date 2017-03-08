# gcc -S -O1 -m32 -march=i686 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables p57_cread_alt.c
	.file	"p57_cread_alt.c"
	.text
	.globl	cread
	.type	cread, @function
cread:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	je	.L3
	movl	(%eax), %eax
.L1:
	popl	%ebp
	ret
.L3:
	movl	$0, %eax
	jmp	.L1
	.size	cread, .-cread
	.globl	cread_alt
	.type	cread_alt, @function
cread_alt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	$0, -4(%ebp)
	leal	-4(%ebp), %edx
	testl	%eax, %eax
	cmove	%edx, %eax
	movl	(%eax), %eax
	leave
	ret
	.size	cread_alt, .-cread_alt
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
