
/* dummy source file for compatibility purposes */

#if defined(HAVE_CDEFS_H)
#include <sys/cdefs.h>
#endif

#ifndef __warn_references

#if defined(__GNUC__) && defined(HAS_GNU_WARNING_LONG)

#define __warn_references(sym, msg) \
	__asm__(".section .gnu" #sym ",\n\t.ascii \"" msg "\"\n\t.text");

#else
#define __warn_references(sym, msg) /* nothing */
#endif

#endif

#include "../inc/json_object.h"
#include <stdlib.h>
#include <unistd.h>
void print (void) {
    write(1, "\a", 1);
}

__warn_references(json_object_get, "Warning: please link against libjson-c instead of libjson");

/*        __asm__(".section .gnu.warning." __STRING(sym)  \
            " ; .ascii \"" msg "\" ; .text") */
