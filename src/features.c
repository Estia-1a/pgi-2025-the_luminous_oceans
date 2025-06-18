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
            printf("first_pixel: %u, %u, %u\n",
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
            printf("tenth_pixel: %u, %u, %u\n",
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
        printf("second_line: %u, %u, %u\n",
               pixel->r, pixel->g, pixel->b);
        free(pixel);
    }
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
        printf("print_pixel(%d,%d): %u, %u, %u\n", x, y, pixel->r, pixel->g, pixel->b);
        free(pixel);
    } else {
        fprintf(stderr, "Erreur : coordonnées hors image.\n");
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
        data[i + 1] = 0; // G à 0
        data[i + 2] = 0; // B à 0
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
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
        data[i] = 0;     // R à 0
        data[i + 1] = 0; // G à 0
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
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

        data[i]     = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }

    free(data);
}

void color_green(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }

    int size = width * height * channels;
    for (int i = 0; i < size; i += channels) {
        data[i] = 0;     // R à 0
        data[i + 2] = 0; // B à 0
        // On garde G (data[i + 1])
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }

    free(data);
}

void color_gray_luminance(char *source_path) {
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
        unsigned char gray = (unsigned char)(0.21 * r + 0.72 * g + 0.07 * b);

        data[i]     = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }

    free(data);
}

void rotate_cw(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int new_width = height;
    int new_height = width;
    unsigned char *rotated_data = malloc(width * height * channels);
    
    if (!rotated_data) {
        fprintf(stderr, "Erreur : mémoire insuffisante pour la rotation.\n");
        free(data);
        return;
    }
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                int src_index = (y * width + x) * channels + c;
                int dest_index = (x * height + (height - 1 - y)) * channels + c;
                rotated_data[dest_index] = data[src_index];
            }
        }
    }
    
    if (write_image_data("image_out.bmp", rotated_data, new_width, new_height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
    free(rotated_data);
}

void color_invert(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int size = width * height * channels;
    for (int i = 0; i < size; i++) {
        data[i] = 255 - data[i]; 
    }
    
    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
}

void rotate_acw(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int new_width = height;
    int new_height = width;
    unsigned char *rotated_data = malloc(width * height * channels);
 
    if (!rotated_data) {
        fprintf(stderr, "Erreur : mémoire insuffisante pour la rotation.\n");
        free(data);
        return;
    }
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                int src_index = (y * width + x) * channels + c;
                int dest_index = ((width - 1 - x) * height + y) * channels + c;
                rotated_data[dest_index] = data[src_index];
            }
        }
    }
 
    if (write_image_data("image_out.bmp", rotated_data, new_width, new_height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
    free(rotated_data);
}

void mirror_horizontal(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            int left_index  = (y * width + x) * channels;
            int right_index = (y * width + (width - 1 - x)) * channels;
 
            for (int c = 0; c < channels; c++) {
                unsigned char temp = data[left_index + c];
                data[left_index + c] = data[right_index + c];
                data[right_index + c] = temp;
            }
        }
    }
    
    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
}

void mirror_vertical(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }

    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            int top_index    = (y * width + x) * channels;
            int bottom_index = ((height - 1 - y) * width + x) * channels;

            for (int c = 0; c < channels; c++) {
                unsigned char temp = data[top_index + c];
                data[top_index + c] = data[bottom_index + c];
                data[bottom_index + c] = temp;
            }
        }
    }

    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }

    free(data);
}
void mirror_total(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            int top_index = (y * width + x) * channels;
            int bottom_index = ((height - 1 - y) * width + (width - 1 - x)) * channels;
 
            for (int c = 0; c < channels; c++) {
                unsigned char temp = data[top_index + c];
                data[top_index + c] = data[bottom_index + c];
                data[bottom_index + c] = temp;
            }
        }
    }
 
    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
}
void color_desaturate(char *source_path) {
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
 
        unsigned char min_val = r < g ? (r < b ? r : b) : (g < b ? g : b);
        unsigned char max_val = r > g ? (r > b ? r : b) : (g > b ? g : b);
        unsigned char desaturated = (min_val + max_val) / 2;
 
        data[i]     = desaturated;
        data[i + 1] = desaturated;
        data[i + 2] = desaturated;
    }
 
    if (write_image_data("image_out.bmp", data, width, height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
}
void max_pixel(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int max_sum = -1;
    int max_x = 0, max_y = 0;
    pixelRGB *max_pixel = NULL;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            int sum = p->r + p->g + p->b;
            if (sum > max_sum) {
                max_sum = sum;
                max_x = x;
                max_y = y;
                max_pixel = p;
            } else {
                free(p); // libère les autres pixels
            }
        }
    }
 
    if (max_pixel) {
        printf("max_pixel (%d, %d): %u, %u, %u\n", max_x, max_y, max_pixel->r, max_pixel->g, max_pixel->b);
        free(max_pixel);
    }
 
    free(data);
}
void max_component(char *source_path, char component) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    if (component != 'R' && component != 'G' && component != 'B') {
        fprintf(stderr, "Erreur : composant invalide (choisir R, G ou B).\n");
        free(data);
        return;
    }
 
    int max_val = -1;
    int max_x = 0, max_y = 0;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            int val = (component == 'R') ? p->r :
                      (component == 'G') ? p->g : p->b;
            if (val > max_val) {
                max_val = val;
                max_x = x;
                max_y = y;
            }
            free(p);
        }
    }
 
    printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_val);
    free(data);
}
void min_pixel(char *source_path) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int min_sum = 256 * 3 + 1; // Somme maximale possible +1
    int min_x = 0, min_y = 0;
    pixelRGB *min_pixel_ptr = NULL;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            int sum = p->r + p->g + p->b;
            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
                if (min_pixel_ptr) free(min_pixel_ptr);
                min_pixel_ptr = p;
            } else {
                free(p);
            }
        }
    }
 
    if (min_pixel_ptr) {
        printf("min_pixel (%d, %d): %u, %u, %u\n", min_x, min_y, min_pixel_ptr->r, min_pixel_ptr->g, min_pixel_ptr->b);
        free(min_pixel_ptr);
    }
 
    free(data);
}
void min_component(char *source_path, char component) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    if (component != 'R' && component != 'G' && component != 'B') {
        fprintf(stderr, "Erreur : composant invalide (choisir R, G ou B).\n");
        free(data);
        return;
    }
 
    int min_val = 256;
    int min_x = 0, min_y = 0;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            int val = (component == 'R') ? p->r :
                      (component == 'G') ? p->g : p->b;
            if (val < min_val) {
                min_val = val;
                min_x = x;
                min_y = y;
            }
            free(p);
        }
    }
 
    printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_val);
    free(data);
}
void stat_report(char *source_path) {
    FILE *f = fopen("stat_report.txt", "w");
    if (!f) {
        fprintf(stderr, "Erreur : impossible de créer stat_report.txt\n");
        return;
    }
 
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture image échouée.\n");
        fclose(f);
        return;
    }
 
    // Initialisation
    int max_sum = -1, min_sum = 256 * 3 + 1;
    int max_sum_x = 0, max_sum_y = 0;
    int min_sum_x = 0, min_sum_y = 0;
 
    int maxR = -1, maxG = -1, maxB = -1;
    int maxRx = 0, maxRy = 0, maxGx = 0, maxGy = 0, maxBx = 0, maxBy = 0;
 
    int minR = 256, minG = 256, minB = 256;
    int minRx = 0, minRy = 0, minGx = 0, minGy = 0, minBx = 0, minBy = 0;
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            int sum = p->r + p->g + p->b;
 
            if (sum > max_sum) {
                max_sum = sum;
                max_sum_x = x;
                max_sum_y = y;
            }
            if (sum < min_sum) {
                min_sum = sum;
                min_sum_x = x;
                min_sum_y = y;
            }
 
            if (p->r > maxR) { maxR = p->r; maxRx = x; maxRy = y; }
            if (p->g > maxG) { maxG = p->g; maxGx = x; maxGy = y; }
            if (p->b > maxB) { maxB = p->b; maxBx = x; maxBy = y; }
 
            if (p->r < minR) { minR = p->r; minRx = x; minRy = y; }
            if (p->g < minG) { minG = p->g; minGx = x; minGy = y; }
            if (p->b < minB) { minB = p->b; minBx = x; minBy = y; }
 
            free(p);
        }
    }
 
    // Écriture dans le fichier
    fprintf(f, "max_pixel (%d, %d): %d\n\n", max_sum_x, max_sum_y, max_sum);
    fprintf(f, "min_pixel (%d, %d): %d\n\n", min_sum_x, min_sum_y, min_sum);
 
    fprintf(f, "max_component R (%d, %d): %d\n\n", maxRx, maxRy, maxR);
    fprintf(f, "max_component G (%d, %d): %d\n\n", maxGx, maxGy, maxG);
    fprintf(f, "max_component B (%d, %d): %d\n\n", maxBx, maxBy, maxB);
 
    fprintf(f, "min_component R (%d, %d): %d\n\n", minRx, minRy, minR);
    fprintf(f, "min_component G (%d, %d): %d\n\n", minGx, minGy, minG);
    fprintf(f, "min_component B (%d, %d): %d\n", minBx, minBy, minB);
 
    fclose(f);
    free(data);
}
void scale_crop(char *source_path, int center_x, int center_y, int width, int height) {
    int original_width, original_height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &original_width, &original_height, &channel_count);

    int x_start = center_x - width / 2;
    int y_start = center_y - height / 2;

    if (x_start < 0) {
        x_start = 0;
    } else if (x_start + width > original_width) {
        x_start = original_width - width;
    }

    if (y_start < 0) {
        y_start = 0;
    } else if (y_start + height > original_height) {
        y_start = original_height - height;
    }

    unsigned char *new_data = (unsigned char*)malloc(width * height * channel_count * sizeof(unsigned char));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = x_start + x;
            int new_y = y_start + y;

            pixelRGB *pixel = get_pixel(data, original_width, original_height, channel_count, new_x, new_y);
            unsigned char R = pixel->r;
            unsigned char G = pixel->g;
            unsigned char B = pixel->b;

            new_data[(y * width + x) * channel_count] = R;
            new_data[(y * width + x) * channel_count + 1] = G;
            new_data[(y * width + x) * channel_count + 2] = B;
        }
    }
    write_image_data("image_out.bmp", new_data, width, height);
    free(new_data);
    free_image_data(data);
}
void scale_nearest(char *source_path, float scale) {
    int width, height, channels;
    unsigned char *data = NULL;
 
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        fprintf(stderr, "Erreur : lecture de l'image échouée.\n");
        return;
    }
 
    int new_width = (int)(width * scale);
    int new_height = (int)(height * scale);
    unsigned char *scaled_data = malloc(new_width * new_height * channels);
 
    if (!scaled_data) {
        fprintf(stderr, "Erreur : mémoire insuffisante.\n");
        free(data);
        return;
    }
 
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = (int)(x / scale + 0.5f);
            int src_y = (int)(y / scale + 0.5f);
 
            if (src_x >= width) src_x = width - 1;
            if (src_y >= height) src_y = height - 1;
 
            for (int c = 0; c < channels; c++) {
                int dest_index = (y * new_width + x) * channels + c;
                int src_index = (src_y * width + src_x) * channels + c;
                scaled_data[dest_index] = data[src_index];
            }
        }
    }
 
    if (write_image_data("image_out.bmp", scaled_data, new_width, new_height) != 0) {
        fprintf(stderr, "Erreur : écriture de l'image échouée.\n");
    }
 
    free(data);
    free(scaled_data);
}