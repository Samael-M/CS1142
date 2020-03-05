#include <stdlib.h>
#include <stdio.h>

/*
Samuel Milner
sjmilner@mtu.edu
CS1142

This program takes in a number, probability, seed and list of words. It then generates as many pseudo random
sentences as specified. The probability input determines likely hood that the program will add another word to a sentence after each word is added
*/

int main(int argc, char** argv) {

    if(argc < 5 ) {
        printf("SentenceInventor <number> <probability> <seed> <word1> [word2] ...");
        return 0;
    }

    int number = atoi(argv[1]);
    double prob = atof(argv[2]);
    int seed = atoi(argv[3]);
    int size = argc - 4; // number of words available to us to use
    srand(seed);
    int count = number; // tracks how many words are printed
    for(int i = 0; i < number; i++) {

        int nextWord = rand() % size; //random number to select what the next word is going to be
        printf("%s", argv[nextWord + 4]);

        double probOfWord = (double) (rand() % 10 + 1) / 10.0; //random numbe rfrom 0.0 to prob to see if there will be another word
        while(probOfWord <= prob) {
            nextWord = rand() % size; //random number to select what the next word is going to be
            printf(" %s", argv[nextWord + 4]);
            probOfWord = (double) (rand() % 10 + 1) / 10.0; //random numbe rfrom 0.0 to prob to see if there will be another word
            count++; // new word in string was added
        } printf(".\n");
    }

    printf("Total sentences = %d ", number);
    printf("\nAverage words per sentence = %.2f", (double) count / (double) number);
    return 0;
}