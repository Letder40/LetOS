/* memory address where this boot sector is expected to be loaded */
.org 0x7c00

#include "utils/print_string.s"

.section .text

/* Print message */
movw $init_message, %bx
call print_string

call kernel_main

jmp .

.section .data

init_message: 
    .ascii "booting LetOS..."
    .byte 0

/* Padding hasta 510 bytes */
.section .bss
    . = 0x7c00 + 510

.section .data
    .word 0xaa55   /* Magic number for boot sector recognition */

