#include <stdint.h>

#include <letos/tty.h>
#include <letos/gdt.h>
#include <letos/interrupts.h>
#include <letos/keymaps.h>

extern void kernel_shell();

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

    kernel_shell(); 
}
