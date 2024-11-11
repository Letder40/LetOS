print_string:
   pusha
   mov ah, 0x0e
   next_it:
      mov al, [bx]
      cmp al, 0
      int 0x10
      je end
      add bx, 1
      jmp next_it

end: 
   popa
   ret
