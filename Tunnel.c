#include <stdlib.h>
#include <stdio.h>

/*
Samuel Milner
sjmilner@mtu.edu
CS1142

This program simulates a cave in. There is a grid with integers 1-9 where the number reperesnts the diffuctly to break through there. 
This program finds a way out by choosing the easiet available area to break through. The goal is to get to the rightmost side

*/
void printMap(int columns, int rows, int cave[][columns]) //this method prints out the map
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (cave[i][j] > 9)
            {
                printf("."); //areas traveled through will be changed to 10, so this marks them with a .
            }
            else
            {
                printf("%d", cave[i][j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Tunnel <start row> [verbose]\n");
        return 0;
    }

    //initialize variables we are going to use
    int columns = 0;
    int rows = 0;
    int size = 0;
    double average = 0.0;
    int min = 9;
    int max = 0;

    scanf("%d", &rows);
    if (atoi(argv[1]) > rows - 1)
    {
        printf("Invalid starting row!\n");
        return 0;
    }
    scanf("%d", &columns);
    size = columns * rows;
    int cave[rows][columns];
    int temp = 0;
    int length = 1;
    //nested for loops go through the grid and scan in numbers, finding the min and max as it goes through them
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            scanf("%d", &temp);
            cave[i][j] = temp;
            if (cave[i][j] < min)
            {
                min = cave[i][j];
            }
            if (cave[i][j] > max)
            {
                max = cave[i][j];
            }
            average = average + cave[i][j];
        }
    }
    average = average / size;
    printf("Data points: %d\nAvg difficulty: %.3f\nMin difficulty: %d\nMax difficulty: %d\n\n", size, average, min, max);
    int positionY = atoi(argv[1]);
    int positionX = 0;

    int options[4]; //this represents the options available direction to go; 0 is left, 1 is up, 2 is down and 3 is right
    int cost = cave[positionY][positionX];
    int direction = 0;
    do //main loop for algorithm to find a way out
    {
        cave[positionY][positionX] = 10;

        //This set of if statements to to make sure we dont go out of bounds if we are on the edge of the map
        //as we are looking a the directions we can go and their cost

        if (positionX == 0)
        {
            options[0] = 10;
        } else
            options[0] = cave[positionY][positionX - 1];
        if (positionY == 0)
        {
            options[1] = 10;
        }else
            options[1] = cave[positionY - 1][positionX];
        if (positionY == rows - 1)
        {
            options[2] = 10;
        }else
            options[2] = cave[positionY + 1][positionX];

        options[3] = cave[positionY][positionX + 1];

        int min = 10;
        //go through our options to find which is easiet to get through
        for (int i = 0; i < 4; i++)
        {
            if (options[i] <= min)
            {
                min = options[i];
                direction = i; //keep track of which directions we want for min we 0-3 repersent directions stated earlier
            }
        }
        if (min > 9) // we have run out of places to go
        {
            break;
        }
        cost += min;
        //move to next area
        if (direction == 0)
        {
            positionX--;
        }
        else if (direction == 1)
        {
            positionY--;
        }
        else if (direction == 2)
        {
            positionY++;
        }
        else
        {
            positionX++;
        }

        if (argc > 2)
        {
            if (atoi(argv[2]) > 0) //if 3rd argument is an int larger than 0 print out map after each step
            {
                printMap(columns, rows, cave);
                printf("\n");
            }
        }
        length++;

    } while (positionX < columns - 1);

    cave[positionY][positionX] = 10;
    printMap(columns, rows, cave);
    printf("\nLength = %d\nCost = %d\n", length, cost);
    return 0;
}
