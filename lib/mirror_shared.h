#pragma once

#ifdef MIRROR_APP
#include <stdint_target.h>
#endif

#ifdef MIRROR_HOST
#include <stdint.h>
#endif

// Syscall IDs (The O(1) indices)
typedef enum {
    SYS_YIELD       = 0, // Maps to UVM32_SYSCALL_YIELD
    SYS_PUTC        = 1, // Maps to UVM32_SYSCALL_PUTC
    SYS_PRINTLN     = 2, // Maps to UVM32_SYSCALL_PRINTLN

    SYS_MAX_FUNCTIONS
} mirror_syscall_id_t;
