; crt0.asm 
;  defines the entry point for c executables
;  
bits 64

section .text

global _start

extern main
extern exit

; default entry
_start:
    ; set up the end of the stack framed link list
    mov qword rbp, 0x0
    push qword rbp 
    push qword rbp 
    mov qword rbp, rsp

    ; we will need these in a moment to call main
    ; rsi = argv
    ; rdi = argc
    push qword rsi 
    push qword rdi

    ; prepare standard library
    ; call initialize_clib

    ; global constructors (run in c++ programs and before main is called)
    ; call _init

    ; restore argc and argv
    pop qword rdi
    pop qword rsi

    call main 

    mov dword edi, eax
    call exit