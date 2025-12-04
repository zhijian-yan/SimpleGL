#ifndef __SGL_BITMAP_H
#define __SGL_BITMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_show_mono_bitmap(sgl_t *sgl, int x, int y, int w, int h,
                          const uint8_t *bitmap, sgl_dir_t dir, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
