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
    sgl_set_screen_rotation(screen, SGL_ROTATE_DEFAULT);
    screen->invalidate = screen->visible;
    return 0;
}

void sgl_handler(void) {
    sgl_screen_t *scr = active_screen;
    if (!scr || !scr->paint || !scr->flush || !scr->buffer)
        return;
    scr->paint();
    scr->flush(scr->buffer, scr->buffer_size);
    ++scr->fcount;
}

void sgl_set_screen(sgl_screen_t *screen) {
    if (!screen)
        return;
    active_screen = screen;
}

void sgl_set_buffer(sgl_screen_t *screen, void *buffer, uint32_t buffer_size) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr || !buffer)
        return;
    scr->buffer = buffer;
    scr->buffer_size = buffer_size;
}

void sgl_set_paint(sgl_screen_t *screen, void (*paint)()) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return;
    scr->paint = paint;
}

void sgl_set_flush(sgl_screen_t *screen,
                   void (*flush)(void *buffer, uint32_t buffer_size)) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return;
    scr->flush = flush;
}

void sgl_set_draw_pixel(sgl_screen_t *screen,
                        void (*draw_pixel)(int32_t x, int32_t y,
                                           uint32_t color)) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr || !draw_pixel)
        return;
    scr->draw_pixel = draw_pixel;
}

void sgl_set_visible(sgl_screen_t *screen, int32_t left, int32_t top,
                     int32_t right, int32_t bottom) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return;
    if (left < 0)
        left = 0;
    if (top < 0)
        top = 0;
    if (right > scr->max_x)
        right = scr->max_x;
    if (bottom > scr->max_y)
        bottom = scr->max_y;
    sgl_set_rect(&scr->visible, left, top, right, bottom);
}

void sgl_set_screen_rotation(sgl_screen_t *screen, sgl_rotate_t rotate) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return;
    scr->rotate = rotate;
    switch (rotate) {
    case SGL_ROTATE_0:
    case SGL_ROTATE_180:
        scr->max_x = scr->hor_res - 1;
        scr->max_y = scr->ver_res - 1;
        break;
    case SGL_ROTATE_90:
    case SGL_ROTATE_270:
        scr->max_x = scr->ver_res - 1;
        scr->max_y = scr->hor_res - 1;
        break;
    }
    sgl_set_rect(&scr->visible, 0, 0, scr->max_x, scr->max_y);
}

uint32_t sgl_get_fcount(sgl_screen_t *screen) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return 0;
    return scr->fcount;
}

void sgl_reset_fcount(sgl_screen_t *screen) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr)
        return;
    scr->fcount = 0;
}

void sgl_clear_screen(sgl_screen_t *screen, uint8_t value) {
    sgl_screen_t *scr = !screen ? active_screen : screen;
    if (!scr || !scr->buffer)
        return;
    memset(scr->buffer, value, scr->buffer_size);
}
