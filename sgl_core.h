// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#ifndef __SGL_CORE_H
#define __SGL_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define SGL_FORMAT_STRING_BUFFERSIZE (128)

typedef enum {
    SGL_MONO_BLACK = 0,
    SGL_MONO_WHITE = 1,
    SGL_MONO_INVERT = 2,
} sgl_mono_color_t;

typedef enum {
    SGL_DIR_UP = 0,
    SGL_DIR_DOWN,
    SGL_DIR_LEFT,
    SGL_DIR_RIGHT,
} sgl_dir_t;

#define SGL_DIR_DEFAULT SGL_DIR_UP

/**
 * alignment:
 *
 *     up_left           up_center           up_right
 *             +-------------+-------------+
 *             |                           |
 *             |                           |
 * left_center +        center(x,y)        + right_center
 *             |                           |
 *             |                           |
 *             +-------------+-------------+
 *   down_left          down_center          down_right
 */

typedef enum {
    SGL_ALIGN_UP_LEFT = 0,
    SGL_ALIGN_UP_RIGHT,
    SGL_ALIGN_DOWN_LEFT,
    SGL_ALIGN_DOWN_RIGHT,
    SGL_ALIGN_CENTER,
    SGL_ALIGN_UP_CENTER,
    SGL_ALIGN_DOWN_CENTER,
    SGL_ALIGN_LEFT_CENTER,
    SGL_ALIGN_RIGHT_CENTER,
} sgl_align_t;

#define SGL_ALIGN_DEFAULT SGL_ALIGN_UP_LEFT

typedef enum {
    SGL_ROTATE_0 = 0,
    SGL_ROTATE_90,
    SGL_ROTATE_180,
    SGL_ROTATE_270,
} sgl_rotate_t;

#define SGL_ROTATE_DEFAULT SGL_ROTATE_0

typedef struct {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} sgl_rect_t;

typedef struct {
    void *buffer;
    uint32_t buffer_size;
    uint32_t hor_res;
    uint32_t ver_res;
    uint32_t max_x;
    uint32_t max_y;
    uint32_t offset_x;
    uint32_t offset_y;
    uint32_t max_fps;
    uint32_t fcount;
    uint32_t ticks;
    sgl_rect_t visible;
    sgl_rect_t invalidate;
    sgl_rotate_t rotate;
    void (*paint)(void);
    void (*flush)(void *buffer, uint32_t buffer_size);
    void (*draw_pixel)(int32_t x, int32_t y, uint32_t color);
} sgl_screen_t;

extern sgl_screen_t *active_screen;

int sgl_init(sgl_screen_t *screen, void *buffer, uint32_t buffer_size,
             uint32_t hor_res, uint32_t ver_res);
void sgl_set_screen(sgl_screen_t *screen);
void sgl_handler(void);
void sgl_set_buffer(sgl_screen_t *screen, void *buffer, uint32_t buffer_size);
void sgl_set_paint(sgl_screen_t *screen, void (*paint)());
void sgl_set_flush(sgl_screen_t *screen,
                   void (*flush)(void *buffer, uint32_t buffer_size));
void sgl_set_draw_pixel(sgl_screen_t *screen,
                        void (*draw_pixel)(int32_t x, int32_t y,
                                           uint32_t color));
void sgl_set_visible(sgl_screen_t *screen, int32_t left, int32_t top,
                     int32_t right, int32_t bottom);
void sgl_set_screen_rotation(sgl_screen_t *screen, sgl_rotate_t rotate);
uint32_t sgl_get_fcount(sgl_screen_t *screen);
void sgl_reset_fcount(sgl_screen_t *screen);
void sgl_clear_screen(sgl_screen_t *screen, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif
