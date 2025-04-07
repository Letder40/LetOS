.PHONY: all config headers build clean iso qemu source-env all

SCRIPTS = ./.build_scripts
SYSTEM_HEADER_PROJECTS = libc kernel
PROJECTS = libc kernel

MAKE_CONFIG = config.mk

-include $(MAKE_CONFIG)

$(MAKE_CONFIG): $(SCRIPTS)/config.sh
	@echo "Generating $(MAKE_CONFIG)..."
	@bash $(SCRIPTS)/config.sh

config:
	@echo "Regenerating $(MAKE_CONFIG)..."; \
	bash $(SCRIPTS)/config.sh; \

headers: $(MAKE_CONFIG)
	mkdir -p $(SYSROOT)
	for PROJECT in $(SYSTEM_HEADER_PROJECTS); do \
		(cd $$PROJECT && DESTDIR=$(SYSROOT) $(MAKE) install-headers); \
	done

build: headers
ifeq ($(DEBUG), true)
	echo "#define _DEBUG true"  > kernel/include/kernel/debug.h
else
	echo "#define _DEBUG false" > kernel/include/kernel/debug.h
endif

	for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && DESTDIR=$(SYSROOT) $(MAKE) install); \
	done

iso: build
	bash $(SCRIPTS)/iso.sh

qemu: iso
	qemu-system-$(ARCH) -cdrom letos.iso -monitor stdio

clean:
	for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && $(MAKE) clean); \
	done
	rm -rf sysroot isodir letos.iso
