#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// We assue all words are no more than 63 characters long.
// This requires 64 characters in any array that holds a word since we need 1 for null.
// Instead of sprinkling the magic number 64 everywhere in your code, you should instead
// use the following constant:
#define WORD_ARRAY_SIZE 64

// Function prototypes, this allows the function implementations to appear in any order in the file
// You will be implementing these three functions.
unsigned int hashString(char *str);
double calcUnigramLogProb(unsigned int count, unsigned long total);
void stripUpper(char *str);

// Function prototypes for the test functions we have provided
void testHashString();
void testCalcUnigramLogProb();
void testStripUpper();

// Hash a null-terminated string to an unsigned int.
// Implement as in Java's hashCode for String s, calculates this equation:
//   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]  (^ denotes exponentiation)
//
// You can follow the Java source code in this discussion: http://tinyurl.com/pqg2al5
//
// NOTE: While the above equation uses exponentiation, it is quite expensive and
// unnecessary to call the pow() function for each character. Also you will not get
// the same answer as us for long strings. You can do the calculation using only
// multiplication and addition. HINT: Can you reorder the calculation?
unsigned int hashString(char *str)
{
   int hash = 0;
   char *t;
   int i = 0;
   for (t = str; *t; t++)
   {
      hash = 31 * hash + str[i];
      i++;
   }

   return hash;
}

// Calculate log probability of a word occurring count times in total words of data.
// Result is in log base 10.
double calcUnigramLogProb(unsigned int count, unsigned long total)
{
   return log10(count) - log10(total);
}

// Strip the null-terminated string str of characters that aren't letters or apostrophe.
// Converts all lowercase letters to uppercase.
// This operates in place on the string str.
void stripUpper(char *str)
{

   char *word = str;
   int i = 0;
   int j = 0;
   while (str[i] != 0)
   {
      if (122 >= str[i] && str[i] >= 97)
      {
         str[i] -= 32;
         word[j] = str[i];
         j++;
      }
      else if (90 >= str[i] && str[i] >= 65)
      {
         word[j] = str[i];
         j++;
      }
      else if (str[i] == 39)
      {
         word[j] = str[i];
         j++;
      }
      i++;
   }
   //printf("%s\n", word);
   word[j] = '\0';
   str = word;
   //strcpy(str, word);
}

// Test function for the hashString function.
// Do NOT change this function.
void testHashString()
{
   char tests[][WORD_ARRAY_SIZE] = {"BAD", "DAB", "GOODFELLOWS", "WRITERSHIP", "a", "A", "abcdefghijklmnopqrstuvwxyz", "1234567890!@#$%^&*()", ""};

   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> %u\n", tests[i], hashString(tests[i]));
      i++;
   }
}

// Test function for the calcUnigramLogProb function.
// Do NOT change this function.
void testCalcUnigramLogProb()
{
   const int SIZE = 8;
   unsigned int counts[] = {5, 50, 1, 1, 1234, 0, 100, 1};
   unsigned long totals[] = {10, 100, 100, 2000, 567890, 123, 100, 1};

   for (int i = 0; i < SIZE; i++)
   {
      printf("%5u %7lu -> %9.6f\n", counts[i], totals[i], calcUnigramLogProb(counts[i], totals[i]));
   }
}

// Test function for the stripUpper function.
// Do NOT change this function.
void testStripUpper()
{
   char tests[][WORD_ARRAY_SIZE] = {"bad", "BAD", "BaD", "CAN'T", "well-done", "!L00K-", "1234567890", ""};

   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> ", tests[i]);
      stripUpper(tests[i]);
      printf("\"%s\" (len %zu)\n", tests[i], strlen(tests[i]));
      i++;
   }
}

int main(int argc, char **argv)
{
   // If no command line input we print out a help message and also run test functions
   if (argc <= 1)
   {
      printf("Usage: Unigram <hash table size> [debug]\n\n");
      testHashString();
      printf("\n");
      testCalcUnigramLogProb();
      printf("\n");
      testStripUpper();
      return 0;
   }

   int hashTableSize;
   if(atoi(argv[1]) > 0) {
      hashTableSize = atoi(argv[1]);
   } else {
      printf("Table size must be positive!\n");
      return 0;
   }
   char word[WORD_ARRAY_SIZE];
   char hashTable[hashTableSize][WORD_ARRAY_SIZE];
   int numOfWords[hashTableSize];

   for (int i = 0; i < hashTableSize; i++)
   {
      *hashTable[i] = '\0';
      numOfWords[i] = 0;
   }

   int bucket = 0;
   long count = 0;
   int debug = 0;
   int index = 0;
   if(argc > 2) {
      debug = atoi(argv[2]);
   }
   //testCalcUnigramLogProb();
   
   while (scanf("%63s", word) == 1)
   {
      stripUpper(word);
      bucket = hashString(word) % hashTableSize;
      index = bucket;
      if (*hashTable[bucket] == '\0')
      {
         strcpy(hashTable[index], word);
         numOfWords[index] = +1;
         count++;
      }
      else if (strcmp(hashTable[bucket], word) == 0)
      {
         numOfWords[index] += 1;
         count++;
      }
      else if (strcmp(hashTable[index], word) != 0)
      {
         index++;
         while(1) {
            if(index == hashTableSize) index = 0;
            if(index == bucket) {
               printf("ERROR: hash table is full!\n");
               return 0;
            }
            if(*hashTable[index] == '\0') {
               strcpy(hashTable[index], word);
               numOfWords[index] = +1;
               count++;
               break;
            } else if(strcmp(hashTable[index], word) == 0) {
               numOfWords[index]++;
               count++;
               break;
            }
            index++;
         }
      }
      if (debug != 0)
      {
         printf("%s -> hash %d, bucket %d, stored at %d, count %d\n", word, hashString(word), bucket, index, numOfWords[bucket]);
      }
   } 
   double prob = 0.0;
   for (int i = 0; i < hashTableSize; i++)
   {
      if (*hashTable[i] != '\0')
      {
         prob = calcUnigramLogProb(numOfWords[i], count);
         printf("%.6f %s\n", prob, hashTable[i]);
      }
   }
return 0;
}



