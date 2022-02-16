global entry ; the entry point for our kernel.elf file

; todo : move multiboot2 handling to separate file
MAGIC_NUMBER  equ 0xE85250D6    ; define the magic number constant
ARCHITECTURE  equ 0x0           ; i32 

section .text ; start of the code section
align 8 ; align with 64 bit boundary
multiboot_header:
  dd MAGIC_NUMBER
  dd ARCHITECTURE
  dd multiboot_header_end - multiboot_header ; header length
  dd -(MAGIC_NUMBER + ARCHITECTURE + (multiboot_header_end - multiboot_header)) ; the checksum
  ; the magic number plus the architexture plus the header length plus the checksum should be 0

  multiboot_tags:
  ; nothing yet, so terminate it
  dw 0x0
  dw 0x0
  dd 0x8
multiboot_header_end:
align 4

entry:
  mov eax, 0xCAFEBABE ; tells us that the operating system has initialized correctly
.loop:
  jmp .loop ; loops forever. basically so that we can inspect eax in bochs