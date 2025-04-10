KERNEL_ARCH_CFLAGS=
KERNEL_ARCH_LDFLAGS=
KERNEL_ARCH_LIBS=

KERNEL_ARCH_OBJS=\
$(ARCHDIR)/boot/boot.o \
$(ARCHDIR)/boot/gdt.o \
$(ARCHDIR)/interrupts/idt.o \
$(ARCHDIR)/interrupts/pic.o \
$(ARCHDIR)/hardware/keyboard/keyboard.o \
$(ARCHDIR)/video/tty.o \
