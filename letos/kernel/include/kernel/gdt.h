#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#include <stdint.h>

#define KERNEL_CS 0x08
#define KERNEL_DS 0x10

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtr_t;

extern gdtr_t gdt_register;
extern void load_gdt(void);

#endif
