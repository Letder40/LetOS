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
string/strlen.o \

# Hosted objects
HOSTED_OBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREE_OBJS) \
$(HOSTED_OBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a, to early for libc.a
BINARIES=libk.a

.PHONY: all clean install install-headers install-libs

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

%.o: %.c
	$(CC) -MD -c -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS) $<

%.o: %.S
	$(CC) -MD -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

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
