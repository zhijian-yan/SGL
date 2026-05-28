// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#include "sgl_line.h"
#include "sgl_common.h"

void sgl_draw_point(int32_t x, int32_t y, uint32_t color) {
    if (sgl_check_rect(x, y, x, y))
        return;
    sgl_rotate_point(&x, &y);
    active_screen->draw_pixel(x, y, color);
}

void sgl_draw_hline(int32_t x, int32_t y, int32_t len, uint32_t color) {
    if (y < active_screen->visible.top || y > active_screen->visible.bottom)
        return;
    if (sgl_clip_line(&x, &len, active_screen->visible.left,
                      active_screen->visible.right))
        return;
    sgl_rotate_point(&x, &y);
    switch (active_screen->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_hpixel(x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_vpixel(x, y, len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_hpixel(x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_vpixel(x, y, -len, color);
        break;
    }
}

void sgl_draw_vline(int32_t x, int32_t y, int32_t len, uint32_t color) {
    if (x < active_screen->visible.left || x > active_screen->visible.right)
        return;
    if (sgl_clip_line(&y, &len, active_screen->visible.top,
                      active_screen->visible.bottom))
        return;
    sgl_rotate_point(&x, &y);
    switch (active_screen->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_vpixel(x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_hpixel(x, y, -len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_vpixel(x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_hpixel(x, y, len, color);
        break;
    }
}

void sgl_draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                   uint32_t color) {
    int32_t dx, dy, sx, sy, err;
    sgl_rotate_point(&x0, &y0);
    sgl_rotate_point(&x1, &y1);
    dx = x1 - x0;
    dy = y1 - y0;
    sx = 1, sy = 1;
    if (dx < 0) {
        dx = -dx;
        sx = -1;
    }
    if (dy < 0) {
        dy = -dy;
        sy = -1;
    }
    if (dx > dy) {
        for (err = dx >> 1; x0 != x1; x0 += sx) {
            sgl_draw_point(x0, y0, color);
            err -= dy;
            if (err < 0) {
                y0 += sy;
                err += dx;
            }
        }
    } else {
        for (err = dy >> 1; y0 != y1; y0 += sy) {
            sgl_draw_point(x0, y0, color);
            err -= dx;
            if (err < 0) {
                x0 += sx;
                err += dy;
            }
        }
    }
    //    sgl_draw_point(x1, y1, color);
}
