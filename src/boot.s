.intel_syntax noprefix

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
# The stack grows downwards on x86
stack_bottom:
.skip 16384 # 16 KiB for the stack
stack_top:

.section .text
.global _start

_start:
    # ESP is the register that points to the stack 
    mov stack_top, esp

    call kernel_main

    cli # disable interuptions

    # Infinite loop: 
1:  hlt # wait for interuptions
    # if any interruption bypass cli go bask hlt
    jmp 1b

.size _start, . - _start # set size for start simmbol, current position - start
