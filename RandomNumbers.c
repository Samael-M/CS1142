#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<stdbool.h>

/*
Samuel Milner
sjmilner@mtu.edu
CS1142

This is a pseudo random number generator. It takes in a number of bits, a seed, a tap bit and the number of numbers to be generated
It then generates the specified amount of numbers by turning the seed into a binary number of the specified amount of bits, and uses 
the xor operator on the most significant bit and the tap bit, does a left shift and inserts the new bit from the xor operation as the 
new right most bit. This process is repeated as many times as there are numbers to be generated.
*/

int main(int argc, char** argv) {
    if(argc < 5 ) {
        printf("RandomNumbers <bits> <seed> <tap bit> <numbers>");
        return 0;
    }

    int bits = atoi(argv[1]);
    int seed = atoi(argv[2]);
    int tapBits = atoi(argv[3]);
    int numbers = atoi(argv[4]);

    if(bits < 0 || bits > 31) {
        printf("Invalid input!");
        return 0;
    }
    if(seed < 0 || seed > pow(2, bits) - 1) {
        printf("Invalid input!");
        return 0;
    }
    if(tapBits < 0 || tapBits >= bits) {
        printf("Invalid input!");
        return 0;
    }

    bool buffer[bits];
    int tempbit = bits; 
    int tempSeed = seed;
    //a little magic here to convert decimal number to binary
    for(int i = bits; i > 0; i--) {
        if((tempSeed - pow(2, i - 1)) >= 0) {   //take rightmost bit and see if its 1 or 0
            buffer[bits - i] = 1;               //ex: with 8 bits and seed = 150, 2^7 = 128 which is smaller than seed so we put 1 there and subtract 128 from 150
            tempSeed = tempSeed - pow(2, i - 1);
        } else {
            buffer[bits - i] = 0;               //ex: with 8 bits and seed = 100, 2^7 = 128 which is larger than seed so we put 0 there
        }
        tempbit = tempbit / 2;                  //increment our bit down to next position
    }

    for(int i = 0; i < bits; i++) {
        printf("%d", buffer[i]);
    } printf(" = %d\n", seed);

    int decimalForm = 0;
    for(int i = 0; i < numbers - 1; i++) {
        bool A = buffer[bits - tapBits - 1] ^ buffer[0];    //A will be our new bit to insert at end of array after shifting to left
        for(int i = 0; i < bits - 1; i++) {                 //this for loop shifts each bit to the left
            buffer[i] = buffer[i + 1];
        }
        buffer[bits - 1] = A;                               //insert A after shifting

        for(int i = bits; i > 0; i--) {                 //this for loop turns our new binary number back to decimal
            if(buffer[bits - i] == 1){
                decimalForm = decimalForm + pow(2, i - 1);
            } 
        }

        for(int i = 0; i < bits; i++) {
            printf("%d", buffer[i]);
        } printf(" = %d\n", decimalForm);
        decimalForm = 0;
    }
}