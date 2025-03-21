#!/bin/sh
set -e

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/letos.kernel isodir/boot/letos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "letos" {
	multiboot /boot/letos.kernel
}
EOF
grub-mkrescue -o letos.iso isodir
