;  mov bx , 30
;  if (bx <= 4) {
;  mov al , ’A’
;  } else if (bx < 40) {
;  mov al , ’B’
;  } else {
;  mov al , ’C’
;  }

[org 0x7c00]

return_here:
mov ah, 0x0e ;int=10/ah=0x0e -> BIOS tele-type output
mov al, 'f'
int 0x10 ; print the character in al

jmp return_here

jmp $ ; INF LOOP

times 510 -($-$$) db 0
dw 0xaa55



