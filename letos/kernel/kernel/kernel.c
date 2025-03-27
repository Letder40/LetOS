#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>

void kernel_main(void) {
    terminal_initialize();

    load_gdt();
    terminal_writestring("[GDT] Global descriptor table loaded\n");
    load_idt();
    terminal_writestring("[IDT] Interrupt descriptor table loaded\n");

    terminal_writestring(BANNER);
}
