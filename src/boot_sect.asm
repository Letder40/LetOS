;
; Boot sector 
;

[org 0x7c00] ; memory address that where this boot sector is expected to be loaded

%include "./utils/print_string.asm"

; Print messgage
mov bx, init_message
call print_string

jmp $

init_message: 
   db "booting LetOS...",0 ;NULL terminated "string"

; padding

times 510-($-$$) db 0

dw 0xaa55 ; magic number for boot sector recognition 2bytes (1 word)
