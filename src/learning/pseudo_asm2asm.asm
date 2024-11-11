;  mov bx , 30
;  if (bx <= 4) {
;  mov al , ’A’
;  } else if (bx < 40) {
;  mov al , ’B’
;  } else {
;  mov al , ’C’
;  }

[org 0x7c00]

mov bx, 45
cmp bx, 4
jle le_4
cmp bx, 40
jl l_40
jmp else

return_here:
mov ah, 0x0e ;int=10/ah=0x0e -> BIOS tele-type output
int 0x10 ; print the character in al

jmp $ ; INF LOOP

le_4: 
   mov al, 'A'
   jmp return_here
l_40:
   mov al, 'B'
   jmp return_here
else:
   mov al, 'C'
   jmp return_here

times 510 -($-$$) db 0
dw 0xaa55
