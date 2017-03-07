# gcc p54_decode2.c -m32 -S -O1
	.file	"p54_decode2.c"
	.text
	.globl	decode2
	.type	decode2, @function
decode2:
.LFB0:
	.cfi_startproc
	movl	12(%esp), %edx
	subl	8(%esp), %edx
	movl	%edx, %eax
	sall	$15, %eax
	sarl	$15, %eax
	orl	4(%esp), %edx
	imull	%edx, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	decode2, .-decode2
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
