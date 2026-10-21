#pragma once

#ifdef MIRROR_APP
#include <stdint_target.h>
#endif

#ifdef MIRROR_HOST
#include <stdint.h>
#endif

// Syscall IDs
typedef enum {
    SYS_YIELD = 0,
    SYS_PUTC = 1,
    SYS_PRINTLN = 2,

    // LCD Primitives
    SYS_LCD_ROTATE_POINT,
    SYS_LCD_DRAW_FAST_LINE,
    SYS_LCD_DRAW_RECT,
    SYS_LCD_FILL_RECT,
    SYS_LCD_DRAW_CIRCLE,
    SYS_LCD_FILL_CIRCLE,
    SYS_LCD_DRAW_ROUND_RECT,
    SYS_LCD_FILL_ROUND_RECT,
    SYS_LCD_FILL_RECT_PATTERN,
    SYS_LCD_DRAW_RECT_ROTATED,
    SYS_LCD_DRAW_CHAR,
    SYS_LCD_DRAW_CHAR_LC,
    SYS_LCD_DRAW_FONT,
    SYS_LCD_DRAW_FONT_LC,
    SYS_LCD_GET_FONT_BOUNDS,
    SYS_LCD_GET_FONT_BOUNDS_LC,
    SYS_LCD_DRAW_BITMAP,
    SYS_LCD_GET_FONT_MIRROR_ICONS12,
    SYS_LCD_GET_FONT_ORG_01,
    SYS_LCD_UPDATE,
    SYS_LCD_CLEAR,
    SYS_LCD_SET_PIXEL,

    SYS_MSLEEP,

    // system services
    SYS_EXT_RTC_GET_TIME,
    SYS_SETTINGS_TIME_IS_24H,
    SYS_PMIC_GET_CHARGE_STATUS,
    SYS_PMIC_GET_BATTERY_STATUS,
    SYS_SENSING_BARO_MEASURE,
    SYS_MOTION_TRACKER_GET_STEPS,
    SYS_MOTION_TRACKER_STEPS_ENABLED,
    SYS_MOTION_TRACKER_SLEEP_ENABLED,
    SYS_MOTION_TRACKER_GET_SLEEP_STATS,
    SYS_HAPTICS_PLAY,

    SYS_MAX_FUNCTIONS
} mirror_syscall_id_t;

// --- LCD Command Structures ---
typedef struct {
    int16_t x0;
    int16_t y0;
    int16_t angleDeg;
} ffi_lcd_rotate_pt_cmd_t;

typedef struct {
    int x0, y0, x1, y1, color;
} ffi_lcd_line_cmd_t;

typedef struct {
    int x, y, w, h, color;
} ffi_lcd_rect_cmd_t;

typedef struct {
    int x, y, r, color;
} ffi_lcd_circle_cmd_t;

typedef struct {
    int x, y, w, h, r, color;
} ffi_lcd_round_rect_cmd_t;

typedef struct {
    int x, y, w, h;
} ffi_lcd_pattern_cmd_t;

typedef struct {
    int cx, cy, w, h, angle, color;
} ffi_lcd_rot_rect_cmd_t;

typedef struct {
    int x, y, color;
    uint8_t size;
    unsigned char c;
    uint32_t font_ptr;
} ffi_lcd_char_cmd_t;

typedef struct {
    int x, y, color;
    uint8_t size;
    uint32_t font_ptr;
} ffi_lcd_font_cmd_t;

typedef struct {
    int x, y;
    uint8_t size;
    uint32_t font_ptr;
    int x1, y1, w, h; // Output bounds
} ffi_lcd_font_bounds_cmd_t;

typedef struct {
    uint32_t font_ptr;
} ffi_lcd_get_font_cmd_t;

typedef struct {
    int x, y, color;
} ffi_lcd_set_pixel_cmd_t;

typedef struct {
    int x, y, color;
    uint8_t w, h;
} ffi_lcd_bitmap_cmd_t;

typedef struct {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday;
} ffi_rtc_get_time_cmd_t;

typedef struct {
    int charging, error, vbus_present;
} ffi_pmic_charge_status_cmd_t;

typedef struct {
    int voltage_mv, percent, rate_mpct_per_hr;
} ffi_pmic_battery_status_cmd_t;

typedef struct {
    int pressure_pa, temperature_c, altitude_m;
} ffi_baro_sample_cmd_t;

typedef struct {
    uint32_t sleep_start_utc, uncertain_start_utc;
    int sleep_len_m, deep_len_m;
} ffi_sleep_stats_cmd_t;

typedef struct {
    uint8_t seq_regs[8];
} ffi_haptics_play_cmd_t;
