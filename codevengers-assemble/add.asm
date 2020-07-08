			global	main
			extern	atoi
			extern	printf
			extern	puts

			section	.text
main:
			cmp	rdi, 3
			jne	incorrectArgumentCount

            mov     r12, [rsi + 8]      ; move the first arg into r12
            mov     r13, [rsi + 16]     ; move the second arg into r13

			push	r12			; The necessity of these will depend on implementation;
			push	r13			; this is mainly a reminder to preserve any callee-save
			push	r14			; registers that you might use.

			mov     rdi, r12    ; move the first argument to be converted
            call    atoi        ; atoi(string_to_convert)
            mov     r12, rax    ; move it back to r12

            mov     rdi, r13    ; move the second arg to be converted
            call    atoi        ; atoi(string_to_convert)
            mov     r13, rax    ; move it back to r13
            jmp     addition_handler    ; jump to the addition section for the actual calculation to occur

addition_handler:  
            mov     rax, r12    ; move the first argument into the rax
            add     rax, r13    ; add the r12 and r13 summands
            mov     r14, rax    ; store the sum in r14
            jmp     format_result       ; jump to the format section for the result printing

format_result:
            mov     rdi, format ; move the format string into the first argument 
            mov     rsi, r12    ; first number to be added into first %d
            mov     rdx, r13    ; second number to be added into second %d
            mov     rcx, r14    ; final sum result into third %d    
            xor     rax, rax    ; only needed for printf, rax must be 0
            call    printf      ; printf(format, r12, r13, r14) 

			pop	r14
			pop	r13
			pop	r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

			section	.data
incorrectArgumentCountMessage:
			db	"Two arguments are needed in order to perform addition.", 0
format:			db	"%d + %d = %d", 10, 0

