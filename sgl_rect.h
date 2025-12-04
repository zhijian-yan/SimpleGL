#ifndef __SGL_RECT_H
#define __SGL_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_draw_rectangle(sgl_t *sgl, int x, int y, int w, int h, int is_filled,
                        uint32_t color);
void sgl_draw_round_rectangle(sgl_t *sgl, int x, int y, int w, int h, int r,
                              int is_filled, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
