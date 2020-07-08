;-------------------------------------------------------------------------------------------
; Function that takes in two arguments <directoryName> <fileName> and creates
; a directory and file with the passed in user arguments.
;-------------------------------------------------------------------------------------------
global main
section .text
main:
     cmp rdi, 3                         ; compares number of arguments, must have have 2
     jne args_error                     ; jump to the error handling if arguments insufficient

     mov r12, [rsi +0x08]               ; moving the first arg (folder name) to r12
     mov r13, [rsi +0x10]               ; moving the second arg (file name) to r13  

     mov rax, 83                        ; system call to make a folder
     mov rdi, r12                       ; taking 1st arg for sys call arg, creating dir with name
     mov rsi, 777q                      ; indicating standard folder creation
     syscall                            ; os to make the folder

     mov rax, 85                        ; system call to make a file
     mov rdi, r13                       ; taking 2nd arg for sys call arg, creating file with name
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