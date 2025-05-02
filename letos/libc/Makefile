include ../config.mk

LDFLAGS?=
LIBS?=

INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
LIBK_CFLAGS:=$(CFLAGS)

ARCHDIR=arch/$(ARCH)

include $(ARCHDIR)/config.mk

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)

# Freestanding objects
FREE_OBJS=\
$(ARCH_FREEOBJS) \
stdio/printf.o \
stdio/putchar.o \
string/strlen.o \
string/strtok.o \
string/strcmp.o \
string/memcpy.o \
string/memset.o \
stdlib/atoi.o \

# Hosted objects
HOSTED_OBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREE_OBJS) \
$(HOSTED_OBJS) \

LIBK_OBJS=$(FREE_OBJS:.o=.libk.o)

#BINARIES=libc.a libk.a, to early for libc.a
BINARIES=libk.a

.PHONY: all clean install install-headers install-libs

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

%.libk.o: %.c
	$(CC) -MD -c -o $@ -std=gnu11 $(CFLAGS) $<

%.libk.o: %.S
	$(CC) -MD -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install-headers:
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(SYSROOT)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(SYSROOT)$(LIBDIR)
	cp $(BINARIES) $(SYSROOT)$(LIBDIR)

install: install-headers install-libs

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
