// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#include "sgl_core.h"
#include "sgl_common.h"
#include <string.h>

sgl_screen_t *active_screen;

int sgl_init(sgl_screen_t *screen, void *buffer, uint32_t buffer_size,
             uint32_t hor_res, uint32_t ver_res) {
    if (!screen || !buffer)
        return -1;
    memset(screen, 0, sizeof(sgl_screen_t));
    screen->buffer = buffer;
    screen->buffer_size = buffer_size;
    screen->hor_res = hor_res;
    screen->ver_res = ver_res;
    screen->max_x = hor_res - 1;
    screen->max_y = ver_res - 1;
    screen->visible.left = 0;
    screen->visible.top = 0;
    screen->visible.right = screen->max_x;
    screen->visible.bottom = screen->max_y;
    screen->invalidate = screen->visible;
    screen->rotate = SGL_ROTATE_DEFAULT;
    screen->fcount = 0;
    return 0;
}

void sgl_handler(void) {
    if (!active_screen || !active_screen->paint || !active_screen->flush)
        return;
    active_screen->paint();
    active_screen->flush(active_screen->buffer, active_screen->buffer_size);
    ++active_screen->fcount;
}

void sgl_set_screen(sgl_screen_t *screen) {
    if (!screen)
        return;
    active_screen = screen;
}

void sgl_set_buffer(void *buffer, uint32_t buffer_size) {
    if (!active_screen || !buffer)
        return;
    active_screen->buffer = buffer;
    active_screen->buffer_size = buffer_size;
}

void sgl_set_paint(void (*paint)()) {
    if (!active_screen)
        return;
    active_screen->paint = paint;
}

void sgl_set_flush(void (*flush)(void *buffer, uint32_t buffer_size)) {
    if (!active_screen)
        return;
    active_screen->flush = flush;
}

void sgl_set_draw_pixel(void (*draw_pixel)(int32_t x, int32_t y,
                                           uint32_t color)) {
    if (!active_screen || !draw_pixel)
        return;
    active_screen->draw_pixel = draw_pixel;
}

void sgl_set_visible(int32_t left, int32_t top, int32_t right, int32_t bottom) {
    if (!active_screen)
        return;
    if (left < 0 || top < 0 || right > active_screen->max_x ||
        bottom > active_screen->max_y)
        return;
    active_screen->visible.left = left;
    active_screen->visible.top = top;
    active_screen->visible.right = right;
    active_screen->visible.bottom = bottom;
}

uint32_t sgl_get_fcount(void) {
    if (!active_screen)
        return 0;
    return active_screen->fcount;
}

void sgl_reset_fcount(void) {
    if (!active_screen)
        return;
    active_screen->fcount = 0;
}

void sgl_clear_screen(uint8_t value) {
    if (!active_screen || !active_screen->buffer)
        return;
    memset(active_screen->buffer, value, active_screen->buffer_size);
}
