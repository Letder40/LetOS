#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stdint.h>

void idt_set_descriptor(uint8_t, void*, uint8_t);
void load_idt(void);

#endif
