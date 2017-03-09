# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables p63_sum_col.c
	.file	"p63_sum_col.c"
	.text
	.globl	sum_col
	.type	sum_col, @function
sum_col:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %edx   # n@EDX
	leal	(%edx,%edx), %eax   # EAX <- 2*n@EDX
	leal	-1(%eax), %ebx  # EBX <- (2*n)@EAX - 1
	addl	%edx, %eax  # EAX <- n + 2*n = 3*n
	testl	%eax, %eax  # if EAX <= 0
	jle	.L4         # goto .L4(END)
	movl	%eax, %esi  # ESI <- 3*n
	sall	$2, %ebx    # EBX <- 4*(2n - 1)
	movl	16(%ebp), %edx  # j@EDX
	movl	12(%ebp), %eax  # A@EAX
	leal	(%eax,%edx,4), %ecx # ECX <- &A[0][j]
	movl	$0, %eax    # result@EAX
	movl	$0, %edx    # i@EDX
.L3:
	addl	(%ecx), %eax    # result@EAX += A[i][j]
	addl	$1, %edx    # i@EDX ++
	addl	%ebx, %ecx  # ECX <- &A[i_][j] + 4*(2n-1)@EBX = &A[i][j]
	cmpl	%edx, %esi  # if i@EDX != 3n@ESI
	jne	.L3         # goto .L3(loop)
.L1:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.L4:
	movl	$0, %eax
	jmp	.L1
	.size	sum_col, .-sum_col
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
