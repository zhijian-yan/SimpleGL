#include "sgl_line.h"
#include "sgl_function.h"
#include "sgl_point.h"

static int __sgl_clip_line(int *start, int *len, int min, int max) {
    int end;
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

static void __sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0 || y < sgl->visible.top || y > sgl->visible.bottom)
        return;
    if (__sgl_clip_line(&x, &len, sgl->visible.left, sgl->visible.right))
        return;
    int x1 = x + len;
    int step = (len > 0) ? 1 : -1;
    for (int i = x; i != x1; i += step)
        sgl->draw_pixel(sgl, i, y, color);
}

static void __sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0 || x < sgl->visible.left || x > sgl->visible.right)
        return;
    if (__sgl_clip_line(&y, &len, sgl->visible.top, sgl->visible.bottom))
        return;
    int y1 = y + len;
    int step = (len > 0) ? 1 : -1;
    for (int i = y; i != y1; i += step)
        sgl->draw_pixel(sgl, x, i, color);
}

void sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color)
{
    sgl_rotate_point(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        __sgl_draw_hline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        __sgl_draw_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_180:
        __sgl_draw_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        __sgl_draw_vline(sgl, x, y, -len, color);
        break;
    }
}

void sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color)
{
    gl_rotate_point(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        __sgl_draw_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        __sgl_draw_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_180:
        __sgl_draw_vline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        __sgl_draw_hline(sgl, x, y, len, color);
        break;
    }
}

void sgl_draw_line(sgl_t *sgl, int x0, int y0, int x1, int y1, uint32_t color) {
    if (x0 == x1) {
        sgl_draw_vline(sgl, x0, y0, y1 - y0, color);
        return;
    }
    if (y0 == y1) {
        sgl_draw_hline(sgl, x0, y0, x1 - x0, color);
        return;
    }
    sgl_rotate_point(&x0, &y0, sgl->max_x, sgl->max_y, sgl->rotate);
    sgl_rotate_point(&x1, &y1, sgl->max_x, sgl->max_y, sgl->rotate);
    int dx = x1 - x0;
    int dy = y1 - y0;
    // __sgl_clip_line(&x0, &dy, sgl->visible.left, sgl->visible.right);
    // __sgl_clip_line(&y0, &dx, sgl->visible.top, sgl->visible.bottom);
    int x = x0, y = y0;
    int sx = 1, sy = 1;
    if (dx < 0) {
        dx = -dx;
        sx = -1;
    }
    if (dy < 0) {
        dy = -dy;
        sy = -1;
    }
    if (dx > dy) {
        for (int err = dx >> 1; x != x1; x += sx) {
            sgl_draw_point(sgl, x, y, color);
            err -= dy;
            if (err < 0) {
                y += sy;
                err += dx;
            }
        }
    } else {
        for (int err = dy >> 1; y != y1; y += sy) {
            sgl_draw_point(sgl, x, y, color);
            err -= dx;
            if (err < 0) {
                x += sx;
                err += dy;
            }
        }
    }
    sgl_draw_point(sgl, x1, y1, color);
}
