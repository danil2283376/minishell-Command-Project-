global _ft_strcpy
section .text
_ft_strcpy:
	push	rcx
	mov		rcx, 0
.loop:
	mov		al, byte[rsi + rcx]
	mov		byte [rdi + rcx], al
	cmp		byte [rsi + rcx], 0
	je		.return
	inc		rcx
	jmp		.loop

.return:
	pop		rcx
	mov		rax, rdi
	ret
