.intel_syntax noprefix

# memory address that where this boot sector is expected to be loaded */
.org 0x7c00

.include "./utils/print_string.s"

.section .text

/* Print messgage */
mov bx, offset init_message
call print_string

jmp .

.section .data

.init_message: 
   .ascii "booting LetOS..."
   .byte 0

# padding hasta 510 bytes
.section .bss
    .space 510 - (. - 0x7c00)

.section .data
    .word 0xaa55 # magic number for boot sector recognition 2bytes (1 word)
