# Multiboot constants
.set ALIGN,     1<<0                # Align loaded modules on page boundaries
.set MEMINFO,   1<<1                # memmory map
.set FLAGS,     ALIGN | MEMINFO     # Multiboot flags
.set MAGIC,     0x1BADB002          # Number defined by multiboot standard for header recognition
.set CHECKSUM,  -(MAGIC + FLAGS)    # Number defined by multiboot standard for header recognition

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Set esp & stack
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB for the stack
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    # ESP is the register that points to the stack 
    movl $stack_top, %esp

    call load_gdt

    call kernel_main

    # disable interuptions
    cli
    # Infinite loop: 
1:  hlt
    # wait for interuptions
    # check if interruption bypass cli && go back to hlt
    jmp 1b

.size _start, . - _start # set size for start simmbol, current position - start
