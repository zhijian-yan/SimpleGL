#include "sgl_line.h"
#include "sgl_function.h"
#include "sgl_point.h"

static void sgl_draw_original_hline(sgl_t *sgl, int x, int y, int len,
                                    uint32_t color) {
    int i;
    int x1 = x + len;
    int step = (len > 0) ? 1 : -1;
    for (i = x; i != x1; i += step)
        sgl->draw_pixel(sgl, i, y, color);
}

static void sgl_draw_original_vline(sgl_t *sgl, int x, int y, int len,
                                    uint32_t color) {
    int i;
    int y1 = y + len;
    int step = (len > 0) ? 1 : -1;
    for (i = y; i != y1; i += step)
        sgl->draw_pixel(sgl, x, i, color);
}

static int sgl_clip_line(int *start, int *len, int min, int max) {
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

void sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0 || y < sgl->visible.top || y > sgl->visible.bottom)
        return;
    if (sgl_clip_line(&x, &len, sgl->visible.left, sgl->visible.right))
        return;
    if (sgl->rotate)
        sgl_rotated2original(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    if (sgl->page_num > 1)
        y -= sgl->page_start;
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_original_hline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_original_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_original_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_original_vline(sgl, x, y, -len, color);
        break;
    }
}

void sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0 || x < sgl->visible.left || x > sgl->visible.right)
        return;
    if (sgl_clip_line(&y, &len, sgl->visible.top, sgl->visible.bottom))
        return;
    if (sgl->rotate)
        sgl_rotated2original(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    if (sgl->page_num > 1)
        y -= sgl->page_start;
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_original_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_original_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_original_vline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_original_hline(sgl, x, y, len, color);
        break;
    }
}

void sgl_draw_line(sgl_t *sgl, int x0, int y0, int x1, int y1, uint32_t color) {
    int x, y;
    int sx = 1, sy = 1;
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (dx == 0) {
        sgl_draw_original_vline(sgl, x0, y0, dy, color);
        return;
    }
    if (dy == 0) {
        sgl_draw_original_hline(sgl, x0, y0, dx, color);
        return;
    }
    if (dx < 0) {
        dx = -dx;
        sx = -1;
    }
    if (dy < 0) {
        dy = -dy;
        sy = -1;
    }
    if (dx > dy) {
        int err = dx >> 1;
        for (x = x0, y = y0; x != x1; x += sx) {
            sgl_draw_point(sgl, x, y, color);
            err -= dy;
            if (err < 0) {
                y += sy;
                err += dx;
            }
        }
    } else {
        int err = dy >> 1;
        for (x = x0, y = y0; y != y1; y += sy) {
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