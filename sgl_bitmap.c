#include "sgl_bitmap.h"
#include "sgl_point.h"

void sgl_show_mono_bitmap(sgl_t *sgl, int x, int y, int w, int h,
                          const uint8_t *bitmap, sgl_dir_t dir,
                          uint32_t color) {
    int i, j;
    int offset_x = x;
    int offset_y = y;
    switch (dir) {
    case SGL_DIR_UP:
        for (i = 0; i < w; ++i)
            for (j = 0; j < h; ++j)
                if ((bitmap[i + (j / 8 * w)] & (1 << (j % 8))))
                    sgl_draw_point(sgl, offset_x + i, offset_y + j, color);
        break;
    case SGL_DIR_RIGHT:
        offset_x = x + h - 1;
        for (i = 0; i < w; ++i)
            for (j = 0; j < h; ++j)
                if ((bitmap[i + (j / 8 * w)] & (1 << (j % 8))))
                    sgl_draw_point(sgl, offset_x - j, offset_y + i, color);
        break;
    case SGL_DIR_LEFT:
        offset_y = y + w - 1;
        for (i = 0; i < w; ++i)
            for (j = 0; j < h; ++j)
                if ((bitmap[i + (j / 8 * w)] & (1 << (j % 8))))
                    sgl_draw_point(sgl, offset_x + j, offset_y - i, color);
        break;
    case SGL_DIR_DOWN:
        offset_x = x + w - 1;
        offset_y = y + h - 1;
        for (i = 0; i < w; ++i)
            for (j = 0; j < h; ++j)
                if ((bitmap[i + (j / 8 * w)] & (1 << (j % 8))))
                    sgl_draw_point(sgl, offset_x - i, offset_y - j, color);
        break;
    }
}
