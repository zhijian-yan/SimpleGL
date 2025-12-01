#ifndef __SGL_CORE_H
#define __SGL_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define sgl_FORMAT_STRING_BUFFERSIZE 256

#define SGL_COLOR_DARK 0
#define SGL_COLOR_LIGHT 1
#define SGL_COLOR_INVERSE 2

typedef enum {
    SGL_DIR_UP = 0,
    SGL_DIR_DOWN,
    SGL_DIR_LEFT,
    SGL_DIR_RIGHT,
} sgl_dir_t;

#define SGL_DIR_DEFAULT SGL_DIR_UP

/**
 * alignment:
 *
 *     up_left           up_center           up_right
 *             +-------------+-------------+
 *             |                           |
 *             |                           |
 * left_center +        center(x,y)        + right_center
 *             |                           |
 *             |                           |
 *             +-------------+-------------+
 *   down_left          down_center          down_right
 *
 */

typedef enum {
    SGL_ALIGN_UP_LEFT = 0,
    SGL_ALIGN_UP_RIGHT,
    SGL_ALIGN_DOWN_LEFT,
    SGL_ALIGN_DOWN_RIGHT,
    SGL_ALIGN_CENTER,
    SGL_ALIGN_UP_CENTER,
    SGL_ALIGN_DOWN_CENTER,
    SGL_ALIGN_LEFT_CENTER,
    SGL_ALIGN_RIGHT_CENTER,
} sgl_align_t;

#define SGL_ALIGN_DEFAULT SGL_ALIGN_UP_LEFT

/**
 * rotate shape:坐标轴固定，图像旋转
 *
 * -------------------------
 * |rotate |   x'  |   y'  |
 * |-------|-------|-------|
 * |   0   |   x   |   y   |
 * |   90  |  w-y  |   x   |
 * |  -90  |   y   |  h-x  |
 * |  180  |  w-x  |  h-y  |
 * -------------------------
 *
 * rotate axis:图像固定，坐标轴旋转
 *
 * -------------------------
 * |rotate |   x'  |   y'  |
 * |-------|-------|-------|
 * |   0   |   x   |   y   |
 * |   90  |   y   |  w-x  |
 * |  -90  |  h-y  |   x   |
 * |  180  |  w-x  |  h-y  |
 * -------------------------
 *
 * w(width):hor_res-1  h(height):ver_res-1
 *
 */

typedef enum {
    SGL_ROTATE_0 = 0,
    SGL_ROTATE_90,
    SGL_ROTATE_180,
    SGL_ROTATE_270,
} sgl_rotate_t;

#define SGL_ROTATE_DEFAULT SGL_ROTATE_0

typedef enum {
    SGL_CIRCLE_UPPER_RIGHT = 0x01,
    SGL_CIRCLE_UPPER_LEFT = 0x02,
    SGL_CIRCLE_LOWER_RIGHT = 0x04,
    SGL_CIRCLE_LOWER_LEFT = 0x08,
    SGL_CIRCLE_ALL = 0xFF,
} sgl_circle_t;

typedef struct {
    int width;
    int height;
    int fontsize;
    const uint8_t *font;
} sgl_font_info_t;

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
} sgl_rect_t;

typedef struct sgl_t {
    void *buffer;                    // 缓冲区指针
    int buffer_size;                 // 缓冲区大小
    int hor_res;                     // 屏幕水平分辨率(X坐标范围的大小)
    int ver_res;                     // 屏幕垂直分辨率(Y坐标范围的大小)
    int max_x;                       // x坐标最大值
    int max_y;                       // y坐标最大值
    int page_start;                  // 页起始y坐标
    int page_width;                  // 页宽
    int page_num;                    // 页数
    int offset_x;                    // x坐标偏移
    int offset_y;                    // y坐标偏移
    sgl_rect_t page;                 // 页矩形
    sgl_rect_t visible;              // 可见矩形
    sgl_font_info_t font_info;       // 字体信息
    sgl_rotate_t rotate;             // 屏幕旋转参数
    void (*draw)(struct sgl_t *sgl); // 绘制回调函数
    void (*flush)(void *buffer, uint32_t buffer_size); // 发送数据回调函数
    void (*frame_start_cb)(void);                      // 帧起始回调函数
    void (*frame_end_cb)(void);                        // 帧结束回调函数
    void (*draw_pixel)(struct sgl_t *sgl,              // 绘制像素函数指针
                       int x, int y, uint32_t color);
} sgl_t;

// 初始化函数
void sgl_init(sgl_t *sgl, void *buffer, uint32_t buffer_size, uint32_t page_num,
              uint32_t hor_res, uint32_t ver_res);
void sgl_display(sgl_t *sgl);
void sgl_clear(sgl_t *sgl, uint8_t data);
void sgl_set_draw(sgl_t *sgl, void (*draw)(struct sgl_t *));
void sgl_set_flush(sgl_t *sgl, void (*flush)(void *buffer, uint32_t size));
// 设置函数
void sgl_set_buffer(sgl_t *sgl, void *buffer);
void sgl_set_draw_pixel(sgl_t *sgl, void (*draw_pixel)(sgl_t *sgl, int x, int y,
                                                       uint32_t color));
void sgl_set_frame_start_cb(sgl_t *sgl, void (*frame_start_cb)(void));
void sgl_set_frame_end_cb(sgl_t *sgl, void (*frame_end_cb)(void));
void sgl_set_font(sgl_t *sgl, int font);
void sgl_set_screen_rotation(sgl_t *sgl, sgl_rotate_t rotate);

static inline void sgl_set_visible_rect(sgl_t *sgl, int left, int top,
                                        int right, int bottom) {
    if (left < sgl->page.left)
        left = sgl->page.left;
    if (top < sgl->page.top)
        top = sgl->page.top;
    if (right > sgl->page.right)
        right = sgl->page.right;
    if (bottom > sgl->page.bottom)
        bottom = sgl->page.bottom;
    sgl->visible.left = left;
    sgl->visible.top = top;
    sgl->visible.right = right;
    sgl->visible.bottom = bottom;
}

static inline void sgl_reset_visible_rect(sgl_t *sgl) {
    sgl->visible = sgl->page;
}

#ifdef __cplusplus
}
#endif

#endif