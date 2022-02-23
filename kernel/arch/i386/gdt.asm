bits 32

global load_gdtr

; load_gdtr - installs our global descriptor table.
;
; stack: [esp + 4]
; 		 [esp    ] the return code
;

load_gdtr:
    lgdt [esp + 4] ; load the gdt with our gdt ptr
    ret