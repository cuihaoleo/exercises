# gcc -S -O2 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables p61_var_prod_ele.c
	.file	"p61_var_prod_ele.c"
	.text
	.p2align 4,,15
	.globl	var_prod_ele
	.type	var_prod_ele, @function
var_prod_ele:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %edi   # EDI <- n
	testl	%edi, %edi      # if n@EDI <= 0 goto L4 (end)
	jle	.L4
	leal	0(,%edi,4), %eax    # EAX <- 4*n@EDI
	movl	24(%ebp), %edx  # EDX <- k
	movl	%eax, -16(%ebp) # [-16] <- (4*n)@EAX
	movl	20(%ebp), %eax  # EAX <- i
	leal	0(,%eax,4), %esi    # ESI <- 4*i@EAX
	movl	16(%ebp), %eax  # EAX <- B
	imull	%edi, %esi  # ESI <- (4*i)@ESI * n@EDI = 4*i*n
	addl	12(%ebp), %esi  # ESI <- (4*i*n)@ESI + A = &A[i]
	leal	(%eax,%edx,4), %ebx # EBX <- B@EAX + 4*k@EDX = &B[0][k]
	xorl	%eax, %eax  # EAX <- 0
	xorl	%edx, %edx  # EDX <- 0
	.p2align 4,,10
	.p2align 3
.L3:    # j@EDX <- 0,  Bjk@EBX <- &B[0][k],  result@EAX <- 0
	movl	(%esi,%edx,4), %ecx # ECX <- [&A[i]@ESI + 4*j@EDX] = A[i][j]
	addl	$1, %edx    # j@EDX += 1
	imull	(%ebx), %ecx    # ECX <- A[i][j_]@ECX * [Bjk@EBX] = A[i][j_] * B[j_][k]
	addl	-16(%ebp), %ebx # EBX <- Bjk@EBX + (4*n)@[-16] = B[j][k]
	addl	%ecx, %eax  # EAX += @ECX
	cmpl	%edx, %edi  # if j != n goto L3
	jne	.L3
.L1:
	addl	$4, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L4:
	xorl	%eax, %eax
	jmp	.L1
	.size	var_prod_ele, .-var_prod_ele
	.p2align 4,,15
	.globl	var_prod_ele2
	.type	var_prod_ele2, @function
var_prod_ele2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	8(%ebp), %eax
	pushl	%ebx
	movl	%eax, %edx
	subl	$1, %edx
	js	.L11
	movl	20(%ebp), %esi
	leal	0(,%eax,4), %edi
	movl	24(%ebp), %ecx
	sall	$2, %esi
	imull	%eax, %esi
	movl	%edx, %eax
	addl	12(%ebp), %esi
	imull	%edi, %eax
	leal	(%eax,%ecx,4), %ebx
	addl	16(%ebp), %ebx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L10:
	movl	(%esi,%edx,4), %ecx
	subl	$1, %edx
	imull	(%ebx), %ecx
	subl	%edi, %ebx
	addl	%ecx, %eax
	cmpl	$-1, %edx
	jne	.L10
.L8:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L11:
	xorl	%eax, %eax
	jmp	.L8
	.size	var_prod_ele2, .-var_prod_ele2
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
