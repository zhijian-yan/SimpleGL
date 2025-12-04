#ifndef __SGL_FONT_H
#define __SGL_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sgl_core.h"

typedef enum {
    font_Song_Typeface_6x12,
    font_Song_Typeface_8x16,
    // font_xxx,(自定义字体添加字段)
} font_t;

sgl_font_info_t sgl_font_get_info(font_t font);

#ifdef __cplusplus
}
#endif

#endif
