#pragma once

#ifdef MIRROR_APP

#include "uvm32_sys.h"
#include <stdbool.h>
#include "stdint_target.h"

typedef uint32_t size_t;
typedef int32_t ssize_t;
typedef uint32_t uintptr_t;

void *memcpy(void *dst, const void *src, int len);
void *memset(void *buf, int c, int len);
void *memmove(void *dest, const void *src, size_t len);

static uint32_t syscall(uint32_t id, uint32_t param1, uint32_t param2) {
    register uint32_t a0 asm("a0") = (uint32_t)(param1);
    register uint32_t a1 asm("a1") = (uint32_t)(param2);
    register uint32_t a2 asm("a2");
    register uint32_t a7 asm("a7") = (uint32_t)(id);

    asm volatile (
        "ecall"
        : "=r"(a2) // output
        : "r"(a7), "r"(a0), "r"(a1) // input
        : "memory"
    );
    return a2;
}

#define NULL 0
#define syscall_cast(id, p1, p2) syscall((uint32_t)id, (uint32_t)p1, (uint32_t)p2)
#define yield(x)        syscall_cast(UVM32_SYSCALL_YIELD, x, 0)

extern char _estack;

static void stackprotect(void) {
    syscall_cast(UVM32_SYSCALL_STACKPROTECT, &_estack, 0);
}

void *memcpy(void *dst, const void *src, int len) {
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (len--) {
        *d++ = *s++;
    }
    return dst;
}

void *memset(void *buf, int c, int len) {
    uint8_t *b = (uint8_t *)buf;
    while (len--) {
        *b++ = (uint8_t)c;
    }
    return buf;
}

void *memmove(void *dest, const void *src, size_t len) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;

    if (d == s || len == 0) {
        return dest;
    }

    if (d < s) {
        while (len--) {
            *d++ = *s++;
        }
    } else {
        d += len;
        s += len;
        while (len--) {
            *(--d) = *(--s);
        }
    }
    return dest;
}

#endif
