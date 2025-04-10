#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#define TRAP_GATE 0xE
#define INT_GATE 0xF

#define DPL_KERNEL_MODE 0x0
#define DPL_USER_MODE 0x3

void idt_set_descriptor(uint8_t, void*, uint8_t);

void irq_unmask(uint8_t);

#define ISR_WRAPPER(isr_name, handler)                                         \
    void isr_name(void) {                                                      \
        asm volatile("pusha\n\t"                                               \
                     "call *%0\n\t"                                            \
                     "movb $0x20, %%al\n\t"                                    \
                     "outb %%al, $0x20\n\t"                                    \
                     "popa\n\t"                                                \
                     "iret\n\t"                                                \
                     :                                                         \
                     : "r"(handler)                                            \
                     : "eax");                                                 \
    }

#endif
