#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define check(cond) \
        do { \
            if (!(cond)) { \
            printf(ASNI_FMT("Assertion fail at %s:%d\n", ASNI_FG_RED), __FILE__, __LINE__); \
            halt(0xbadbad); \
            } \
        } while (0)


#endif