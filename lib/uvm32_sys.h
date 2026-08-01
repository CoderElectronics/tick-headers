#pragma once

// Common definitions used by both uvm32.c and any code running inside VM
#define UVM32_MEMORY_SIZE 16384

// System provided UVM32_SYSCALLs, start at 0x10000000
#define UVM32_SYSCALL_HALT          0x1000000
#define UVM32_SYSCALL_YIELD         0x1000001
#define UVM32_SYSCALL_STACKPROTECT  0x1000002

// Address of External RAM, when offered by host
#define UVM32_EXTRAM_BASE 0x10000000
