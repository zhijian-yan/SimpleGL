#ifndef __SGL_CIRCLE_H
#define __SGL_CIRCLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_draw_outlined_circle_section(sgl_t *sgl, int xc, int yc, int r,
                                      sgl_circle_t dir, uint32_t color);
void sgl_draw_filled_circle_section(sgl_t *sgl, int xc, int yc, int r,
                                    sgl_circle_t dir, uint32_t color);
void sgl_draw_circle(sgl_t *sgl, int xc, int yc, int r, int is_filled,
                     uint32_t color);
void sgl_draw_outlined_ellipse_section(sgl_t *sgl, int xc, int yc, int rx,
                                       int ry, sgl_circle_t dir,
                                       uint32_t color);
void sgl_draw_filled_ellipse_section(sgl_t *sgl, int xc, int yc, int rx, int ry,
                                     sgl_circle_t dir, uint32_t color);
void sgl_draw_ellipse(sgl_t *sgl, int xc, int yc, int rx, int ry, int is_filled,
                      uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
