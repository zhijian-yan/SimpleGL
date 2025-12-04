#ifndef __SGL_FUNCTION_H
#define __SGL_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

static inline void sgl_swap_int(int *var0, int *var1) {
    int temp = *var0;
    *var0 = *var1;
    *var1 = temp;
}

static inline int sgl_min(int var0, int var1) {
    if (var0 > var1)
        return var1;
    else
        return var0;
}

static inline int sgl_max(int var0, int var1) {
    if (var0 > var1)
        return var0;
    else
        return var1;
}

static inline int sgl_check_rect(int left, int top, int right, int bottom,
                                 sgl_rect_t visible) {
    if (left > visible.right || right < visible.left || top > visible.bottom ||
        bottom < visible.top)
        return -1;
    return 0;
}

static inline void sgl_rotated2original(int *x, int *y, int max_x, int max_y,
                                        sgl_rotate_t rotate) {
    int temp = *x;
    if (rotate == SGL_ROTATE_90) {
        *x = max_x - *y;
        *y = temp;
    } else if (rotate == SGL_ROTATE_270) {
        *x = *y;
        *y = max_y - temp;
    } else if (rotate == SGL_ROTATE_180) {
        *x = max_x - *x;
        *y = max_y - *y;
    }
}

static inline void sgl_original2rotated(int *x, int *y, int max_x, int max_y,
                                        sgl_rotate_t rotate) {
    int temp = *x;
    if (rotate == SGL_ROTATE_90) {
        *x = *y;
        *y = max_x - temp;
    } else if (rotate == SGL_ROTATE_270) {
        *x = max_y - *y;
        *y = temp;
    } else if (rotate == SGL_ROTATE_180) {
        *x = max_x - *x;
        *y = max_y - *y;
    }
}

static inline void sgl_align(int *x, int *y, int w, int h, sgl_align_t align) {
    switch (align) {
    case SGL_ALIGN_UP_LEFT:
        break;
    case SGL_ALIGN_UP_RIGHT:
        *x -= w - 1;
        break;
    case SGL_ALIGN_DOWN_LEFT:
        *y -= h - 1;
        break;
    case SGL_ALIGN_DOWN_RIGHT:
        *x -= w - 1;
        *y -= h - 1;
        break;
    case SGL_ALIGN_CENTER:
        *x -= w / 2;
        *y -= h / 2;
        break;
    case SGL_ALIGN_UP_CENTER:
        *x -= w / 2;
        break;
    case SGL_ALIGN_DOWN_CENTER:
        *x -= w / 2;
        *y -= h - 1;
        break;
    case SGL_ALIGN_LEFT_CENTER:
        *y -= h / 2;
        break;
    case SGL_ALIGN_RIGHT_CENTER:
        *x -= w - 1;
        *y -= h / 2;
        break;
    }
}

#ifdef __cplusplus
}
#endif

#endif
