#include <stdio.h>
#include <stdlib.h>

//Samuel Milner
//CS1142

/*
* This program takes in a single greyscale file from standard input
* and prints out an ascii representaion of the greyscale image through
* standard output
*/

//this function draws the top and bottom line fo the art
void drawLine(int cols) {
    printf("+");
    for(int i = 0; i < cols; i++) printf("-");
    printf("+\n");
}

int main(int argc, char** argv) {

    // represent shade
    double greyScaleShade = 0;
    //modifies output if present
    double delta = 0;
    if(argc > 1) {
        delta = atof(argv[1]);
    }

    int rows = 0;
    int cols = 0;
    scanf("%d", &rows);
    scanf("%d", &cols);
    drawLine(cols);
    //loop checks value in pixelArt and prints out a certain ascii char based on value
    for(int i = 0; i < rows; i++) {
        printf("|");
        for(int j = 0; j < cols; j++) {
            scanf("%lf", &greyScaleShade);
            greyScaleShade += delta;
            if(greyScaleShade < 0.2) {
                printf(" ");
            } else if(greyScaleShade < 0.4) {
                printf(".");
            } else if(greyScaleShade < 0.6) {
                printf("o");
            } else if(greyScaleShade < 0.8) {
                printf("O");
            } else if(greyScaleShade >= 0.8) {
                printf("@");
            }
        }
        printf("|");
        printf("\n");
    }
    drawLine(cols);
    return 0;
}