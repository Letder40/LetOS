# GDT constants

# Flags 

# 1bit: present
# 2bit: privilege_mode (00 kernel mode - 11 user mode)
# 1bit: segment_type (code/data or system)
# 1bit: is_excutable
# 1bit: direction (grows up: 0, grows down: 1)
# 1bit: is_writeable
# 1bit: asccessed

.set KERNEL_CODE_FLAGS, 0b10011010  
.set KERNEL_DATA_FLAGS, 0b10010010

.set USER_CODE_FLAGS, 0b11111010
.set USER_DATA_FLAGS, 0b11110010

# Granularity

# 1bit: 4kb_pages
# 1bit: size (1: 32-bit (stack|instructions), 0: 16-bit(stack|instructions)) 
# 1bit: long_mode (1: 64-bit, 0: 32-bit) 
# 1bit: reserved (always 0)
# 4bit: upper 4-bit of limit

.set GRANULARITY, 0b11001111


.section .rodata
gdt:
    # Null descriptor
    .word 0, 0
    .byte 0, 0, 0, 0

    # Kernel mode #

    # Code segment
    .word 0xffff, 0
    .byte 0
    .byte KERNEL_CODE_FLAGS
    .byte GRANULARITY
    .byte 0

    # Data segment
    .word 0xffff, 0
    .byte 0
    .byte KERNEL_DATA_FLAGS
    .byte GRANULARITY
    .byte 0

    # User mode #

    # Code segment
    .word 0xffff, 0
    .byte 0
    .byte USER_CODE_FLAGS
    .byte GRANULARITY
    .byte 0

    # Data segment
    .word 0xffff, 0
    .byte 0
    .byte USER_DATA_FLAGS
    .byte GRANULARITY
    .byte 0
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt - 1 # GDT limit
    .long gdt # GDT base

.section .text
.code32
.global load_gdt
update_segments_registers:
    mov $0x10, %ax # index of kernel mode data segment
    # data
    mov %ax, %ds # data segment reg
    mov %ax, %es # extra segment reg
    mov %ax, %fs # extra segment reg
    mov %ax, %gs # extra segment reg
    mov %ax, %ss # stack segment reg
    # code
    ljmp $0x08, $rt # reload code segment ...
rt: ret

.type load_gdt, @function
load_gdt:
    lgdt [gdt_descriptor]
    jmp update_segments_registers
