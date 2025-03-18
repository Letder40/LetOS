.intel_syntax noprefix

.section .text

print_string:
    pusha
    mov ah, 0x0e

loop:
    mov al, [bx]
    cmp al, 0
    int 0x10
    je end
    add bx, 1
    jmp loop

end:
    popa
    ret
