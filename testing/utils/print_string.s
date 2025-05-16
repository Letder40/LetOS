.att_syntax
.code16

print_string:
    pusha

    movb $0x0e, %ah

loop:
    movb (%bx), %al
    cmpb $0, %al
    je end
    int $0x10
    addw $1, %bx
    jmp loop

end:
    popa
    ret
