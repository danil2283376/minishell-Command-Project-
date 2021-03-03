global _fn_space

section .text
_fn_space:
	xor		rax, rax
.loop:
	cmp		byte[rdi + rsi], 32
	jne		.return
	inc		rsi
	jmp		.loop
.return:
	mov		rax, rsi
	ret