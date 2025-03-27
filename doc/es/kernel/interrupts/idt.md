# Interrupts
---

## IDT
La IDT es la tabla de descriptores de interrupciones, esta tabla es una estructura interna de la cpu que permite localizar un Inturrupt Service Routine (Rutina de servicio de interrupción) con respecto a una interrupción especifica siempre que tenga una entrada en el IDT.

## Entrada de la IDT

Cada entrada ocupa 64 bits en total y sus campos son:

1. **isr_low**: los 4bits menos significativos de la dirección de memoria de la ISR a llamar para esta interrupción
2. **GDT selector**: el indice del segmento de código de kernel
3. **reserved**: es siempre 0
4. **gate_attributes**: Este campo define el tipo de puerta usada para la entrada de la IDT, adémas del nivel de privilegio desde el cual la interrupción estará disponible.
5. **isr_high**: los 4bits más significativos de la dirección de memoria de una ISR


```c
typedef struct {
    uint16_t isr_low; // interrupt service rutine addr low
    uint16_t gdt_selector; // gdt code segment selector
    uint8_t reserved; // always 0
    uint8_t gate_attributes; // 4bits gate type, 1b not used, 2b DPL, 1b present
    uint16_t isr_high; // ... high
}__attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

```

## Tipos de gates
1. Trap: usada para exepciones de software.
2. Inturrupt: usada para interrupciones de hardware.

## Cargar la IDT
Para cargar la IDT se usa una instrucción especial en x86, esta el lidt y espera como argumento idtr (el descriptor de la tabla de interrupciones)

```c
typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idtr_t;

static idtr_t idtr;

void load_idt() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * MAX_INTERRUPTS - 1;

    // load idt with generic interrupts
    for (int i = 0; i < MAX_INTERRUPTS; i++)
        idt_set_descriptor((uint8_t)i, (void*)&generic_isr, KERNEL_TRAP);
    
    __asm__ volatile ("lidt %0" :: "m"(idtr));
    __asm__ volatile ("sti");
}
```

Este codigo setea todas las 256 interrupciones con un ISR génerico, las entradas deberán de ser editadas en el futuro siempre que se quiera cargar un ISR espécifico para la interrupción que se quiere manejar.
```c
__attribute__((noreturn))
void generic_isr() {
    __asm__ volatile ("cli; hlt");
    __builtin_unreachable();
}
```

