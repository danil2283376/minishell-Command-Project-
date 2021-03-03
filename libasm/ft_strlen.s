global _ft_strlen

section	.text
_ft_strlen:
	mov rax, 0
.loop:
	cmp	byte[rdi + rax], 0
	je	.return
	inc	rax
	jmp	.loop
.return:
	ret
