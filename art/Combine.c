#include<stdio.h>
#include<stdlib.h>

//Samuel Milner
//CS1142

/*
* This program takes an input mask files, and any number of other greyscale files as input. 
* Using the mask file, this program combines the different greyscale files into a single one.
* Along with this the stats on the values in the final value are stored, These are number of values
* max value, min value and mean values
*/

//Stats struct stores number of values, mean value, maximum value and minimun value
typedef struct Stats {
    int nums;
    double min;
    double max;
    double mean;
} Stats;

//param: Stats struct
//prints out stats stored in stats struct
//Am I missing something here or is it really stupid to make us use a seperate function for a single print statement?
void printStats(Stats stats) {
    printf("count = %d, mean = %f, min = %f, max = %f\n", stats.nums, stats.mean, stats.min, stats.max);
}

//param: 2d array for greyscale image, int rows & cols for size of immage, string output, this is name of our output file
void computeStatsFromDouble2D(double** array, int rows, int cols, char* output) {
    Stats stats;
    FILE* out = fopen(output, "w");
    printf("Opening '%s' for output\n", output);
    if(out == NULL) {
        printf("Failed to open '%s' for output!\n", output);
        //fclose(mask);
        return;
    }
    fprintf(out, "%d %d\n", rows, cols);
    stats.nums = 0;
    stats.max = 0.0;
    stats.min = 1.0;
    stats.mean = 0.0;
    double total = 0;
    //iterate trhough 2d array, saving stats and printing to file as we go
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(array[i][j] > stats.max) {
                stats.max = array[i][j];
            } else if(array[i][j] < stats.min) {
                stats.min = array[i][j];
            }
            total += array[i][j];
            stats.nums++;
            fprintf(out, "%f ", array[i][j]);
        }
        fprintf(out, "\n");
    }
    stats.mean = total / stats.nums;
    fclose(out);
    printStats(stats);
}

int main(int argc, char** argv) {
    // printf friendly error if there arent enough command line arguments
    if(argc < 4) {
        printf("Combine <mask file> <output file> <grey file0> [grey file1] ...");
        return 0;
    }
    
    FILE* maskFile = fopen(argv[1], "r");
    printf("Opening '%s' for input\n", argv[1]);
    if(maskFile == NULL) {
        printf("ERROR: Can't open '%s' for input!\n", argv[1]);
        return 0;
    }

    int rows = 0;
    int cols = 0;
    //this is size of array of files, we use this a lot so I made it a variable for ease of use
    int size = argc - 3;
    fscanf(maskFile, "%d%d", &rows, &cols);
    printf("Mask size: %d x %d\n", rows, cols);

    //levels represents the different levels gotten from the mask file
    int maxLevel = size - 1;
    int* levels = calloc(size, sizeof(int*));
    int mask[rows * cols];
    int level = 0;
    int a = 0;
    while(fscanf(maskFile, "%d", &level) != EOF) {
        //we don't know how many different numbers are in mask as number of input files could be less that mask needs
        //so we resize our array if number of levels is more than number of input files
        if(level > maxLevel) {
            levels = realloc(levels, level);
            maxLevel = level;
        }
        levels[level]++;
        if(level > size - 1) {
            // a value of -1 is useful later, it denotes that we don't have an input file for that level.
            level = -1;
        }
        mask[a] = level;
        a++;
    }
    
    for(int i = 0; i <= maxLevel; i++) {
        printf("Mask %d: %.2f%%\n", i, (double) levels[i] / (rows * cols) * 100);
    }
    free(levels);
    levels = NULL;
    fclose(maskFile);
    //these values are to compare against rows and cols to make sure
    //all files ahve the smae dimensions
    int newRows = 0;
    int newCols = 0;
    
    FILE* files[size];
    //loop through command line arguments to open every files and put them in files array
    for(int i = 0; i < size; i++) {
        files[i] = fopen(argv[i + 3], "r");
        printf("Opening '%s' for input\n", argv[i + 3]);
        if(files[i] == NULL) {
            printf("ERROR: Can't open '%s' for input!\n", argv[i + 3]);
            return 0;
        } 
        fscanf(files[i], "%d %d", &newRows, &newCols);
        if(rows != newRows || cols != newCols) {
            printf("ERROR: Input file '%s' size %d x %d invalid!\n", argv[i + 3], newRows, newCols);
            return 0;
        }
    }
    
    //this array stores our output data
    double** outputArray = malloc(rows * sizeof(double));
    for(int i = 0; i < rows; i++) {
        outputArray[i] = malloc(cols * sizeof(double));
    }
    //2d array that stores all the greyscale numbers of all files
    //[i][j] where i is which file(matching with levels) and j is 
    //the greyscale numbers in that file
    double fileImage[size][rows * cols];

    //i is how many inputs through the file we are.
    int i = 0;
    //j is our rows
    int j = 0;
    //k is our cols
    int k = 0;

    //main loop goes from i = 0 to i = size of file. at each value the 
    //value at mask[i] determines which file to use the value from to put into the 2d array that represents the image
    while(i < rows * cols) {
        if(k == cols) {
            j++;
            k = 0;
        }
        for(int l = 0; l < size; l++) {
            fscanf(files[l], "%lf", &fileImage[l][i]);
        }
        if(mask[i] < 0) {
            outputArray[j][k] = 0.0;
        } else outputArray[j][k] = fileImage[mask[i]][i];
        
        i++;
        k++;
    }

    computeStatsFromDouble2D(outputArray, rows, cols, argv[2]);

    //Freeing memory allocated and closing files
    for(int i = 0; i < size; i++) {
        fclose(files[i]);
    }
    for(int i = 0; i < rows; i++) {
        free(outputArray[i]);
    }
    free(outputArray);
    return 0;

}