; 32-bit entry is standard for gnu multiboot2
; so somehow, we have to setup a transition to x86_64 bit mode...
bits 32

global entry ; the entry point for the kernel.elf file

KERNEL_STACK_SIZE equ 4096  ; the kernels stack size in bytes
section .bss 
align 4                     ; align at 4 bytes
kernel_stack:               ; kernel stack header for later reference
  resb KERNEL_STACK_SIZE    ; reserve KERNEL_STACK_SIZE bytes in the executable for later use.

section .text ; start of the code section
align 8 ; align with 64 bit boundary (multiboot2 standard)
%include "multiboot_header.inc" ; info for the multiboot2 header.
align 4

extern kmain ; defined so that we can call it later

entry:
  ;mov eax, 0xCAFEBABE ; tells us that the operating system has initialized correctly
  ; initialize the stack
  mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the stack.
  ; jump to a c function
  call kmain
  cli
  hlt