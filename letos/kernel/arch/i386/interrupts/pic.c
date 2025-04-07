#include "../include/io.h"

// PIC constants
#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC2_COMMAND PIC2

#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)

// Initialization Command Words

// ICW1
// 7-5: (RESERVED)
// 4:   1 (init indicator)
// 3:   1 = level triggered, 0 = edge triggered
// 2:   interval (deprectaed always 0) 
// 1:   1 = SINGLE PIC, 0 = CASCADE
// 0:   1 = ICW4 is present

#define ICW1_ICW4           0x01
#define ICW1_SINGLE         0x02
#define ICW1_INTERVAL4      0x04
#define ICW1_LEVEL_TRIGG    0x08
#define ICW1_INIT           0x10

// ICW2: offsets
#define ICW2_PIC1_OFFSET    0x20 // 32 - 39 IDT
#define ICW2_PIC2_OFFSET    0x28 // 40 - 47 IDT
// ICW3: cascade settings

// ICW4
// 7-5: (RESERVED)
// 4:   1 = fully nested, 0 = normal
// 3:   1 = BUFFERED MASTER (Additonals int lines by additonal hardware componenet) 
// 2:   1 = BUFFERED SLAVE ... 
// 1:   1 = AUTO EOI
// 0:   1 = 8086, 0 = MCS-80/85

#define ICW4_FULLY_NESTED   0x01
#define ICW4_BUFFER_MASTER  0x02
#define ICW4_BUFFER_SLAVE   0x04
#define ICW4_AUTO_EOI       0x08
#define ICW4_8086           0x10

void pic_init() {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, ICW2_PIC1_OFFSET);
    io_wait();
    outb(PIC2_DATA, ICW2_PIC2_OFFSET);
    io_wait();

    outb(PIC1_DATA, 0b000100); // IRQ2
    io_wait();
    outb(PIC2_DATA, 2); // connected to IRQ2
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, 0xff);
	outb(PIC2_DATA, 0xff);
}

void irq_unmask(uint8_t irq) {
    if (irq > 15) return;

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}
