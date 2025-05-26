#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}
void dimension (char *source_path) {
    int width ;
    int height ;
    int channel_count ;
    unsigned char *data ;
    
    int resultat = read_image_data (source_path, &data, &width, &height, &channel_count);
    if(resultat) {
    printf("dimension: %d, %d ", width, height);
    }
    else {
     printf("erreur: ");
    }
}

void first_pixel (char *source_path) {
    int width ;
    int height ;
    int channel_count ;
    unsigned char *data ;
    
    int resultat = read_image_data (source_path, &data, &width, &height, &channel_count);
    if(resultat) {
    printf("dimension: %d, %d, %d ",data[0], data[1], data[2]);
    }
    else {
     printf("erreur: ");
    }
}

void tenth_pixel (char *source_path) {
    int width ;
    int height ;
    int channel_count ;
    unsigned char *data ;
    int pixel = 10 ;
    
    int resultat = read_image_data (source_path, &data, &width, &height, &channel_count);
    if(resultat) {
    printf("La couleur du dernier pixel est : %d, %d, %d ",data[3*pixel-3], data[3*pixel-2], data[3*pixel-1]);
    }
    else {
     printf("erreur: ");
    }
}

void second_line (char *source_path) {
    int width = 2 ;
    int height ;
    int channel_count ;
    unsigned char *data ;
    int pixel = 1 ;
    
    int resultat = read_image_data (source_path, &data, &width, &height, &channel_count);
    if(resultat) {
    printf("La couleur du dernier pixel est : %d, %d, %d ",data[width*(3*pixel-3)], data[width*(3*pixel-2)], data[width*(3*pixel-1)]);
    }
    else {
     printf("erreur: ");
    }
}