global _ft_atoi

section .text
_ft_atoi:
	push	r8
	push	r9
	push	rcx
	xor		rax, rax
	xor		r8, r8
	xor		r9, r9
	xor		rcx, rcx
	mov		r9, 1
.loop:
	cmp		byte[rdi + r8], 32
	je		.iter
	cmp		byte[rdi + r8], 9
	je		.iter
	cmp		byte[rdi + r8], 10
	je		.iter
	cmp		byte[rdi + r8], 11
	je		.iter
	cmp		byte[rdi + r8], 12
	je		.iter
	cmp		byte[rdi + r8], 13
	je		.iter
	cmp		byte[rdi + r8], '+'
	je		.pos_r
	cmp		byte[rdi + r8], '-'
	je		.neg_r

.while:
	cmp		byte[rdi + r8], '0'
	jge		.check_sym
	jmp		.return

.continue:
	movzx	rcx, byte[rdi + r8]
	add		rax, rcx
	sub		rax, 48
	inc		r8
	cmp		byte[rdi + r8], 0
	jne		.multiply
.cont:
	jmp		.while

.iter:
	inc		r8
	jmp		.loop

.pos_r:
	inc		r8
	jmp		.while

.neg_r:
	inc		r8
	mov		r9, -1
	jmp		.while

.check_sym:
	cmp		byte[rdi + r8], '9'
	jle		.continue

.return:
	cmp		r9, 0
	jg		.pos_rax
	jl		.neg_rax

.neg_rax:
	push	rsi
	mov		rsi, rax
	xor		rax, rax
	sub		rax, rsi
	pop		rsi

.pos_rax:
	pop		rcx
	pop		r9
	pop		r8
	ret

.multiply:
	push	rdx
	push	rsi
	mov		rsi, rax
	xor		rdx, rdx
.mult:
	cmp		rdx, 9
	jl		.multloop
	pop		rsi
	pop		rdx
	jmp		.cont

.multloop:
	inc		rdx
	add		rax, rsi
	jmp		.mult