// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Zhijian Yan

#include "sgl_common.h"

int sgl_clip_line(int32_t *start, int32_t *len, int32_t min, int32_t max) {
    int32_t end;
    if (*len > 0) {
        if (*start > max)
            return -1;
        end = *start + *len - 1;
        if (end < min)
            return -1;
        if (*start < min)
            *start = min;
        if (end > max)
            end = max;
        *len = end - *start + 1;
    } else if (*len < 0) {
        if (*start < min)
            return -1;
        end = *start + *len + 1;
        if (end > max)
            return -1;
        if (end < min)
            end = min;
        if (*start > max)
            *start = max;
        *len = end - *start - 1;
    }
    return 0;
}
