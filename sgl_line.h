#ifndef __SGL_LINE_H
#define __SGL_LINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color);
void sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color);
void sgl_draw_line(sgl_t *sgl, int x0, int y0, int x1, int y1, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
