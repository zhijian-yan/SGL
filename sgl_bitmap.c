// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#include "sgl_bitmap.h"
#include "sgl_common.h"
#include "sgl_line.h"

void sgl_show_mono_bitmap(sgl_screen_t *scr, int32_t x, int32_t y, int32_t w,
                          int32_t h, const uint8_t *bitmap, sgl_dir_t dir,
                          uint32_t color) {
    int32_t offset_x, offset_y, temp, index, i, j;
    uint32_t mask;
    switch (dir) {
    case SGL_DIR_UP:
        offset_x = x;
        offset_y = y;
        for (j = 0; j < h; ++j) {
            index = (j >> 3) * w;
            mask = 1 << (j & 7);
            temp = offset_y + j;
            for (i = 0; i < w; ++i)
                if ((bitmap[i + index] & mask))
                    sgl_draw_point(scr, offset_x + i, temp, color);
        }
        break;
    case SGL_DIR_RIGHT:
        offset_x = x + h - 1;
        offset_y = y;
        for (j = 0; j < h; ++j) {
            index = (j >> 3) * w;
            mask = 1 << (j & 7);
            temp = offset_x - j;
            for (i = 0; i < w; ++i)
                if ((bitmap[i + index] & mask))
                    sgl_draw_point(scr, temp, offset_y + i, color);
        }
        break;
    case SGL_DIR_LEFT:
        offset_x = x;
        offset_y = y + w - 1;
        for (j = 0; j < h; ++j) {
            index = (j >> 3) * w;
            mask = 1 << (j & 7);
            temp = offset_x + j;
            for (i = 0; i < w; ++i)
                if ((bitmap[i + index] & mask))
                    sgl_draw_point(scr, temp, offset_y - i, color);
        }
        break;
    case SGL_DIR_DOWN:
        offset_x = x + w - 1;
        offset_y = y + h - 1;
        for (j = 0; j < h; ++j) {
            index = (j >> 3) * w;
            mask = 1 << (j & 7);
            temp = offset_y - j;
            for (i = 0; i < w; ++i)
                if ((bitmap[i + index] & mask))
                    sgl_draw_point(scr, offset_x - i, temp, color);
        }
        break;
    }
}

void sgl_show_rgb565_bitmap(sgl_screen_t *scr, int32_t x, int32_t y, int32_t w,
                            int32_t h, const uint16_t *bitmap, sgl_dir_t dir) {
    int32_t dx = x, dy = y, bmp_w = w, bmp_h = h, temp, index, i, j;
    if (dir == SGL_DIR_UP || dir == SGL_DIR_DOWN) {
        if (sgl_clip_line(&x, &w, scr->visible.left, scr->visible.right))
            return;
        if (sgl_clip_line(&y, &h, scr->visible.top, scr->visible.bottom))
            return;
    } else {
        if (sgl_clip_line(&x, &h, scr->visible.left, scr->visible.right))
            return;
        if (sgl_clip_line(&y, &w, scr->visible.top, scr->visible.bottom))
            return;
    }
    dx = x - dx;
    dy = y - dy;
    x -= scr->offset_x;
    y -= scr->offset_y;
    switch (dir) {
    case SGL_DIR_UP:
        for (j = 0; j < h; ++j) {
            temp = y + j;
            index = (dy + j) * bmp_h;
            for (i = 0; i < w; ++i)
                scr->draw_pixel(scr, x + i, temp, bitmap[dx + i + index]);
        }
        break;
    case SGL_DIR_RIGHT:
        for (j = 0; j < h; ++j) {
            temp = x + j;
            index = ((bmp_h - 1) - (dx + j)) * bmp_w;
            for (i = 0; i < w; ++i)
                scr->draw_pixel(scr, temp, y + i, bitmap[dy + i + index]);
        }
        break;
    case SGL_DIR_LEFT:
        for (j = 0; j < h; ++j) {
            temp = x + j;
            index = (dx + j) * bmp_w;
            for (i = 0; i < w; ++i)
                scr->draw_pixel(scr, temp, y + i,
                                bitmap[(bmp_w - 1) - (dy + i) + index]);
        }
        break;
    case SGL_DIR_DOWN:
        for (j = 0; j < h; ++j) {
            temp = y + j;
            index = ((bmp_h - 1) - (dy + j)) * bmp_h;
            for (i = 0; i < w; ++i)
                scr->draw_pixel(scr, x + i, temp,
                                bitmap[(bmp_w - 1) - (dx + i) + index]);
        }
        break;
    }
}
