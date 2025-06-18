#include <stdlib.h>
#include <estia-image.h>
#include "utils.h"
 
pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const int x, const int y) {
    if (data == NULL || x < 0 || y < 0 || x >= width || y >= height) {
        return NULL;
    }
 
    pixelRGB *p = malloc(sizeof(pixelRGB));
    if (p == NULL) return NULL;
 
    int index = (y * width + x) * n;
    p->R = data[index];
    p->G = data[index + 1];
    p->B = data[index + 2];
    return p;
}
