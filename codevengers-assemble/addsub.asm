			global	main
			extern	atoi
			extern	strlen			; The specific externs that you will need
			extern	strncmp			; depend on your implementation; edit this
			extern	printf			; list as necessary.
			extern	puts

			section	.text
main:
			cmp	rdi, 4
			jne	incorrectArgumentCount

			mov 	r12, [rsi + 8] 	; move first arg into r12, this is the first num
			mov		r13, [rsi + 16] ; move second arg into r13, this is the operator
			mov 	r14, [rsi + 24]	; move the third arg into r14, this is the second num

			push	r12				; The necessity of these will depend on implementation;
			push	r13				; this is mainly a reminder to preserve any callee-save
			push	r14				; registers that you might use.
			push 	r15

			mov		rdi, r12		; moving the first num into the rdi
			call 	atoi			; atoi(first_num)
			mov		r12, rax		; move the converted num back into r12

			mov		rdi, r14		; moving the second num into the rdi
			call	atoi			; atoi(second_num)
			mov		r14, rax		; move the converted num back into r14

			jmp 	operator_check	; jump to the operator check section

operator_check: 
			mov 	rdi, r13		; moving the operator arg into the rdi for checks
			call	strlen			; strlen(operator_arg)
			cmp 	rax, 1			; is the length of the operator passed in 1? 
			jne		incorrectOperator 	; jump to incorrect operator if operator arg's len != 1

			mov 	rdi, r13		; moving the operator arg into the rdi for more checks
			mov		rsi, plusOperator	; moving the plusOperator into the rsi for comparison
			mov 	rdx, 1			; length of the plusOperator
			call 	strncmp			; strncmp(argv[1], plusOperator, 1)
			cmp 	rax, 0			; do the strings match?
			je 		add_handler		; jump to the addition handler section if the strings are the same

			mov		rsi, minusOperator	; moving the plusOperator into the rsi for comparison
			mov 	rdx, 1			; length of the plusOperator
			call 	strncmp			; strncmp(argv[1], plusOperator, 1)
			cmp 	rax, 0			; do the strings match?
			je 		sub_handler		; jump to the addition handler section if the strings are the same

add_handler: 
 			mov     rax, r12    ; move the first argument into the rax
            add     rax, r14    ; add the r12 and r14 summands
            mov     r15, rax    ; store the sum in r15
            jmp     format_result       ; jump to the format section for the result printing

sub_handler: 
			mov     rax, r12    ; move the first argument into the rax
            sub     rax, r14    ; subtract r12 and r14
            mov     r15, rax    ; store the difference in r15
            jmp     format_result       ; jump to the format section for the result printing

format_result:
			mov     rdi, resultFormat 	; move the format string into the first argument 
            mov     rsi, r12    ; first number to be added into first %d
            mov     rdx, r13    ; operator string in the %s
            mov     rcx, r14    ; second number result into second %d    
			mov 	r8,  r15	; operation total into the third %d
            xor     rax, rax    ; only needed for printf, rax must be 0
            call    printf      ; printf(format, r12, r13, r14, r15) 
			jmp		finished	; jump to the finished section

finished:	
			pop r15
			pop	r14
			pop	r13
			pop	r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

incorrectOperator:
			mov	rdi, incorrectOperatorMessage
			call	puts
			jmp	finished

			section	.data
plusOperator:		db	"+", 0
minusOperator:		db	"-", 0
resultFormat:		db	"%d %s %d = %d", 10, 0

incorrectArgumentCountMessage:
			db	"To use this program, either enter <number> + <number> or <number> - <number>.", 0

incorrectOperatorMessage:
			db	"This program only recognizes + or -.", 0
