extern	_ft_strlen
extern	_ft_strcpy
extern	_malloc

global	_ft_strdup
section .text
_ft_strdup:
	push	rdi
	call	_ft_strlen
	mov		rbx, rdi
	mov		rdi, rax
	call	_malloc
	cmp		rax, 0
	je		.error
	pop		rdi
	mov		rdi, rax
	push	rsi
	mov		rsi, rbx
	call	_ft_strcpy
	pop		rsi
	ret

.error:
	mov		rdi, 0
	mov		rax, 0
	ret