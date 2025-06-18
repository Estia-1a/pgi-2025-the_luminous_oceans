#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

#include "features.h"
#include "utils.h"    // pour get_pixel()

void helloWorld(void) {
    printf("Hello World !\n");
}

void dimension(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count)) {
        printf("dimension: %d, %d\n", width, height);
        free(data);
    } else {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
    }
}

void first_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    if (read_image_data(source_path, &data, &width, &height, &channel_count)) {
        if (channel_count >= 3) {
            printf("pixel: %u, %u, %u\n",
                   data[0], data[1], data[2]);
        } else {
            fprintf(stderr, "Erreur : image avec moins de 3 canaux.\n");
        }
        free(data);
    } else {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
    }
}

void tenth_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;
    int pixel_index = 9;  // 10ème pixel = index 9

    if (read_image_data(source_path, &data, &width, &height, &channel_count)) {
        if (channel_count >= 3 && pixel_index < width * height) {
            int offset = pixel_index * channel_count;
            printf("10e pixel: %u, %u, %u\n",
                   data[offset], data[offset+1], data[offset+2]);
        } else {
            fprintf(stderr, "Erreur : moins de 3 canaux ou pixel hors image.\n");
        }
        free(data);
    } else {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
    }
}

void second_line(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : impossible de lire %s\n", source_path);
        return;
    }
    if (height < 2) {
        fprintf(stderr, "Erreur : l'image doit avoir au moins 2 lignes.\n");
        free(data);
        return;
    }

    pixelRGB *pixel = get_pixel(data, width, height, channels, 0, 1);
    if (!pixel) {
        fprintf(stderr, "Erreur : pixel (0,1) non accessible\n");
    } else {
        /* accès aux champs r,g,b (minuscules dans estia-image.h) */
        printf("second_line: %u, %u, %u\n",
               pixel->r, pixel->g, pixel->b);
    }
    free(data);
}

void max_component(char *source_path, char component) {
    int width, height, channel_count;
    unsigned char *data;

    if (!read_image_data(source_path, &data, &width, &height, &channel_count)) {
        fprintf(stderr, "Erreur : impossible de lire %s\n", source_path);
        return;
    }
    if (channel_count < 3) {
        fprintf(stderr, "Erreur : moins de 3 canaux.\n");
        free(data);
        return;
    }
    if (component!='R' && component!='G' && component!='B') {
        fprintf(stderr, "Erreur : composant invalide (%c)\n", component);
        free(data);
        return;
    }

    int max_val = -1, max_x = 0, max_y = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channel_count, x, y);
            int v = (component=='R' ? p->r :
                     component=='G' ? p->g : p->b);
            if (v > max_val) {
                max_val = v;
                max_x = x;
                max_y = y;
            }
        }
    }
    printf("max_component (%c): %d at (%d, %d)\n",
           component, max_val, max_x, max_y);
    free(data);
}
void print_pixel(char *source_path, int x, int y) {
    int width, height, channel_count;
    unsigned char *data;

    if (!read_image_data(source_path, &data, &width, &height, &channel_count)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
    pixelRGB *pixel = get_pixel(data, width, height, channel_count, x, y);
    if (pixel) {
        printf("pixel(%d,%d): %u, %u, %u\n", x, y, pixel->r, pixel->g, pixel->b);
        free(pixel);
    } else {
        fprintf(stderr, "Erreur : coordonnées hors image.\n");
    }
    free(data);
}
void color_red(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }

    int size = width * height * channels;
    for (int i = 0; i < size; i += channels) {
        data[i + 1] = 0; // G
        data[i + 2] = 0; // B
    }

    free(data);
}

void color_blue(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }

    int size = width * height * channels;
    for (int i = 0; i < size; i += channels) {
        data[i] = 0; 
        data[i + 1] = 0; 
    }

    free(data);
}
void color_gray(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }

    int size = width * height * channels;
    for (int i = 0; i < size; i += channels) {
        unsigned char r = data[i];
        unsigned char g = data[i + 1];
        unsigned char b = data[i + 2];
        unsigned char gray = (r + g + b) / 3;

        data[i] = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }
    
    free(data);
}
