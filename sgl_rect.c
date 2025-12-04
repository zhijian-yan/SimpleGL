#include "sgl_rect.h"
#include "sgl_circle.h"
#include "sgl_function.h"
#include "sgl_line.h"

void sgl_draw_rectangle(sgl_t *sgl, int x, int y, int w, int h, int is_filled,
                        uint32_t color) {
    int i;
    if (!w || !h)
        return;
    if (w < 0) {
        x += w + 1;
        w = -w;
    }
    if (h < 0) {
        y += h + 1;
        h = -h;
    }
    if (sgl_check_rect(x, y, x + w - 1, y + h - 1, sgl->visible))
        return;
    if (!is_filled) {
        if (h > 2) {
            sgl_draw_hline(sgl, x, y, w, color);
            sgl_draw_hline(sgl, x, y + h - 1, w, color);
            sgl_draw_vline(sgl, x, y + 1, h - 2, color);
            sgl_draw_vline(sgl, x + w - 1, y + 1, h - 2, color);
        } else if (h == 2) {
            sgl_draw_hline(sgl, x, y, w, color);
            sgl_draw_hline(sgl, x, y + 1, w, color);
        }
        if (h == 1) {
            sgl_draw_hline(sgl, x, y, w, color);
        }
    } else {
        for (i = y; i < y + h; ++i)
            sgl_draw_hline(sgl, x, i, w, color);
    }
}

void sgl_draw_round_rectangle(sgl_t *sgl, int x, int y, int w, int h, int r,
                              int is_filled, uint32_t color) {
    int min, hl, vl;
    sgl_rect_t rect;
    if (!w || !h)
        return;
    if (r == 0) {
        sgl_draw_rectangle(sgl, x, y, w, h, is_filled, color);
        return;
    }
    if (w < 0) {
        x += w + 1;
        w = -w;
    }
    if (h < 0) {
        y += h + 1;
        h = -h;
    }
    if (sgl_check_rect(x, y, x + w - 1, y + h - 1, sgl->visible))
        return;
    if (w < 3) {
        sgl_draw_vline(sgl, x, y, h, color);
        if (w == 2)
            sgl_draw_vline(sgl, x + 1, y, h + 1, color);
        return;
    }
    if (h < 3) {
        sgl_draw_hline(sgl, x, y, w, color);
        if (h == 2)
            sgl_draw_hline(sgl, x, y + 1, w + 1, color);
        return;
    }
    if (r < 0)
        r = -r;
    min = sgl_min(w, h);
    if (2 * r > min)
        r = min / 2;
    hl = w - 2 * r;
    vl = h - 2 * r;
    rect.left = x + r;
    rect.top = y + r;
    rect.right = x + w - 1 - r;
    rect.bottom = y + h - 1 - r;
    if (!is_filled) {
        sgl_draw_hline(sgl, rect.left, y, hl, color);
        sgl_draw_hline(sgl, rect.left, rect.bottom + r, hl, color);
        sgl_draw_vline(sgl, x, rect.top, vl, color);
        sgl_draw_vline(sgl, rect.right + r, rect.top, vl, color);
        sgl_draw_outlined_circle_section(sgl, rect.left, rect.top, r,
                                         SGL_CIRCLE_UPPER_LEFT, color);
        sgl_draw_outlined_circle_section(sgl, rect.right, rect.top, r,
                                         SGL_CIRCLE_UPPER_RIGHT, color);
        sgl_draw_outlined_circle_section(sgl, rect.left, rect.bottom, r,
                                         SGL_CIRCLE_LOWER_LEFT, color);
        sgl_draw_outlined_circle_section(sgl, rect.right, rect.bottom, r,
                                         SGL_CIRCLE_LOWER_RIGHT, color);
    } else {
        sgl_draw_rectangle(sgl, rect.left, rect.top, hl, vl, 1, color);
        sgl_draw_rectangle(sgl, rect.left, y, hl, r, 1, color);
        sgl_draw_rectangle(sgl, rect.left, rect.bottom + 1, hl, r, 1, color);
        sgl_draw_rectangle(sgl, x, rect.top, r, vl, 1, color);
        sgl_draw_rectangle(sgl, rect.right + 1, rect.top, r, vl, 1, color);
        sgl_draw_filled_circle_section(sgl, rect.left, rect.top, r,
                                       SGL_CIRCLE_UPPER_LEFT, color);
        sgl_draw_filled_circle_section(sgl, rect.right, rect.top, r,
                                       SGL_CIRCLE_UPPER_RIGHT, color);
        sgl_draw_filled_circle_section(sgl, rect.left, rect.bottom, r,
                                       SGL_CIRCLE_LOWER_LEFT, color);
        sgl_draw_filled_circle_section(sgl, rect.right, rect.bottom, r,
                                       SGL_CIRCLE_LOWER_RIGHT, color);
    }
}
