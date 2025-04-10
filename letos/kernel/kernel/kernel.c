#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <stdio.h>

extern char input_buffer[255];

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring(BANNER);

    load_gdt();
    kernel_debug("[GDT] Global descriptor table loaded\n");
    load_idt();
    kernel_debug("[IDT] Interrupt descriptor table loaded\n");

    pic_init();
    kernel_debug("[PIC MASTER] PIC REMMAPED TO 0x20\n");
    kernel_debug("[PIC SLAVE]  PIC REMMAPED TO 0x28\n");
    irq_unmask(1);
    kernel_debug("[IRQ 1] keyboard INITIALIZED\n");

    while (1) {
        printf("test");
        asm volatile ("hlt");
    }
}
