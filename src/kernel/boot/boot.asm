; boot.asm ;
; Main entry point for kernel ;
; Written by Harry Rigg ;

; For the multiboot
MBALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC+FLAGS)

; Grub needs to see this in order to boot us
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Lets setup our stack
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:

; Kernel entry point
section .text
global _start
_start:
	mov esp, stack_top	; Move our stack in
	push ebx
	extern kernel_main	; Located in kernel.c
	call kernel_main	; Lets jump to C code
	cli			; Clear interrupts
	hlt			; Halt
	pop ebx
.stub:
	hlt			; Halt
	jmp .stub		; Jump back here again, a infinite loop
