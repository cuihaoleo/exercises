	.file	"p59_switch_prob.c"
	.text
	.globl	switch_prob
	.type	switch_prob, @function
switch_prob:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	leal	-28(%ecx), %edx
	cmpl	$5, %edx
	ja	.L2
	jmp	*.L4(,%edx,4)
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L3
	.long	.L2
	.long	.L3
	.long	.L5
	.long	.L6
	.long	.L7
	.text
.L3:
	sall	$3, %eax
	jmp	.L1
.L5:
	sarl	$3, %eax
	jmp	.L1
.L6:
	leal	0(,%eax,8), %edx
	subl	%eax, %edx
	movl	%edx, %eax
.L7:
	imull	%eax, %eax
.L2:
	addl	$11, %eax
.L1:
	popl	%ebp
	ret
	.size	switch_prob, .-switch_prob
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
