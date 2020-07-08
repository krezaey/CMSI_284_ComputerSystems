			global	main
			extern	puts
			extern	sscanf
			extern	printf
			extern	emit_utf_8

			section	.text
main:
			cmp 	rdi, 2					; check if there is at least 1 argument
			jl		argumentsError			; jump to the argument error section is value < 1 passed arg
			
			push 	rdi						; save registers that is being used for loop
			push	rsi						; save registers that is being used for loop
			sub 	rsp, 8					; must align stack before call
			jmp 	loop					; jump to the loop section where args are being iterated

checking_args_to_emit: 
			push 	rdi						; save registers that is being used for loop
			push 	rsi						; save registers that is being used for loop
			sub 	rsp, 8					; must align stack before call
			
			mov		rdi, [rsi]				; move the code_point_string into the rdi
			mov 	r12, rdi				; move the code_point_string into r12 for later
			mov		rsi, codePointFormat	; moving the format string into the second arg
			mov		rdx, codePoint			; moving the actual code
			call	sscanf					; sscanf(code_point_string, "U+%6X", &code_point)

			cmp 	rax, 1					; check if the scan is successful
			jne 	incorrect_format		; if scan is wrong, jump to the incorrect_format section

			mov 	rdi, [codePoint]		; move the code point into the rdi
			call	emit_utf_8				; emit_utf_8(codePoint)

			jmp		loop					; go back to the loop

loop:
			add		rsp, 8					; restore the %rsp to pre-aligned value
			pop 	rsi						; restore registers 
			pop		rdi						; restore registers

			add 	rsi, 8					; point to next argument
			dec 	rdi						; count down
			jnz 	checking_args_to_emit	; if not done, keep going
			jmp		output_result			; if done, go to final section where new line printed

incorrect_format:
			mov 	rdi, incorrectFormat	; move the string formatter into the rdi
			mov		rsi, r12				; move the code point string arg into rsi
			xor		rax, rax				; only needs to be done for printf
			call	printf					; printf(incorrectFormat, code_point_string)
			jmp		loop					; go back to the loop

output_result:
			mov 	rdi, new_line			; puts a new line into the rdi
			xor		rax, rax				; only needs to be done for printf
			call	printf					; printf(new_line)
			ret								; finally return from the function

argumentsError:		mov	rdi, argumentsRequiredMessage
			call	puts

			mov	rdi, argumentDescription
			call	puts

			xor	rax, rax
			inc	rax
			ret

			section	.data
			; The following definitions are here to get you started and to standardize
			; error messages but of course, feel free to define more as needed.
argumentsRequiredMessage:
			db	"This program requires one or more command line arguments,", 0
argumentDescription:	db	"one for each code point to encode as UTF-8.", 0
incorrectFormat:	db	"(%s incorrect format)", 0
codePointFormat:	db	"U+%6X", 0
new_line:		db "", 10

			section	.bss
codePoint:		resb	8			; The code point from sscanf should go here.
