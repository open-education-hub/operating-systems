#include <stdlib.h>

#define N 500000

typedef struct Image
{
    int pixelMatrix[50][50];
    int someOtherField;
}Image;

void printImage(Image img)
{
    /* code to print the image */
}

void main()
{
    Image *imgArray = malloc(N * sizeof(Image));

    /* do some initializations and some work with imgArray */

    /* now print the images */
    for (int i = 0; i < N; i++)
        printImage(imgArray[i]);
}
