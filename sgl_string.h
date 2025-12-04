#ifndef __SGL_STRING_H
#define __SGL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

void sgl_show_string(sgl_t *sgl, int x, int y, const char *str, int length,
                     sgl_align_t align, sgl_dir_t dir, uint32_t color);
int sgl_show_format(sgl_t *sgl, int x, int y, sgl_align_t align, sgl_dir_t dir,
                    uint32_t color, const char *format, ...);
void sgl_show_string_default(sgl_t *sgl, int x, int y, const char *str,
                             int length, uint32_t color);
int sgl_show_format_default(sgl_t *sgl, int x, int y, uint32_t color,
                            const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
