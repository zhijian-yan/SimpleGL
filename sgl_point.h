#ifndef __SGL_POINT_H
#define __SGL_POINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_rotate_point(int *x, int *y, int max_x, int max_y,
                                        sgl_rotate_t rotate);
void sgl_draw_point(sgl_t *sgl, int x, int y, uint32_t color);
void sgl_draw_pixel_mono(sgl_t *sgl, int x, int y, uint32_t color);
void sgl_draw_pixel_rgb565(sgl_t *sgl, int x, int y, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif