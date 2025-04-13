#ifndef CDEFS_H
#define CDEFS_H

#include <stddef.h>

#if __STDC_HOSTED__ == 0
#define __is_kernel__
#else
#define __is_libc__
#endif

#endif
