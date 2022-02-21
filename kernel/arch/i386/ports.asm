bits 32

; asm subroutinues with a C ABI
global outportb
global inportb

; sends a byte (second argument) to the port (first argument)
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outportb:
    mov dx, word [esp+4]    ; move the address of the I/O port into the dx register
    mov al, byte [esp+8]    ; move the data to be sent into the al register

    out dx, al           ; send the data to the I/O port
    ret

; returns a byte read from the port (first argument)
; stack: [esp + 4] the I/O port
; 		 [esp    ] return address
inportb:
    ;push dx 				; save registers
	mov dx, [esp + 4] 		; move the address of the I/O port into the dx register.
	in ax, dx 				; read the byte from the I/O port
	;pop dx					; load registers
    ret