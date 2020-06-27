#include <stdio.h>
#include <stdlib.h>

//Samuel Milner
//SC1142

/*
* This program takes in an rgb filse which represents a picture and converts it into 
* a greyscale file. It takes in a single rbg file from command standard input
* and outputs file through standard output
*/

int main(void) {

    int Red = 0;
    int Green = 0;
    int Blue = 0;
    double greyScaleShade = 0;

    int rows = 0;
    int cols = 0;
    scanf("%d", &rows);
    scanf("%d", &cols);
    printf("%d %d\n", rows, cols);
    //main loops go through each column and row, turning each value into a grescale one
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &Red);
            scanf("%d", &Green);
            scanf("%d", &Blue);

            greyScaleShade = (0.299 * ((double) Red / 255.0)) + (0.587 * ((double) Green / 255.0)) + (0.114 * ((double) Blue / 255.0));
            printf("%.6f ", greyScaleShade);
        }
        printf("\n");
    }
    return 0;
}