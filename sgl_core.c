#include "sgl_core.h"
#include "sgl_font.h"
#include "sgl_function.h"
#include "sgl_point.h"
#include <stdlib.h>
#include <string.h>

void sgl_init(sgl_t *sgl, void *buffer, uint32_t buffer_size, uint32_t page_num,
              uint32_t hor_res, uint32_t ver_res) {
    sgl->buffer = buffer;
    sgl->buffer_size = buffer_size;
    sgl->hor_res = hor_res;
    sgl->ver_res = ver_res;
    sgl->max_x = hor_res - 1;
    sgl->max_y = ver_res - 1;
    if (page_num < 2)
        page_num = 1;
    sgl->page_num = page_num;
    sgl->page_width = sgl->ver_res / page_num;
    sgl->page_start = 0;
    sgl->page.left = 0;
    sgl->page.right = hor_res - 1;
    sgl->page.top = 0;
    sgl->page.bottom = sgl->page_width - 1;
    sgl->visible = sgl->page;
    sgl->offset_x = 0;
    sgl->offset_y = 0;
    sgl->font_info = sgl_font_get_info(font_Song_Typeface_8x16);
    sgl->rotate = SGL_ROTATE_0;
    sgl->frame_start_cb = NULL;
    sgl->frame_end_cb = NULL;
    sgl->draw_pixel = sgl_draw_pixel_mono;
}

static void sgl_paint_start(sgl_t *sgl) {
    if (sgl->page_start == 0 && sgl->frame_start_cb)
        sgl->frame_start_cb();
    if (sgl->page_num > 1) {
        sgl->page.left = 0;
        sgl->page.top = sgl->page_start;
        sgl->page.right = sgl->hor_res - 1;
        sgl->page.bottom = sgl->page_start + sgl->page_width - 1;
        if (sgl->rotate) {
            sgl_original2rotated(&sgl->page.left, &sgl->page.top, sgl->max_x,
                                 sgl->max_y, sgl->rotate);
            sgl_original2rotated(&sgl->page.right, &sgl->page.bottom,
                                 sgl->max_x, sgl->max_y, sgl->rotate);
            if (sgl->page.left > sgl->page.right)
                sgl_swap_int(&sgl->page.left, &sgl->page.right);
            if (sgl->page.top > sgl->page.bottom)
                sgl_swap_int(&sgl->page.top, &sgl->page.bottom);
        }
        sgl->visible = sgl->page;
    }
}

static void sgl_paint_end(sgl_t *sgl) {
    sgl->page_start += sgl->page_width;
    if (sgl->page_start >= sgl->ver_res) {
        sgl->page_start = 0;
        if (sgl->frame_end_cb != NULL)
            sgl->frame_end_cb();
    }
}

void sgl_clear(sgl_t *sgl, uint8_t data) {
    memset(sgl->buffer, data, sgl->buffer_size);
}

void sgl_display(sgl_t *sgl) {
    sgl_paint_start(sgl);
    if (sgl->draw)
        sgl->draw(sgl);
    if (sgl->flush)
        sgl->flush(sgl->buffer, sgl->buffer_size);
    sgl_paint_end(sgl);
}

void sgl_set_buffer(sgl_t *sgl, void *buffer) { sgl->buffer = buffer; }

void sgl_set_draw(sgl_t *sgl, void (*draw)(struct sgl_t *)) {
    sgl->draw = draw;
}

void sgl_set_flush(sgl_t *sgl, void (*flush)(void *buffer, uint32_t size)) {
    sgl->flush = flush;
}

void sgl_set_draw_pixel(sgl_t *sgl, void (*draw_pixel)(sgl_t *sgl, int x, int y,
                                                       uint32_t color)) {
    sgl->draw_pixel = draw_pixel;
}

void sgl_set_frame_start_cb(sgl_t *sgl, void (*frame_start_cb)(void)) {
    sgl->frame_start_cb = frame_start_cb;
}

void sgl_set_frame_end_cb(sgl_t *sgl, void (*frame_end_cb)(void)) {
    sgl->frame_end_cb = frame_end_cb;
}

void sgl_set_font(sgl_t *sgl, int font) {
    sgl->font_info = sgl_font_get_info((font_t)font);
}

void sgl_set_screen_rotation(sgl_t *sgl, sgl_rotate_t rotate) {
    sgl->rotate = rotate;
    if (sgl->page_num < 2) {
        if (rotate == SGL_ROTATE_0 || rotate == SGL_ROTATE_180) {
            sgl->page.right = sgl->max_x;
            sgl->page.bottom = sgl->max_y;
        } else {
            sgl->page.right = sgl->max_y;
            sgl->page.bottom = sgl->max_x;
        }
        sgl_reset_visible_rect(sgl);
    }
}
