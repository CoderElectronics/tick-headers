#pragma once

#include "mirror_target.h"
#include "mirror_shared.h"

#ifdef MIRROR_APP

/*
 * App side FFI
 *
 * these will be compiled into the app binary and used to transfer data to the host via syscalls
 */

static inline void mirror_putc(char c) {
    syscall((uint32_t)SYS_PUTC, (uint32_t)c, 0);
}

static inline void mirror_println(const char *str) {
    syscall((uint32_t)SYS_PRINTLN, (uint32_t)str, 0);
}

#endif

#ifdef MIRROR_HOST

/*
 * Host side FFI
 *
 * these will be compiled into the host binary and used to transfer data from the app via syscalls
 */

#include "mirror_bindings.h"
#include "tick_engine/tick_engine.h"
#include "tick_engine/uvm32/uvm32.h"
#include <zephyr/kernel.h>

static void handle_putc(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    char c = (char)uvm32_arg_getval(vmst, evt, ARG0);

    printk("%c", c);
}
REGISTER_FFI(SYS_PUTC, handle_putc);

static void handle_println(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    const char *str = uvm32_arg_getcstr(vmst, evt, ARG0);

    printk("%s\n", str);
}
REGISTER_FFI(SYS_PRINTLN, handle_println);

#endif
