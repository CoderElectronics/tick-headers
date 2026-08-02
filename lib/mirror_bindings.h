/*
 * Split FFI bindings for Tick Engine host and VM side. These are in the same file for easy reference.
 */

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

static inline void mirror_lcd_rotate_point(int16_t *x0, int16_t *y0, int16_t angleDeg) {
    static ffi_lcd_rotate_pt_cmd_t cmd;
    cmd.x0 = *x0;
    cmd.y0 = *y0;
    cmd.angleDeg = angleDeg;
    syscall((uint32_t)SYS_LCD_ROTATE_POINT, (uint32_t)&cmd, 0);
    *x0 = cmd.x0; // Read back modified values from the static struct
    *y0 = cmd.y0;
}

static inline void mirror_lcd_draw_fast_line(int x0, int y0, int x1, int y1, int color) {
    static ffi_lcd_line_cmd_t cmd;
    cmd.x0 = x0; cmd.y0 = y0; cmd.x1 = x1; cmd.y1 = y1; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_FAST_LINE, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_rect(int x, int y, int w, int h, int color) {
    static ffi_lcd_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_RECT, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_fill_rect(int x, int y, int w, int h, int color) {
    static ffi_lcd_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_RECT, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_circle(int x0, int y0, int r, int color) {
    static ffi_lcd_circle_cmd_t cmd;
    cmd.x = x0; cmd.y = y0; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_CIRCLE, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_fill_circle(int x0, int y0, int r, int color) {
    static ffi_lcd_circle_cmd_t cmd;
    cmd.x = x0; cmd.y = y0; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_CIRCLE, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_round_rect(int x, int y, int w, int h, int r, int color) {
    static ffi_lcd_round_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_ROUND_RECT, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_fill_round_rect(int x, int y, int w, int h, int r, int color) {
    static ffi_lcd_round_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_ROUND_RECT, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_fill_rect_pattern(int x, int y, int w, int h, const uint8_t *pattern) {
    static ffi_lcd_pattern_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h;
    syscall((uint32_t)SYS_LCD_FILL_RECT_PATTERN, (uint32_t)&cmd, (uint32_t)pattern);
}

static inline void mirror_lcd_draw_rect_rotated(int cenX, int cenY, int w, int h, int angleDeg, int color) {
    static ffi_lcd_rot_rect_cmd_t cmd;
    cmd.cx = cenX; cmd.cy = cenY; cmd.w = w; cmd.h = h; cmd.angle = angleDeg; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_RECT_ROTATED, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_char(int x, int y, unsigned char c, const void *font, int color, uint8_t size) {
    static ffi_lcd_char_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.c = c; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_CHAR, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_char_lc(int x, int y, unsigned char c, const void *font, int color, uint8_t size) {
    static ffi_lcd_char_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.c = c; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_CHAR_LC, (uint32_t)&cmd, 0);
}

static inline void mirror_lcd_draw_font(int x, int y, const char *str, const void *font, int color, uint8_t size) {
    static ffi_lcd_font_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_FONT, (uint32_t)&cmd, (uint32_t)str); // Pass str via ARG1 for bounds checking
}

static inline void mirror_lcd_draw_font_lc(int x, int y, const char *str, const void *font, int color, uint8_t size) {
    static ffi_lcd_font_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_FONT_LC, (uint32_t)&cmd, (uint32_t)str);
}

static inline void mirror_lcd_get_font_bounds(const char *str, const void *font, int x, int y, uint8_t size, int *x1, int *y1, int *w, int *h) {
    static ffi_lcd_font_bounds_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.size = size;
    syscall((uint32_t)SYS_LCD_GET_FONT_BOUNDS, (uint32_t)&cmd, (uint32_t)str);
    *x1 = cmd.x1; *y1 = cmd.y1; *w = cmd.w; *h = cmd.h; // Read populated bounding box values
}

static inline void mirror_lcd_get_font_bounds_lc(const char *str, const void *font, int x, int y, uint8_t size, int *x1, int *y1, int *w, int *h) {
    static ffi_lcd_font_bounds_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.size = size;
    syscall((uint32_t)SYS_LCD_GET_FONT_BOUNDS_LC, (uint32_t)&cmd, (uint32_t)str);
    *x1 = cmd.x1; *y1 = cmd.y1; *w = cmd.w; *h = cmd.h;
}

static inline const void* mirror_lcd_get_font_mirror_icons12(void) {
    static ffi_lcd_get_font_cmd_t cmd;
    syscall((uint32_t)SYS_LCD_GET_FONT_MIRROR_ICONS12, (uint32_t)&cmd, 0);
    return (const void*)cmd.font_ptr;
}

static inline const void* mirror_lcd_get_font_org_01(void) {
    static ffi_lcd_get_font_cmd_t cmd;
    syscall((uint32_t)SYS_LCD_GET_FONT_ORG_01, (uint32_t)&cmd, 0);
    return (const void*)cmd.font_ptr;
}

static inline void mirror_msleep(int32_t ms) {
    syscall((uint32_t)SYS_MSLEEP, (uint32_t)ms, 0);
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

#include "lcd/lcd_prim.h"
#include "lcd/fonts/Org_01.h"
#include "lcd/fonts/Mirror_Icons12.h"

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

static void handle_lcd_rotate_point(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_rotate_pt_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_rotate_pt_cmd_t *cmd = (ffi_lcd_rotate_pt_cmd_t *)slice.ptr;

    // Pass pointers directly to the mapped VM memory. The VM app reads the modifications immediately.
    lcd_rotate_point(&cmd->x0, &cmd->y0, cmd->angleDeg);
}
REGISTER_FFI(SYS_LCD_ROTATE_POINT, handle_lcd_rotate_point);

static void handle_lcd_draw_fast_line(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_line_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_line_cmd_t *cmd = (ffi_lcd_line_cmd_t *)slice.ptr;
    lcd_draw_fast_line(cmd->x0, cmd->y0, cmd->x1, cmd->y1, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_FAST_LINE, handle_lcd_draw_fast_line);

static void handle_lcd_draw_rect(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_rect_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_rect_cmd_t *cmd = (ffi_lcd_rect_cmd_t *)slice.ptr;
    lcd_draw_rect(cmd->x, cmd->y, cmd->w, cmd->h, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_RECT, handle_lcd_draw_rect);

static void handle_lcd_fill_rect(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_rect_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_rect_cmd_t *cmd = (ffi_lcd_rect_cmd_t *)slice.ptr;
    lcd_fill_rect(cmd->x, cmd->y, cmd->w, cmd->h, cmd->color);
}
REGISTER_FFI(SYS_LCD_FILL_RECT, handle_lcd_fill_rect);

static void handle_lcd_draw_circle(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_circle_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_circle_cmd_t *cmd = (ffi_lcd_circle_cmd_t *)slice.ptr;
    lcd_draw_circle(cmd->x, cmd->y, cmd->r, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_CIRCLE, handle_lcd_draw_circle);

static void handle_lcd_fill_circle(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_circle_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_circle_cmd_t *cmd = (ffi_lcd_circle_cmd_t *)slice.ptr;
    lcd_fill_circle(cmd->x, cmd->y, cmd->r, cmd->color);
}
REGISTER_FFI(SYS_LCD_FILL_CIRCLE, handle_lcd_fill_circle);

static void handle_lcd_draw_round_rect(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_round_rect_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_round_rect_cmd_t *cmd = (ffi_lcd_round_rect_cmd_t *)slice.ptr;
    lcd_draw_round_rect(cmd->x, cmd->y, cmd->w, cmd->h, cmd->r, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_ROUND_RECT, handle_lcd_draw_round_rect);

static void handle_lcd_fill_round_rect(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_round_rect_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_round_rect_cmd_t *cmd = (ffi_lcd_round_rect_cmd_t *)slice.ptr;
    lcd_fill_round_rect(cmd->x, cmd->y, cmd->w, cmd->h, cmd->r, cmd->color);
}
REGISTER_FFI(SYS_LCD_FILL_ROUND_RECT, handle_lcd_fill_round_rect);

static void handle_lcd_fill_rect_pattern(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t cmd_slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_pattern_cmd_t));
    uvm32_slice_t pat_slice = uvm32_arg_getslice_fixed(vmst, evt, ARG1, 8); // Pattern size is fixed at 8 bytes
    if (!cmd_slice.ptr || !pat_slice.ptr) return;

    ffi_lcd_pattern_cmd_t *cmd = (ffi_lcd_pattern_cmd_t *)cmd_slice.ptr;
    lcd_fill_rect_pattern(cmd->x, cmd->y, cmd->w, cmd->h, (const uint8_t *)pat_slice.ptr);
}
REGISTER_FFI(SYS_LCD_FILL_RECT_PATTERN, handle_lcd_fill_rect_pattern);

static void handle_lcd_draw_rect_rotated(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_rot_rect_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_rot_rect_cmd_t *cmd = (ffi_lcd_rot_rect_cmd_t *)slice.ptr;
    lcd_draw_rect_rotated(cmd->cx, cmd->cy, cmd->w, cmd->h, cmd->angle, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_RECT_ROTATED, handle_lcd_draw_rect_rotated);

static void handle_lcd_draw_char(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_char_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_char_cmd_t *cmd = (ffi_lcd_char_cmd_t *)slice.ptr;
    lcd_draw_char(cmd->x, cmd->y, cmd->c, (const GFXfont *)cmd->font_ptr, cmd->color, cmd->size);
}
REGISTER_FFI(SYS_LCD_DRAW_CHAR, handle_lcd_draw_char);

static void handle_lcd_draw_char_lc(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_char_cmd_t));
    if (!slice.ptr) return;
    ffi_lcd_char_cmd_t *cmd = (ffi_lcd_char_cmd_t *)slice.ptr;
    lcd_draw_char_lc(cmd->x, cmd->y, cmd->c, (const GFXfont *)cmd->font_ptr, cmd->color, cmd->size);
}
REGISTER_FFI(SYS_LCD_DRAW_CHAR_LC, handle_lcd_draw_char_lc);

static void handle_lcd_draw_font(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_font_cmd_t));
    const char *str = uvm32_arg_getcstr(vmst, evt, ARG1); // Safely decodes string from ARG1 pointer
    if (!slice.ptr || !str) return;

    ffi_lcd_font_cmd_t *cmd = (ffi_lcd_font_cmd_t *)slice.ptr;
    lcd_draw_font(cmd->x, cmd->y, str, (const GFXfont *)cmd->font_ptr, cmd->color, cmd->size);
}
REGISTER_FFI(SYS_LCD_DRAW_FONT, handle_lcd_draw_font);

static void handle_lcd_draw_font_lc(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_font_cmd_t));
    const char *str = uvm32_arg_getcstr(vmst, evt, ARG1);
    if (!slice.ptr || !str) return;

    ffi_lcd_font_cmd_t *cmd = (ffi_lcd_font_cmd_t *)slice.ptr;
    lcd_draw_font_lc(cmd->x, cmd->y, str, (const GFXfont *)cmd->font_ptr, cmd->color, cmd->size);
}
REGISTER_FFI(SYS_LCD_DRAW_FONT_LC, handle_lcd_draw_font_lc);

static void handle_lcd_get_font_bounds(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_font_bounds_cmd_t));
    const char *str = uvm32_arg_getcstr(vmst, evt, ARG1);
    if (!slice.ptr || !str) return;

    ffi_lcd_font_bounds_cmd_t *cmd = (ffi_lcd_font_bounds_cmd_t *)slice.ptr;

    // Target struct memory is passed, results are naturally pulled back to VM on return
    lcd_get_font_bounds(str, (const GFXfont *)cmd->font_ptr, cmd->x, cmd->y, cmd->size,
                        &cmd->x1, &cmd->y1, &cmd->w, &cmd->h);
}
REGISTER_FFI(SYS_LCD_GET_FONT_BOUNDS, handle_lcd_get_font_bounds);

static void handle_lcd_get_font_bounds_lc(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_font_bounds_cmd_t));
    const char *str = uvm32_arg_getcstr(vmst, evt, ARG1);
    if (!slice.ptr || !str) return;

    ffi_lcd_font_bounds_cmd_t *cmd = (ffi_lcd_font_bounds_cmd_t *)slice.ptr;
    lcd_get_font_bounds_lc(str, (const GFXfont *)cmd->font_ptr, cmd->x, cmd->y, cmd->size,
                           &cmd->x1, &cmd->y1, &cmd->w, &cmd->h);
}
REGISTER_FFI(SYS_LCD_GET_FONT_BOUNDS_LC, handle_lcd_get_font_bounds_lc);

static void handle_lcd_get_font_mirror_icons12(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_get_font_cmd_t));
    if (!slice.ptr) return;

    ffi_lcd_get_font_cmd_t *cmd = (ffi_lcd_get_font_cmd_t *)slice.ptr;
    cmd->font_ptr = (uint32_t)&Mirror_Icons12;
}
REGISTER_FFI(SYS_LCD_GET_FONT_MIRROR_ICONS12, handle_lcd_get_font_mirror_icons12);

static void handle_lcd_get_font_org_01(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_get_font_cmd_t));
    if (!slice.ptr) return;

    ffi_lcd_get_font_cmd_t *cmd = (ffi_lcd_get_font_cmd_t *)slice.ptr;
    cmd->font_ptr = (uint32_t)&Org_01;
}
REGISTER_FFI(SYS_LCD_GET_FONT_ORG_01, handle_lcd_get_font_org_01);

static void handle_msleep(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    // Read ARG0 directly as a 32-bit integer
    int32_t ms = (int32_t)uvm32_arg_getval(vmst, evt, ARG0);

    k_msleep(ms);
}
REGISTER_FFI(SYS_MSLEEP, handle_msleep);

#endif
