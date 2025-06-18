#ifndef UTILS_H
#define UTILS_H

typedef struct _pixelRGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixelRGB;

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const int x, const int y);

#endif
