#include "utils.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

MenuItem * newMenuItem(char * name, int preparation_time, int complexity)
{
    MenuItem * item = malloc(sizeof(MenuItem));
    item->name = name;
    item->preparation_time = preparation_time;
    item->complexity = complexity;
    item->prepared = 0;

    return item; 
}

MenuItem * generateItems(int number)
{
    int i = 0;

    MenuItem * itemArray = malloc(number * (sizeof(*itemArray)));

    for(i = 0; i < number; i++)
    {
        int food_index = randInt(0, ITEM_ARRAY_SIZE - 1);
        MenuItem temp = foods[food_index];
        itemArray[i] = *(newMenuItem(temp.name, temp.preparation_time, temp.complexity));
    }

    return itemArray;
}

void printItem(void * item)
{
    MenuItem * myItem = (MenuItem *)item;
    printf("prepared: %s\n", (myItem->prepared == 1) ? "yes" : "no");
    printf("name: %s\n", myItem->name);
    printf("cooking time: %d\n", myItem->preparation_time);
}