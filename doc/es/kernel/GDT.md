# GDT
---

La GDT es una tabla global de descriptores interna de la CPU en la arquitectura x86 que sirve para definir propiedades sobre los segmentos que esta leyendo.

## Introducción

### ¿Que son los segmentos?
Los segmentos son secciones lógicamente contiguas de memoria, estos segmentos pueden tener propiedades especificas incluso el comportamiento del procesador puede cambiar segun estas propiedades.

### Registros de segmento 
Los registros de segmento (segment register) son registros que apuntan a un indice de la GDT, esto permite asignar propiedades a un segmento leyendo la entrada a la que apunta los registros de segmento.

**Todos los registros de segmento:**
+ **CS**: Apunta al segmento de codigo
+ **DS**: Apunta al segmento para datos generales
+ **SS**: Apunta al segmento para datos en operaciones relacionados el stack
+ **ES**: Apunta al segmento para datos en operaciones relacionados con strings
+ **FS**: Extra
+ **GS**: Extra

## Implementando la GDT
Para implementar la GDT he ampliado el codigo del arranque para definir y cargar la GDT antes de pasarle el control al kernel

Definición de la gdt:

```asm
.set KERNEL_CODE_FLAGS, 0b10011010  
.set KERNEL_DATA_FLAGS, 0b10010010

.set USER_CODE_FLAGS, 0b11111010
.set USER_DATA_FLAGS, 0b11110010

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
```

### Cargar la GDT
La carga de la GDT se realiza mediante una instrucción especifica llamada ```lgdt```, esta necesita como argumento la dirección de memoria de un descriptor de gdt, que es una estructura de datos que contiene el limite hasta donde leer la GDT y la dirección de memoria desde la que se define la GDT:

```asm
gdt_descriptor:
    .word gdt_end - gdt - 1 # GDT limit
    .long gdt # GDT base
```

#### Recargar los registros de segmento
Es necesario recargar los registros de segmento para que apunten a la entrada de la GDT inical. Cabe destacar que justo despues de cargar la GDT y recargar los registros se le pasara el control al kernel por lo que es lógico cargar los registros en este momento a las entradas de modo kernel.
En este caso el indice para datos en modo kernel es 0x10 y para codigo el 0x0x08.

```asm
.section .text
.code32
.global _start

.type update_segments_registers, @function
update_segments_registers:
    mov $0x10, %ax # index of kernel mode data segment
    # data
    mov %ax, %ds # data segment reg
    mov %ax, %es # extra segment reg
    mov %ax, %fs # extra segment reg
    mov %ax, %gs # extra segment reg
    mov %ax, %ss # stack segment reg
    # code
    ljmp $0x08, $.kernel # reload code segment ...

.type _start, @function
_start:
    # ESP is the register that points to the stack 
    movl $stack_top, %esp

    # load gdt
    lgdt [gdt_descriptor]
    jmp update_segments_registers

    .kernel:
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

El registro de segmento de codigo es critico y las unicas operaciones que pueden alterarlo sin generar problemas son jmp, call entre otras es por esto que lo mejor es usar un long jump para saltar temporalmente a la dirección de la entrada de codigo de la GDT es CS actualizará su valor y directamente saltar al kernel
