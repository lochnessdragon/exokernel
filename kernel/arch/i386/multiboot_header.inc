; defines the multiboot header for the i386 architecture
%include "multiboot2.inc"

multiboot_header:
  dd M2_MAGIC
  dd M2_ARCH_I386
  dd multiboot_header_end - multiboot_header ; header length
  dd -(M2_MAGIC + M2_ARCH_I386 + (multiboot_header_end - multiboot_header)) ; the checksum
  ; the magic number plus the architexture plus the header length plus the checksum should be 0

  multiboot_tags:
  ; nothing yet, so terminate it
  tag_terminate:
  dw M2_TAG_TERMINATE
  dw 0x0
  dd tag_terminate_end - tag_terminate
  tag_terminate_end:
multiboot_header_end: