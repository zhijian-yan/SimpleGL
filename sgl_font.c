#include "sgl_font.h"
#include "font_Song_Typeface.h"
// #include "font_xxx.h"(自定义字体添加字段)

sgl_font_info_t sgl_font_get_info(font_t font) {
    sgl_font_info_t info;
    switch (font) {
    case font_Song_Typeface_6x12:
        info.width = 6, info.height = 12,
        info.font = (uint8_t *)Song_Typeface_6x12;
        break;
    case font_Song_Typeface_8x16:
        info.width = 8, info.height = 16,
        info.font = (uint8_t *)Song_Typeface_8x16;
        break;
        // case font_xxx:font_info.width = xx,font_info.height =
        // xx,font_info.font = (uint8_t*)xxx;break;(自定义字体添加字段)
    }
    info.fontsize =
        info.width * ((info.height + 8 - 1) /
                      8); // 适用于非负数的向上取整除法(a + b - 1) / b
    return info;
}
