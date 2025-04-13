#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stdint.h>

void idt_set_descriptor(uint8_t, void*, uint8_t);
void load_idt(void);

void pic_init(void);
void irq_unmask(uint8_t);

#endif
