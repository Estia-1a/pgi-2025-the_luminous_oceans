#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Here, you have to define pixelRGB struct and its functions:
 * - pixel* getPixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y );
 * - void setPixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel);
 *
*/

typedef struct _pixelRGB {
  /*
   * TO COMPLETE
   */
    unsigned char R;
    unsigned char G;
    unsigned char B;
} pixelRGB ;

pixelRGB * get_pixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y ){
    if (x >= width || y >= height) {
        return NULL;
    }
    if (!data){
      return NULL;
    }
    unsigned int index = (y * width + x) * n;
    return (pixelRGB *) &data[index];
}

void setPixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel);

int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count);

void print_pixel(char *filename, int x, int y);

#endif
