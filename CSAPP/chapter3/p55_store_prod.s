# gcc p55_store_prod.c -S -O1 -m32 -fno-omit-frame-pointer
	.file	"p55_store_prod.c"
	.text
	.globl	store_prod
	.type	store_prod, @function
store_prod:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	.cfi_offset 6, -12
	movl	12(%ebp), %ecx  # load xL
	movl	20(%ebp), %eax  # load yL
	movl	%eax, %esi
	imull	16(%ebp), %esi  # ESI <- yL * xH
	movl	%ecx, %edx
	imull	24(%ebp), %edx  # EDX <- xL * yH
	addl	%edx, %esi      # ESI <- yL*xH + xL*yH
	mull	%ecx            # EDX:EAX <- xL * yL
	addl	%esi, %edx      # EDX <- (xL*yL)L + (yL*xH + xL*yH)
	movl	8(%ebp), %ecx   # load dest
	movl	%eax, (%ecx)    # (dest) <- EAX (low 32bits)
	movl	%edx, 4(%ecx)   # 4(dest) <- ECX (high 32bits)
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	store_prod, .-store_prod
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
