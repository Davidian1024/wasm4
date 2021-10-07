#include "framebuffer.h"

static const uint16_t* drawColors;
static uint8_t* framebuffer;

static void drawPoint (uint8_t color, int x, int y) {
    int idx = (WIDTH * y + x) >> 2;
    int shift = (x & 0x3) << 1;
    int mask = 0x3 << shift;
    framebuffer[idx] = (color << shift) | (framebuffer[idx] & ~mask);
}

void w4_framebufferInit (const uint16_t* drawColors_, uint8_t* framebuffer_) {
    drawColors = drawColors_;
    framebuffer = framebuffer_;
}

void w4_framebufferRect (int x, int y, int width, int height) {
    // TODO(2021-09-28): Clipping
    uint8_t dc0 = *drawColors & 0xf;

    if (dc0) {
        uint8_t fillColor = dc0 - 1;
        for (int yy = y; yy < y+height; ++yy) {
            for (int xx = x; xx < x+width; ++xx) {
                drawPoint(fillColor, xx, yy);
            }
        }
    }
}
