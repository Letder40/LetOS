#include <stddef.h>
#include <stdint.h>

#include "../include/interrupts.h"

#define KERNEL_CS 0x08 // kernel code segment selector
#define MAX_INTERRUPTS 256

const uint8_t KERNEL_TRAP = TRAP_GATE | DPL_KERNEL_MODE << 5 | 0x1 << 7;
const uint8_t USER_TRAP   = TRAP_GATE | DPL_USER_MODE   << 5 | 0x1 << 7;
const uint8_t KERNEL_INT  = INT_GATE  | DPL_KERNEL_MODE << 5 | 0x1 << 7;

typedef struct {
    uint16_t isr_low;        // interrupt service rutine addr low
    uint16_t gdt_selector;   // gdt code segment selector
    uint8_t reserved;        // always 0
    uint8_t gate_attributes; // 4bits gate type, 1b not used, 2b DPL, 1b present
    uint16_t isr_high;       // ... high
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
static idtr_t idtr;

__attribute__((noreturn))
void generic_isr() {
    __asm__ volatile ("cli; hlt");
    __builtin_unreachable();
}

void idt_set_descriptor(uint8_t index, void* isr, uint8_t gate_attributes) {
    idt_entry_t* idt_entry = &idt[index];

    idt_entry->isr_low = (uint32_t)isr & 0xFFFF; 
    idt_entry->gdt_selector = KERNEL_CS;
    idt_entry->reserved = 0;
    idt_entry->gate_attributes = gate_attributes;
    idt_entry->isr_high = (uint32_t)isr >> 16;
}

extern void keyboard_isr();

void load_idt() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * MAX_INTERRUPTS - 1;

    // load idt with generic interrupts
    for (int i = 0; i < MAX_INTERRUPTS; i++)
        idt_set_descriptor((uint8_t)i, (void*)&generic_isr, KERNEL_TRAP);

    idt_set_descriptor((uint8_t)33, (void*)&keyboard_isr, KERNEL_TRAP);
    
    __asm__ volatile ("lidt %0" :: "m"(idtr));
    __asm__ volatile ("sti");
}
