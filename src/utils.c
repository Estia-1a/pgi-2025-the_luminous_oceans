#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


pixelRGB * get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    if (!data || x >= width || y >= height) {
        return NULL;
    }
    unsigned int index = (y * width + x) * n;
    return (pixelRGB *) &data[index];
}


void setPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel) {
    if (!data || !pixel || x >= width || y >= height) {
        return;
    }
    unsigned int index = (y * width + x) * n;
    data[index]     = pixel->R;
    data[index + 1] = pixel->G;
    data[index + 2] = pixel->B;
}

void print_pixel(char *filename, int x, int y) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (!read_image_data(filename, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : impossible de lire l'image %s\n", filename);
        return;
    }

    pixelRGB *pixel = get_pixel(data, width, height, channels, x, y);
    if (!pixel) {
        fprintf(stderr, "Erreur : coordonnées (%d, %d) hors plage\n", x, y);
        free(data);
        return;
    }

    printf("print_pixel (%d, %d): %u, %u, %u\n", x, y, pixel->R, pixel->G, pixel->B);
    free(data);
}
