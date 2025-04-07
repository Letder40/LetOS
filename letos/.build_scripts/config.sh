#!/bin/bash
set -e

export MAKE=${MAKE:-make}
export TARGET=${TARGET:-$(./.build_scripts/target.sh)}
export ARCH=$(./.build_scripts/target2arch.sh $TARGET)

export AR=${TARGET}-ar
export AS=${TARGET}-as
export CC=${TARGET}-gcc

export PREFIX=/usr
export BOOTDIR=/boot
export LIBDIR=$PREFIX/lib
export INCLUDEDIR=$PREFIX/include
export CFLAGS='-O2 -g'

export SYSROOT="$(pwd)/sysroot"
export DEBUG="false"

CC="$CC --sysroot=$SYSROOT"
if echo "$TARGET" | grep -Eq -- '-elf($|-)'; then
  CC="$CC -isystem=$INCLUDEDIR"
fi
export CC

cat > config.mk <<EOF
SYSROOT = $SYSROOT
TARGET = $TARGET
ARCH = $ARCH
MAKE = $MAKE
CC = $CC
AR = $AR
AS = $AS
PREFIX = $PREFIX
BOOTDIR = $BOOTDIR
LIBDIR = $LIBDIR
INCLUDEDIR = $INCLUDEDIR
CFLAGS = $CFLAGS
DEBUG = $DEBUG
EOF
