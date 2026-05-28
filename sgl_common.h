// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#ifndef __SGL_COMMON_H
#define __SGL_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_rotate_point(int32_t *x, int32_t *y);
void sgl_rotate_rect(int32_t *x, int32_t *y, int32_t *w, int32_t *h);
int sgl_clip_line(int32_t *start, int32_t *len, int32_t min, int32_t max);
void sgl_align(int32_t *x, int32_t *y, int32_t w, int32_t h, sgl_align_t align);

static inline void sgl_set_rect(sgl_rect_t *rect, int32_t left, int32_t top,
                                int32_t right, int32_t bottom) {
    rect->left = left;
    rect->top = top;
    rect->right = right;
    rect->bottom = bottom;
}

static inline int sgl_check_rect(int32_t left, int32_t top, int32_t right,
                                 int32_t bottom) {
    if (left > active_screen->visible.right ||
        right < active_screen->visible.left ||
        top > active_screen->visible.bottom ||
        bottom < active_screen->visible.top)
        return -1;
    return 0;
}

static inline void sgl_draw_hpixel(int32_t x, int32_t y, int32_t len,
                                   uint32_t color) {
    int32_t x1 = x + len;
    for (len = (len > 0) ? 1 : -1; x != x1; x += len)
        active_screen->draw_pixel(x, y, color);
}

static inline void sgl_draw_vpixel(int32_t x, int32_t y, int32_t len,
                                   uint32_t color) {
    int32_t y1 = y + len;
    for (len = (len > 0) ? 1 : -1; y != y1; y += len)
        active_screen->draw_pixel(x, y, color);
}

void sgl_draw_circle_section(int32_t xc, int32_t yc, int32_t r,
                             int32_t offset_x, int32_t offset_y,
                             uint32_t color);
void sgl_draw_filled_circle_section(int32_t xc, int32_t yc, int32_t r,
                                    int32_t offset_x, int32_t offset_y,
                                    uint32_t color);
void sgl_draw_ellipse_section(int32_t xc, int32_t yc, int32_t rx, int32_t ry,
                              uint32_t color);
void sgl_draw_filled_ellipse_section(int32_t xc, int32_t yc, int32_t rx,
                                     int32_t ry, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
