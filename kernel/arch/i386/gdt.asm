bits 32

global load_gdtr
global load_data_segs
global load_code_seg

; load_gdtr - installs our global descriptor table.
;
; stack: [esp + 4] the gdtr value
; 		 [esp    ] the return code
;

load_gdtr:
    lgdt [esp + 4] ; load the gdt with our gdt ptr
    ret

; load_data_segs - sets the data segments to the right offset
; 
; stack: [esp + 4] the offset value
;        [esp    ] the reture code
load_data_segs:
    ; c calling convention
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8] ; now the offset value is at the stack pointer + 8 bc we just pushed ax
    mov ds, ax 
    mov ss, ax 
    mov es, ax
    mov fs, ax 
    mov gs, ax
    
    mov esp, ebp
    pop ebp
    ret

; farjumps to fix the code segment to the correct value.
; stack: 
;        [esp    ] the return value

load_code_seg:
    jmp 0x8:load_code_seg_ret
load_code_seg_ret:
    ret