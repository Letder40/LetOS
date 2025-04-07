#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>

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
    irq_unmask(0);
    kernel_debug("[IRQ 0] test INITIALIZED\n");

}
