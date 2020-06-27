#include<stdio.h>
#include<stdlib.h>

void writeDouble2DArrayToFile(double** greyScale, char* outputFile) {

}

int main(int argc, char** argv) {

    if(argc < 4) {
        printf("Combine <mask file> <output file> <grey file0> [grey file1] ...");
    }

    FILE* mask = fopen(argv[1], "r");
    printf("Opening '%s' for input\n", argv[1]);
    if(mask == NULL) {
        printf("ERROR: Can't open '%s' for input!\n", argv[1]);
        fclose(mask);
        return 0;
    }
    int rows = 0;
    int cols = 0;
    int maskRows = 0;
    int maskCols = 0;
    fscanf(mask, "%d%d", &maskRows, &maskCols);
    printf("Mask size: %d x %d\n", maskRows, maskCols);

    int* levels = malloc((argc - 3) * sizeof(int*));
    int level = 0;
    while(fscanf(mask, "%d", &level) != EOF) {
        levels[level]++;
    }

    for(int i = 0; i < argc - 3; i++) {
        printf("Mask %d: %.2f%%\n", i, (double) levels[i] / (rows * cols));
    }

    FILE* output = fopen(argv[2], "w");
    FILE** files = malloc((argc - 3) * sizeof(FILE*));
    for(int i = 0; i < argc - 3; i++) {
        files[i] = fopen(argv[i + 3], "r");
        printf("Opening '%s' for input\n", argv[1]);
        fscanf(files[i], "%d %d", &rows, &cols);
        if(files[i] == NULL) {
            printf("ERROR: Can't open '%s' for input!\n", argv[i + 3]);
            fclose(files[i]);
            return 0;
        } else if(rows != maskRows || cols != maskCols) {
            printf("ERROR: Input file '%s' size %d x %d invalid!", argv[i + 3], rows, cols);
        }
    }

    int* maskNum = malloc((rows * cols) * sizeof(int));
    double** fileImage = malloc((argc - 3) * sizeof(double));
    for(int i = 0; i < argc - 3; i++) {
        fileImage[i] = malloc((rows * cols) * sizeof(double));
    }
    double** outputArray = malloc(rows * sizeof(double));
    for(int i = 0; i < rows; i++) {
        outputArray[i] = malloc(cols * sizeof(double));
    }

    int i = 0;
    int j = 0;
    int k = 0;
    int whichFile = 0;

    while(fscanf(mask, "%d", &whichFile) != EOF) {
        if(k == cols) {
            j++;
            k = 0;
            printf("\n");
        }
        fscanf(mask, "%d", &maskNum[i]);
        for(int l = 0; l < argc - 3; l++) {
            fscanf(files[l], "%lf", &fileImage[l][i]);
        }
        outputArray[j][k] = fileImage[maskNum[i]][i];
        printf("%lf ", fileImage[maskNum[i]][i]);
        i++;
        k++;
    }

    fclose(mask);
    fclose(output);
    for(int i = 0; i < argc - 3; i++) {
        fclose(files[i]);
        free(files[i]);
        files[i] = NULL;
        free(fileImage[i]);
        fileImage[i] = NULL;
    }
    free(files);
    free(fileImage);
    files = NULL;
    fileImage = NULL;
    free(mask);
    for(int i = 0; i < rows; i++) {
        free(outputArray[i]);
        outputArray[i] = NULL;
    }
    free(outputArray);
    outputArray = NULL;

    


}