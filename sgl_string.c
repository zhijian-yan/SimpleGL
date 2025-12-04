#include "sgl_string.h"
#include "sgl_bitmap.h"
#include "sgl_function.h"
#include <stdarg.h>
#include <stdio.h>

void sgl_show_string(sgl_t *sgl, int x, int y, const char *str, int length,
                     sgl_align_t align, sgl_dir_t dir, uint32_t color) {
    int i;
    int fontwidth = sgl->font_info.width;
    int fontheight = sgl->font_info.height;
    switch (dir) {
    case SGL_DIR_UP:
        sgl_align(&x, &y, fontwidth * length, fontheight, align);
        for (i = 0; i < length; ++i)
            sgl_show_mono_bitmap(
                sgl, x + i * fontwidth, y, fontwidth, fontheight,
                &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize],
                dir, color);
        break;
    case SGL_DIR_RIGHT:
        sgl_align(&x, &y, fontheight, fontwidth * length, align);
        for (i = 0; i < length; ++i)
            sgl_show_mono_bitmap(
                sgl, x, y + i * fontwidth, fontwidth, fontheight,
                &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize],
                dir, color);
        break;
    case SGL_DIR_LEFT:
        sgl_align(&x, &y, fontheight, fontwidth * length, align);
        y += (length - 1) * fontwidth;
        for (i = 0; i < length; ++i)
            sgl_show_mono_bitmap(
                sgl, x, y - i * fontwidth, fontwidth, fontheight,
                &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize],
                dir, color);
        break;
    case SGL_DIR_DOWN:
        sgl_align(&x, &y, fontwidth * length, fontheight, align);
        x += (length - 1) * fontwidth;
        for (i = 0; i < length; ++i)
            sgl_show_mono_bitmap(
                sgl, x - i * fontwidth, y, fontwidth, fontheight,
                &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize],
                dir, color);
        break;
    }
}

int sgl_show_format(sgl_t *sgl, int x, int y, sgl_align_t align, sgl_dir_t dir,
                    uint32_t color, const char *format, ...) {
    char buffer[sgl_FORMAT_STRING_BUFFERSIZE];
    va_list args;
    va_start(args, format);
    int length = vsnprintf(buffer, sgl_FORMAT_STRING_BUFFERSIZE, format, args);
    va_end(args);
    sgl_show_string(sgl, x, y, buffer, length, align, dir, color);
    return length;
}

void sgl_show_string_default(sgl_t *sgl, int x, int y, const char *str,
                             int length, uint32_t color) {
    sgl_show_string(sgl, x, y, str, length, SGL_ALIGN_DEFAULT, SGL_DIR_DEFAULT,
                    color);
}

int sgl_show_format_default(sgl_t *sgl, int x, int y, uint32_t color,
                            const char *format, ...) {
    char buffer[sgl_FORMAT_STRING_BUFFERSIZE];
    va_list args;
    va_start(args, format);
    int length = vsnprintf(buffer, sgl_FORMAT_STRING_BUFFERSIZE, format, args);
    va_end(args);
    sgl_show_string(sgl, x, y, buffer, length, SGL_ALIGN_DEFAULT,
                    SGL_DIR_DEFAULT, color);
    return length;
}
