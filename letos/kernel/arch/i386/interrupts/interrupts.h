#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#define TRAP_GATE 0xE
#define INT_GATE 0xF

#define DPL_KERNEL_MODE 0x0
#define DPL_USER_MODE 0x3

const uint8_t KERNEL_TRAP = TRAP_GATE | DPL_KERNEL_MODE << 5 | 0x1 << 7;
const uint8_t USER_TRAP   = TRAP_GATE | DPL_USER_MODE   << 5 | 0x1 << 7;
const uint8_t KERNEL_INT  = INT_GATE  | DPL_KERNEL_MODE << 5 | 0x1 << 7;

void idt_set_descriptor(uint8_t, void*, uint8_t);

#endif
