; Demostrating addressing

   mov ah, 0x0e ; int 10/aah = 0eh -> scrolling teletype BIOS routine

   ;third attempt
   mov bx, the_secret
   add bx, 0x7c00 ; adding start of the memory reserved to boot_sector to our offset
   mov al, [bx]
   int 0x10

   jmp $

the_secret:
   db "X"

times 510-($-$$) db 0
dw 0xaa55
