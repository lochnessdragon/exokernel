global entry ; the entry point for our kernel.elf file

section .text ; start of the code section
align 8 ; align with 64 bit boundary
%include "multiboot_header.inc"
align 4

entry:
  mov eax, 0xCAFEBABE ; tells us that the operating system has initialized correctly
.loop:
  jmp .loop ; loops forever. basically so that we can inspect eax in bochs