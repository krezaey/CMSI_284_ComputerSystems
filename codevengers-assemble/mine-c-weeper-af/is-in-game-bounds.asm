			global	is_in_game_bounds

			section	.text
is_in_game_bounds:
			cmp	esi, 0			; esi = passed in int x
			jl false			; if the esi < 0, jump to the false section

			cmp edx, 0			; edx = passed in int y
			jl false			; if the edx < 0, jump to the false section

			mov rax, rdi		; rdi contains is_in_game_bounds, move that to rax
			mov eax, [rax]		; move the game width to eax

			cmp eax, esi		; compare width and x
			jle false			; if width <= x, jump to the false section

			mov	rax, rdi		; mov rdi once again to the rdx
			mov eax, [rax + 4]	; move the game heigh to eax

			cmp eax, edx		; compare height and y
			jle false			; if height <= y, jump to the false section

			jmp	true			; return true since all false cases are taken care of

true:
			mov	rax, 1
			ret

false:
			xor	rax, rax
			ret
