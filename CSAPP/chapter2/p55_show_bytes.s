	.arch armv8-a
	.file	"p55_show_bytes.c"
	.section	.rodata
	.align	3
.LC0:
	.string	" %.2x"
	.text
	.align	2
	.global	show_bytes
	.type	show_bytes, %function
show_bytes:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x0, [x29, 24]
	str	w1, [x29, 20]
	str	wzr, [x29, 44]
	b	.L2
.L3:
	ldrsw	x0, [x29, 44]
	ldr	x1, [x29, 24]
	add	x0, x1, x0
	ldrb	w0, [x0]
	mov	w1, w0
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	ldr	w0, [x29, 44]
	add	w0, w0, 1
	str	w0, [x29, 44]
.L2:
	ldr	w1, [x29, 44]
	ldr	w0, [x29, 20]
	cmp	w1, w0
	blt	.L3
	mov	w0, 10
	bl	putchar
	nop
	ldp	x29, x30, [sp], 48
	ret
	.size	show_bytes, .-show_bytes
	.align	2
	.global	show_int
	.type	show_int, %function
show_int:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	add	x0, x29, 28
	mov	w1, 4
	bl	show_bytes
	nop
	ldp	x29, x30, [sp], 32
	ret
	.size	show_int, .-show_int
	.align	2
	.global	show_float
	.type	show_float, %function
show_float:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	s0, [x29, 28]
	add	x0, x29, 28
	mov	w1, 4
	bl	show_bytes
	nop
	ldp	x29, x30, [sp], 32
	ret
	.size	show_float, .-show_float
	.align	2
	.global	show_pointer
	.type	show_pointer, %function
show_pointer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x0, [x29, 24]
	add	x0, x29, 24
	mov	w1, 8
	bl	show_bytes
	nop
	ldp	x29, x30, [sp], 32
	ret
	.size	show_pointer, .-show_pointer
	.section	.rodata
	.align	3
.LC1:
	.string	"Integer 0x%0*x: "
	.align	3
.LC2:
	.string	"Float %g: "
	.align	3
.LC3:
	.string	"Pointer %p: "
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	add	x0, x29, 20
	str	x0, [x29, 24]
	mov	x1, 4
	ldr	x0, [x29, 24]
	bl	fill_random_bytes
	add	x0, x29, 16
	mov	x1, 4
	bl	fill_random_bytes
	ldr	w1, [x29, 20]
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	mov	w2, w1
	mov	w1, 8
	bl	printf
	ldr	w0, [x29, 20]
	bl	show_int
	ldr	s0, [x29, 16]
	fcvt	d0, s0
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	ldr	s0, [x29, 16]
	bl	show_float
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	ldr	x1, [x29, 24]
	bl	printf
	ldr	x0, [x29, 24]
	bl	show_pointer
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 6.1.1 20161110"
	.section	.note.GNU-stack,"",@progbits
