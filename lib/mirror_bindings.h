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

static inline void putc(char c) {
    syscall((uint32_t)SYS_PUTC, (uint32_t)c, 0);
}

static inline void println(const char *str) {
    syscall((uint32_t)SYS_PRINTLN, (uint32_t)str, 0);
}

static inline void lcd_rotate_point(int16_t *x0, int16_t *y0, int16_t angleDeg) {
    static ffi_lcd_rotate_pt_cmd_t cmd;
    cmd.x0 = *x0;
    cmd.y0 = *y0;
    cmd.angleDeg = angleDeg;
    syscall((uint32_t)SYS_LCD_ROTATE_POINT, (uint32_t)&cmd, 0);
    *x0 = cmd.x0; // Read back modified values from the static struct
    *y0 = cmd.y0;
}

static inline void lcd_draw_fast_line(int x0, int y0, int x1, int y1, int color) {
    static ffi_lcd_line_cmd_t cmd;
    cmd.x0 = x0; cmd.y0 = y0; cmd.x1 = x1; cmd.y1 = y1; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_FAST_LINE, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_rect(int x, int y, int w, int h, int color) {
    static ffi_lcd_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_RECT, (uint32_t)&cmd, 0);
}

static inline void lcd_fill_rect(int x, int y, int w, int h, int color) {
    static ffi_lcd_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_RECT, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_circle(int x0, int y0, int r, int color) {
    static ffi_lcd_circle_cmd_t cmd;
    cmd.x = x0; cmd.y = y0; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_CIRCLE, (uint32_t)&cmd, 0);
}

static inline void lcd_fill_circle(int x0, int y0, int r, int color) {
    static ffi_lcd_circle_cmd_t cmd;
    cmd.x = x0; cmd.y = y0; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_CIRCLE, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_round_rect(int x, int y, int w, int h, int r, int color) {
    static ffi_lcd_round_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_ROUND_RECT, (uint32_t)&cmd, 0);
}

static inline void lcd_fill_round_rect(int x, int y, int w, int h, int r, int color) {
    static ffi_lcd_round_rect_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h; cmd.r = r; cmd.color = color;
    syscall((uint32_t)SYS_LCD_FILL_ROUND_RECT, (uint32_t)&cmd, 0);
}

static inline void lcd_fill_rect_pattern(int x, int y, int w, int h, const uint8_t *pattern) {
    static ffi_lcd_pattern_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.w = w; cmd.h = h;
    syscall((uint32_t)SYS_LCD_FILL_RECT_PATTERN, (uint32_t)&cmd, (uint32_t)pattern);
}

static inline void lcd_draw_rect_rotated(int cenX, int cenY, int w, int h, int angleDeg, int color) {
    static ffi_lcd_rot_rect_cmd_t cmd;
    cmd.cx = cenX; cmd.cy = cenY; cmd.w = w; cmd.h = h; cmd.angle = angleDeg; cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_RECT_ROTATED, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_char(int x, int y, unsigned char c, const void *font, int color, uint8_t size) {
    static ffi_lcd_char_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.c = c; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_CHAR, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_char_lc(int x, int y, unsigned char c, const void *font, int color, uint8_t size) {
    static ffi_lcd_char_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.c = c; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_CHAR_LC, (uint32_t)&cmd, 0);
}

static inline void lcd_draw_font(int x, int y, const char *str, const void *font, int color, uint8_t size) {
    static ffi_lcd_font_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_FONT, (uint32_t)&cmd, (uint32_t)str); // Pass str via ARG1 for bounds checking
}

static inline void lcd_draw_font_lc(int x, int y, const char *str, const void *font, int color, uint8_t size) {
    static ffi_lcd_font_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.color = color; cmd.size = size;
    syscall((uint32_t)SYS_LCD_DRAW_FONT_LC, (uint32_t)&cmd, (uint32_t)str);
}

static inline void lcd_get_font_bounds(const char *str, const void *font, int x, int y, uint8_t size, int *x1, int *y1, int *w, int *h) {
    static ffi_lcd_font_bounds_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.size = size;
    syscall((uint32_t)SYS_LCD_GET_FONT_BOUNDS, (uint32_t)&cmd, (uint32_t)str);
    *x1 = cmd.x1; *y1 = cmd.y1; *w = cmd.w; *h = cmd.h; // Read populated bounding box values
}

static inline void lcd_get_font_bounds_lc(const char *str, const void *font, int x, int y, uint8_t size, int *x1, int *y1, int *w, int *h) {
    static ffi_lcd_font_bounds_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.font_ptr = (uint32_t)font; cmd.size = size;
    syscall((uint32_t)SYS_LCD_GET_FONT_BOUNDS_LC, (uint32_t)&cmd, (uint32_t)str);
    *x1 = cmd.x1; *y1 = cmd.y1; *w = cmd.w; *h = cmd.h;
}

static inline void lcd_draw_bitmap(int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, int color) {
    static ffi_lcd_bitmap_cmd_t cmd;
    cmd.x = x;
    cmd.y = y;
    cmd.w = w;
    cmd.h = h;
    cmd.color = color;
    syscall((uint32_t)SYS_LCD_DRAW_BITMAP, (uint32_t)&cmd, (uint32_t)bitmap);
}

static inline const void* lcd_get_font_mirror_icons12(void) {
    static ffi_lcd_get_font_cmd_t cmd;
    syscall((uint32_t)SYS_LCD_GET_FONT_MIRROR_ICONS12, (uint32_t)&cmd, 0);
    return (const void*)cmd.font_ptr;
}

static inline const void* lcd_get_font_org_01(void) {
    static ffi_lcd_get_font_cmd_t cmd;
    syscall((uint32_t)SYS_LCD_GET_FONT_ORG_01, (uint32_t)&cmd, 0);
    return (const void*)cmd.font_ptr;
}

static inline void msleep(int32_t ms) {
    syscall((uint32_t)SYS_MSLEEP, (uint32_t)ms, 0);
}

static inline void lcd_update(void) {
    syscall((uint32_t)SYS_LCD_UPDATE, 0, 0);
}

static inline void lcd_clear(int color) {
    syscall((uint32_t)SYS_LCD_CLEAR, (uint32_t)color, 0);
}

static inline void lcd_set_pixel(int x, int y, int color) {
    static ffi_lcd_set_pixel_cmd_t cmd;
    cmd.x = x; cmd.y = y; cmd.color = color;
    syscall((uint32_t)SYS_LCD_SET_PIXEL, (uint32_t)&cmd, 0);
}

/* system service bindings */
struct rtc_time {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday;
};

struct pmic_charge_status {
    bool charging, error, vbus_present;
};

struct pmic_battery_status {
    int voltage_mv;
    int percent;
    int rate_mpct_per_hr;
};

struct sensing_baro_sample {
    int pressure_pa, temperature_c, altitude_m;
};

struct sleep_stats {
    uint32_t sleep_start_utc;
    uint32_t uncertain_start_utc;
    int sleep_len_m;
    int deep_len_m;
};

struct drv2605_rom_data {
    uint8_t seq_regs[8];
};

#define DRV2605_WAVEFORM_SEQUENCER_MAX 8
#define DRV2605_WAVEFORM_SEQUENCER_WAIT_MS(ms) (0x80 | ((ms) / 10))

static inline bool ext_rtc_get_time(struct rtc_time *time) {
    static ffi_rtc_get_time_cmd_t cmd;
    bool ok = syscall((uint32_t)SYS_EXT_RTC_GET_TIME, (uint32_t)&cmd, 0) != 0;
    if (ok) {
        time->tm_sec = cmd.tm_sec; time->tm_min = cmd.tm_min; time->tm_hour = cmd.tm_hour;
        time->tm_mday = cmd.tm_mday; time->tm_mon = cmd.tm_mon; time->tm_year = cmd.tm_year;
        time->tm_wday = cmd.tm_wday;
    }
    return ok;
}

static inline bool settings_time_is_24h(void) {
    return syscall((uint32_t)SYS_SETTINGS_TIME_IS_24H, 0, 0) != 0;
}

static inline int pmic_get_charge_status(struct pmic_charge_status *status) {
    static ffi_pmic_charge_status_cmd_t cmd;
    int ret = (int)syscall((uint32_t)SYS_PMIC_GET_CHARGE_STATUS, (uint32_t)&cmd, 0);
    if (ret == 0) {
        status->charging = cmd.charging; status->error = cmd.error;
        status->vbus_present = cmd.vbus_present;
    }
    return ret;
}

static inline int pmic_get_battery_status(struct pmic_battery_status *status) {
    static ffi_pmic_battery_status_cmd_t cmd;
    int ret = (int)syscall((uint32_t)SYS_PMIC_GET_BATTERY_STATUS, (uint32_t)&cmd, 0);
    if (ret == 0) {
        status->voltage_mv = cmd.voltage_mv; status->percent = cmd.percent;
        status->rate_mpct_per_hr = cmd.rate_mpct_per_hr;
    }
    return ret;
}

static inline int sensing_baro_measure(struct sensing_baro_sample *sample) {
    static ffi_baro_sample_cmd_t cmd;
    int ret = (int)syscall((uint32_t)SYS_SENSING_BARO_MEASURE, (uint32_t)&cmd, 0);
    if (ret == 0) {
        sample->pressure_pa = cmd.pressure_pa; sample->temperature_c = cmd.temperature_c;
        sample->altitude_m = cmd.altitude_m;
    }
    return ret;
}

static inline uint32_t motion_tracker_get_steps(void) {
    return syscall((uint32_t)SYS_MOTION_TRACKER_GET_STEPS, 0, 0);
}

static inline bool motion_tracker_steps_enabled(void) {
    return syscall((uint32_t)SYS_MOTION_TRACKER_STEPS_ENABLED, 0, 0) != 0;
}

static inline bool motion_tracker_sleep_enabled(void) {
    return syscall((uint32_t)SYS_MOTION_TRACKER_SLEEP_ENABLED, 0, 0) != 0;
}

static inline void motion_tracker_get_sleep_stats(struct sleep_stats *stats) {
    static ffi_sleep_stats_cmd_t cmd;
    syscall((uint32_t)SYS_MOTION_TRACKER_GET_SLEEP_STATS, (uint32_t)&cmd, 0);
    stats->sleep_start_utc = cmd.sleep_start_utc; stats->uncertain_start_utc = cmd.uncertain_start_utc;
    stats->sleep_len_m = cmd.sleep_len_m; stats->deep_len_m = cmd.deep_len_m;
}

static inline struct drv2605_rom_data haptics_effect_single(uint8_t num) {
    struct drv2605_rom_data data = { .seq_regs = { num, 0 } };
    return data;
}

static inline int haptics_play(const struct drv2605_rom_data *effect) {
    static ffi_haptics_play_cmd_t cmd;
    for (int i = 0; i < 8; i++) {
        cmd.seq_regs[i] = effect->seq_regs[i];
    }
    return (int)syscall((uint32_t)SYS_HAPTICS_PLAY, (uint32_t)&cmd, 0);
}

#endif

#ifdef MIRROR_HOST

/*
 * Host side FFI
 *
 * these will be compiled into the host binary and used to transfer data from the app via syscalls
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/rtc.h>
#include <errno.h>
#include <string.h>

#include "mirror_bindings.h"
#include "tick_engine/tick_engine.h"
#include "tick_engine/uvm32/uvm32.h"
#include "lcd/lcd_hal.h"
#include "lcd/lcd_prim.h"
#include "lcd/fonts/Org_01.h"
#include "lcd/fonts/Mirror_Icons12.h"
#include "ext_rtc/ext_rtc_hal.h"
#include "settings/settings_time.h"
#include "pmic/pmic_hal.h"
#include "sensing/sensing_hal.h"
#include "sensing/motion_tracker.h"
#include "haptics/haptics_hal.h"

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

static void handle_lcd_draw_bitmap(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t cmd_slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_bitmap_cmd_t));
    if (!cmd_slice.ptr) return;

    ffi_lcd_bitmap_cmd_t *cmd = (ffi_lcd_bitmap_cmd_t *)cmd_slice.ptr;

    uint32_t expected_bytes = (cmd->w * cmd->h + 7) / 8;

    uvm32_slice_t bmp_slice = uvm32_arg_getslice_fixed(vmst, evt, ARG1, expected_bytes);
    if (!bmp_slice.ptr) return;

    lcd_draw_bitmap(cmd->x, cmd->y, (const uint8_t *)bmp_slice.ptr, cmd->w, cmd->h, cmd->color);
}
REGISTER_FFI(SYS_LCD_DRAW_BITMAP, handle_lcd_draw_bitmap);

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

static void handle_lcd_update(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    lcd_update();
}
REGISTER_FFI(SYS_LCD_UPDATE, handle_lcd_update);

static void handle_lcd_clear(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    int color = (int)uvm32_arg_getval(vmst, evt, ARG0);
    lcd_clear(color);
}
REGISTER_FFI(SYS_LCD_CLEAR, handle_lcd_clear);

static void handle_lcd_set_pixel(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_lcd_set_pixel_cmd_t));
    if (!slice.ptr) return;

    ffi_lcd_set_pixel_cmd_t *cmd = (ffi_lcd_set_pixel_cmd_t *)slice.ptr;
    lcd_set_pixel(cmd->x, cmd->y, cmd->color);
}
REGISTER_FFI(SYS_LCD_SET_PIXEL, handle_lcd_set_pixel);

/* non-graphics based system services */
static void handle_ext_rtc_get_time(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_rtc_get_time_cmd_t));
    if (!slice.ptr) return;
    ffi_rtc_get_time_cmd_t *cmd = (ffi_rtc_get_time_cmd_t *)slice.ptr;
    struct rtc_time time;

    bool ok = ext_rtc_get_time(&time);
    if (ok) {
        cmd->tm_sec = time.tm_sec; cmd->tm_min = time.tm_min; cmd->tm_hour = time.tm_hour;
        cmd->tm_mday = time.tm_mday; cmd->tm_mon = time.tm_mon; cmd->tm_year = time.tm_year;
        cmd->tm_wday = time.tm_wday;
    }
    uvm32_arg_setval(vmst, evt, RET, ok ? 1 : 0);
}
REGISTER_FFI(SYS_EXT_RTC_GET_TIME, handle_ext_rtc_get_time);

static void handle_settings_time_is_24h(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_arg_setval(vmst, evt, RET, settings_time_is_24h() ? 1 : 0);
}
REGISTER_FFI(SYS_SETTINGS_TIME_IS_24H, handle_settings_time_is_24h);

static void handle_pmic_get_charge_status(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_pmic_charge_status_cmd_t));
    if (!slice.ptr) return;
    ffi_pmic_charge_status_cmd_t *cmd = (ffi_pmic_charge_status_cmd_t *)slice.ptr;
    struct pmic_charge_status status;

    int ret = pmic_get_charge_status(&status);
    if (ret == 0) {
        cmd->charging = status.charging; cmd->error = status.error;
        cmd->vbus_present = status.vbus_present;
    }
    uvm32_arg_setval(vmst, evt, RET, (uint32_t)ret);
}
REGISTER_FFI(SYS_PMIC_GET_CHARGE_STATUS, handle_pmic_get_charge_status);

static void handle_pmic_get_battery_status(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_pmic_battery_status_cmd_t));
    if (!slice.ptr) return;
    ffi_pmic_battery_status_cmd_t *cmd = (ffi_pmic_battery_status_cmd_t *)slice.ptr;
    struct pmic_battery_status status;

    int ret = pmic_get_battery_status(&status);
    if (ret == 0) {
        cmd->voltage_mv = status.voltage_mv; cmd->percent = status.percent;
        cmd->rate_mpct_per_hr = status.rate_mpct_per_hr;
    }
    uvm32_arg_setval(vmst, evt, RET, (uint32_t)ret);
}
REGISTER_FFI(SYS_PMIC_GET_BATTERY_STATUS, handle_pmic_get_battery_status);

/* float to a scaled integer, rounded to nearest */
static int ffi_scale(float value, float scale) {
    float scaled = value * scale;

    return (int)(scaled + (scaled < 0 ? -0.5f : 0.5f));
}

static void handle_sensing_baro_measure(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_baro_sample_cmd_t));
    if (!slice.ptr) return;
    ffi_baro_sample_cmd_t *cmd = (ffi_baro_sample_cmd_t *)slice.ptr;
    struct sensing_baro_sample sample;

    int ret = sensing_baro_measure(&sample);
    if (ret == 0) {
        cmd->pressure_pa = ffi_scale(sample.pressure_pa, 1.0f);
        cmd->temperature_c = ffi_scale(sample.temperature_c, 100.0f);
        cmd->altitude_m = ffi_scale(sample.altitude_m, 100.0f);
    }
    uvm32_arg_setval(vmst, evt, RET, (uint32_t)ret);
}
REGISTER_FFI(SYS_SENSING_BARO_MEASURE, handle_sensing_baro_measure);

static void handle_motion_tracker_get_steps(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_arg_setval(vmst, evt, RET, motion_tracker_get_steps());
}
REGISTER_FFI(SYS_MOTION_TRACKER_GET_STEPS, handle_motion_tracker_get_steps);

static void handle_motion_tracker_steps_enabled(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_arg_setval(vmst, evt, RET, motion_tracker_steps_enabled() ? 1 : 0);
}
REGISTER_FFI(SYS_MOTION_TRACKER_STEPS_ENABLED, handle_motion_tracker_steps_enabled);

static void handle_motion_tracker_sleep_enabled(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_arg_setval(vmst, evt, RET, motion_tracker_sleep_enabled() ? 1 : 0);
}
REGISTER_FFI(SYS_MOTION_TRACKER_SLEEP_ENABLED, handle_motion_tracker_sleep_enabled);

static void handle_motion_tracker_get_sleep_stats(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_sleep_stats_cmd_t));
    if (!slice.ptr) return;
    ffi_sleep_stats_cmd_t *cmd = (ffi_sleep_stats_cmd_t *)slice.ptr;
    struct sleep_stats stats;

    motion_tracker_get_sleep_stats(&stats);
    cmd->sleep_start_utc = (uint32_t)stats.sleep_start_utc;
    cmd->uncertain_start_utc = (uint32_t)stats.uncertain_start_utc;
    cmd->sleep_len_m = stats.sleep_len_m;
    cmd->deep_len_m = stats.deep_len_m;
}
REGISTER_FFI(SYS_MOTION_TRACKER_GET_SLEEP_STATS, handle_motion_tracker_get_sleep_stats);

static void handle_haptics_play(uvm32_state_t *vmst, uvm32_evt_t *evt) {
    uvm32_slice_t slice = uvm32_arg_getslice_fixed(vmst, evt, ARG0, sizeof(ffi_haptics_play_cmd_t));
    if (!slice.ptr) return;
    ffi_haptics_play_cmd_t *cmd = (ffi_haptics_play_cmd_t *)slice.ptr;

    /* the motor is an LRA and the driver's own trigger is used, whatever the VM asked for */
    struct drv2605_rom_data effect = {
        .library = DRV2605_LIBRARY_LRA,
        .trigger = DRV2605_MODE_INTERNAL_TRIGGER,
    };

    /* copy up to the first 0, an effect number the library does not have ends the sequence */
    for (int i = 0; i < 8; i++) {
        uint8_t entry = cmd->seq_regs[i];

        if (entry == 0 || (!(entry & 0x80) && entry > 123)) {
            break;
        }
        effect.seq_regs[i] = entry;
    }

    int ret = effect.seq_regs[0] ? haptics_play(&effect) : -EINVAL;
    uvm32_arg_setval(vmst, evt, RET, (uint32_t)ret);
}
REGISTER_FFI(SYS_HAPTICS_PLAY, handle_haptics_play);

#endif
