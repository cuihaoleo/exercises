# gcc -S -O1 -m32 -fno-omit-frame-pointer -fno-asynchronous-unwind-tables -fno-inline-functions-called-once p64_word_sum.c
# 参考：Calling convention
	.file	"p64_word_sum.c"
	.text
	.globl	word_sum
	.type	word_sum, @function
word_sum:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %eax   # &result@[diff:-8]@EAX
	movl	16(%ebp), %ecx  # s1.v@ECX
	movl	12(%ebp), %edx  # s1.p@EDX
	movl	(%edx), %edx    # *s1.p@EDX
	movl	%edx, %ebx  # EBX <- *s1.p
	imull	%ecx, %ebx  # EBX <- *s1.p * s1.v
	movl	%ebx, (%eax)    # result.prod
	addl	%ecx, %edx  # EDX <- *s1.p + s1.v
	movl	%edx, 4(%eax)   # result.sum
	popl	%ebx
	popl	%ebp
	ret	$4  # 附加参数（指向返回值的指针）是由 callee 恢复栈的
	.size	word_sum, .-word_sum
	.globl	diff
	.type	diff, @function
diff:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	leal	8(%ebp), %eax   # &x@EAX
	movl	12(%ebp), %edx  # y@EDX
	leal	-8(%ebp), %ecx  # &s2@[-8]@ECX
	pushl	%edx    # s1.v = y
	pushl	%eax    # s1.p = &x
	pushl	%ecx    # &s2, ptr to retval of word_sum
                        # 结构体返回值在 caller 栈上分配空间
                        # 并将其指针作为一个附加参数传给 callee
	call	word_sum
	movl	-8(%ebp), %eax  # EAX <- s2.prod
	subl	-4(%ebp), %eax  # EAX += s2.sum
	leave
	ret
	.size	diff, .-diff
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
