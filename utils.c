#include <stdlib.h>

int randInt(int minimum_number, int max_number)
{
    return rand() % (max_number + 1 - minimum_number) + minimum_number;
}

double findMax(double array[], int arr_length)
{
    int i;
    double max = array[0];
    for(i = 0; i < arr_length; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}