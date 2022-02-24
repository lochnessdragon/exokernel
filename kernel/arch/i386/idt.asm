bits 32
global load_idtr
global enable_interrupts
global disable_interrupts
global gen_interrupt

; install_idt - installs our interrupt descriptor table.
; stack: [esp + 4]
; 		 [esp    ] the return code
;
load_idtr:
 	lidt 	[esp + 4]  ; loads the interrupt descriptor table with our idt
	ret

; enable_interrupts - enables the idt and idt handling
enable_interrupts:
	sti 
	ret

; disable_interrupts - disables the idt and idt handling
disable_interrupts:
	cli
	ret

; gen_interrupt - generates a test interrupt
; stack: [ esp + 4 ]  interrupt to generate
;		 [ esp     ]  return address
gen_interrupt:
	mov 	al, byte [esp+4]
	mov 	byte [genint+1], al 
	jmp  	genint
genint:
	int 	0
	ret
