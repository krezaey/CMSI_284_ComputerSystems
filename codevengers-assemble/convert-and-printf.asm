global	main
			extern	atoi
			extern	printf
			extern	puts

			section	.text
main:
			cmp	rdi, 2
			jne	incorrectArgumentCount

			mov	rdi, [rsi + 8]		; atoi(string_to_convert) <--- first parameter in rdi
			call	atoi			; Result will be in rax (calling convention!).

			mov	rdi, resultFormat	; printf(resultFormat, number) <--- args in rdi then rsi
			mov	rsi, rax		; Result of atoi goes to rsi now.
			xor	rax, rax		; printf is special: needs rax to be 0.
			call	printf

			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

			section	.data
incorrectArgumentCountMessage:
			db	"One argument is needed for conversion to a number.", 0

resultFormat:		db	"Here it is: %d", 10, 0
