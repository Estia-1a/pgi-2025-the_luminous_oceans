#include <stdlib.h>
#include "utils.h"

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const int x, const int y) {
    if (data == NULL || x < 0 || y < 0 || x >= (int)width || y >= (int)height) {
        return NULL;
    }

    pixelRGB *p = malloc(sizeof(pixelRGB));
    if (p == NULL) return NULL;

    int index = (y * width + x) * n;
    p->r = data[index];
    p->g = data[index + 1];
    p->b = data[index + 2];
    return p;
}
