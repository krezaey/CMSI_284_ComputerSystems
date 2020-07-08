;-------------------------------------------------------------------------------------------
; Function that takes in two arguments <directoryName> <fileName> and creates
; a directory and file with the passed in user arguments.
; However, the prank is 2 files are created with names with a message to the user.
;-------------------------------------------------------------------------------------------
global main

section .text
main:
     cmp rdi, 3                         ; compares number of arguments, must have have 2
     jne args_error                     ; jump to the error handling if arguments insufficient

     mov rax, 83                        ; system call to make a folder
     mov rdi, pranked                   ; taking 1st arg for sys call arg, creating dir with name
     mov rsi, 777q                      ; indicating standard folder creation
     syscall                            ; os to make the folder

     mov rax, 85                        ; system call to make a file
     mov rdi, pranked1                  ; creating file with prank!
     mov rsi, 700q                      ; indicating standard file creation
     syscall                            ; os to make the file

     mov rax, 85                        ; system call to make a file
     mov rdi, pranked2                  ; creating file with prank!
     mov rsi, 700q                      ; indicating standard file creation
     syscall                            ; os to make the file

     mov rax, 1                         ; system call for write
     mov rdi, 1                         ; file handle 1 for stdout
     mov rsi, completion                ; address of string to output 
     mov rdx, 52                        ; number of bytes for message
     syscall                            ; os to do the write
     jmp exit                           ; jump to the exit section

args_error: 
     mov rax, 1                         ; system call for write
     mov rdi, 1                         ; file handle 1 for stdout
     mov rsi, error_arguments           ; address of string to output
     mov rdx, 50                        ; number of bytes for message
     syscall                            ; os to do the write
     jmp exit                           ; jump to the exit section
     
exit:
     mov rax, 60                        ; system call for exit
     xor rdi, rdi                       ; exit code
     syscall                            ; os to exit


section .data
completion: db "Your folder and file has successfully been created.", 10
error_arguments: db "This program requires two command line arguments.", 10, 0
pranked1: db "You thought you could name this file.", 0
pranked2: db "But you can't.", 0
pranked: db "PRANKED!", 0

