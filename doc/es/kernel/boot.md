# Bootloader (Estándar multiboot)
---

El bootloader es una pieza de software fundamental en cualquier sistema operativo este se encargará de pasarle el control posteriormente al kernel para que el sistema operativo pueda funcionar.

## Estandar multiboot
El estandar multiboot define una interfaz de operación entre el boot loader y el kernel y permitira que un bootloader pueda leer operar interactuar con el sistema.

### Header mutiboot y llamada al kernel

```asm
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

    call kernel_main

    # disable interuptions
    cli
    # Infinite loop: 
1:  hlt
    # wait for interuptions
    # check if interruption bypass cli && go back to hlt
    jmp 1b

.size _start, . - _start # set size for start simmbol, current position - start
```

Es posible escribir un bootloader propio cosa que ya he hecho para tomar una primera toma de contacto pero nunca será mejor que un bootloader estandar que permita cargar el sistema operativo de manera eficiente y manejar multiples sistemas operativos.

### boot sector propio
Este tiene sintaxis de intel sin prefijar debido a que empecé con esta sintaxis en un principio, acabe cambiando a sintaxís de at&t pues es el estandar en GNU.

```asm
.intel_syntax noprefix

# memory address that where this boot sector is expected to be loaded */
.org 0x7c00

.include "./utils/print_string.s"

.section .text

/* Print messgage */
mov bx, offset init_message
call print_string

jmp .

.section .data

.init_message: 
   .ascii "booting LetOS..."
   .byte 0

# padding hasta 510 bytes
.section .bss
    .space 510 - (. - 0x7c00)

.section .data
    .word 0xaa55 # magic number for boot sector recognition 2bytes (1 word)
```

#### print string
Uso una interrupción especifica de la bios para poder imprimir texto por pantalla, esto solo es valido trabajando en Real Mode (16 bits), por lo que una vez se cargue el kernel todas las rutinas de la bios no estarán disponibles

```asm
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

```
