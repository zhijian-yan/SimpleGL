#include "sgl_point.h"
#include "sgl_function.h"

void sgl_draw_point(sgl_t *sgl, int x, int y, uint32_t color) {
    if (sgl_check_rect(x, y, x, y, sgl->visible))
        return;
    if (sgl->rotate)
        sgl_rotated2original(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    if (sgl->page_num > 1)
        y -= sgl->page_start;
    sgl->draw_pixel(sgl, x, y, color);
}

void sgl_draw_pixel_mono(sgl_t *sgl, int x, int y, uint32_t color) {
    switch (color) {
    case SGL_COLOR_LIGHT:
        ((uint8_t *)sgl->buffer)[(y / 8) * sgl->hor_res + x] |= (1 << (y % 8));
        break;
    case SGL_COLOR_DARK:
        ((uint8_t *)sgl->buffer)[(y / 8) * sgl->hor_res + x] &= ~(1 << (y % 8));
        break;
    case SGL_COLOR_INVERSE:
        ((uint8_t *)sgl->buffer)[(y / 8) * sgl->hor_res + x] ^= (1 << (y % 8));
        break;
    }
}

void sgl_draw_pixel_rgb565(sgl_t *sgl, int x, int y, uint32_t color) {
    ((uint8_t *)sgl->buffer)[(x + sgl->hor_res * y) * 2] = color >> 8;
    ((uint8_t *)sgl->buffer)[(x + sgl->hor_res * y) * 2 + 1] = color;
}