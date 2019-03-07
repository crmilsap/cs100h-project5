/* Cory Milsap CS 100-010
 * Takes a PPM file and converts to one of six different grayscale intesities.
 * Reads an existing PPM file and writes a PGM file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"

ImagePPM *readPPM(char *filename)
{
    FILE *fp = fopen(filename, "r");
    ImagePPM *image = malloc(sizeof(ImagePPM));

    if (fp == NULL) return NULL;

    fscanf(fp, "%s", image->magic);
    fscanf(fp, "%d", &image->width);
    fscanf(fp, "%d", &image->height);
    fscanf(fp, "%d", &image->max_value);

    image->pixels = malloc(sizeof(Pixel *) * image->height);
    for (int k = 0; k < image->height; k++) {
        image->pixels[k] = malloc(sizeof(Pixel) * image->width);
    }

        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fscanf(fp, "%d", &image->pixels[i][j].red);
                fscanf(fp, "%d", &image->pixels[i][j].green);
                fscanf(fp, "%d", &image->pixels[i][j].blue);
            }
        }    
    return image;
}

int writePGM(ImagePGM *pImagePGM, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return 0;
    fprintf(fp, "%s\n", pImagePGM->magic);
    fprintf(fp, "%d\n", pImagePGM->width);
    fprintf(fp, "%d\n", pImagePGM->height);
    fprintf(fp, "%d\n", pImagePGM->max_value);
    for (int i = 0; i < pImagePGM->height; i++) {
        for (int j = 0; j < pImagePGM->width; j++) {
            fprintf(fp, "%3d ", pImagePGM->pixels[i][j]); 
        }
        fprintf(fp, "\n");
    }
    return 1;
}

ImagePGM *extractRed(ImagePPM *pImagePPM)
{
    ImagePGM *gray = malloc(sizeof(ImagePPM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }
   
    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;
    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            gray->pixels[i][j] = pImagePPM->pixels[i][j].red;
        }
    }
    return gray;
}

ImagePGM *extractGreen(ImagePPM *pImagePPM)
{
    ImagePGM *gray = malloc(sizeof(ImagePPM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }

    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;
    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            gray->pixels[i][j] = pImagePPM->pixels[i][j].green;
        }
    }
    return gray;
}

ImagePGM *extractBlue(ImagePPM *pImagePPM)
{
    ImagePGM *gray = malloc(sizeof(ImagePPM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }

    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;
    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            gray->pixels[i][j] = pImagePPM->pixels[i][j].blue;
        }
    }
    return gray;
}

ImagePGM *computeAverage(ImagePPM *pImagePPM)
{
    ImagePGM *gray = malloc(sizeof(ImagePGM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    double avg = 0;
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }

    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;
    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            avg = 0;
            avg += pImagePPM->pixels[i][j].red;
            avg += pImagePPM->pixels[i][j].green;
            avg += pImagePPM->pixels[i][j].blue;
            gray->pixels[i][j] = round(avg / 3.0);
        }
    }
    return gray;
}

ImagePGM *computeLightness(ImagePPM *pImagePPM)
{
    int min = 0, max = 0;
    ImagePGM *gray = malloc(sizeof(ImagePGM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }

    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;

    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            min = pImagePPM->pixels[i][j].red;
            max = pImagePPM->pixels[i][j].red;
            if (pImagePPM->pixels[i][j].green > max) max = pImagePPM->pixels[i][j].green;
            if (pImagePPM->pixels[i][j].blue > max) max = pImagePPM->pixels[i][j].blue;
            if (pImagePPM->pixels[i][j].green < min) min = pImagePPM->pixels[i][j].green;
            if (pImagePPM->pixels[i][j].blue < min) min = pImagePPM->pixels[i][j].blue;
            gray->pixels[i][j] = round((min+max) / 2.0);
        }
    }
    return gray;
}

ImagePGM *computeLuminosity(ImagePPM *pImagePPM)
{
    ImagePGM *gray = malloc(sizeof(ImagePGM));
    gray->pixels = malloc(sizeof(int*) * pImagePPM->height);
    for (int i = 0; i < pImagePPM->height; i++) {
        gray->pixels[i] = malloc(sizeof(int) * pImagePPM->width);
    }

    strcpy(gray->magic, "P2");
    gray->width = pImagePPM->width;
    gray->height = pImagePPM->height;
    gray->max_value = pImagePPM->max_value;

    for (int i = 0; i < pImagePPM->height; i++) {
        for (int j = 0; j < pImagePPM->width; j++) {
            gray->pixels[i][j] = round((pImagePPM->pixels[i][j].red*0.21)+(pImagePPM->pixels[i][j].green*0.72)+(pImagePPM->pixels[i][j].blue*0.07));
        }
    }
    return gray;
}

void freeSpacePPM(ImagePPM *pImagePPM)
{
    for (int i = 0; i < pImagePPM->height; i++) {
        free(pImagePPM->pixels[i]);
    } 
    free(pImagePPM->pixels);
    free(pImagePPM);
}

void freeSpacePGM(ImagePGM *pImagePGM)
{
    for (int i = 0; i < pImagePGM->height; i++) {
        free(pImagePGM->pixels[i]);
    }
    free(pImagePGM->pixels);
    free(pImagePGM);
}
