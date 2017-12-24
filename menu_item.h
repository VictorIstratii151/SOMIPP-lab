#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#define ITEM_ARRAY_SIZE 8

struct menuItemStruct
{
    char * name;
    int preparation_time;
    int complexity;
    int prepared;
};

typedef struct menuItemStruct MenuItem;


MenuItem * newMenuItem(char * name, int preparation_time, int complexity);
void printItem(void * item);
MenuItem * generateItems(int number);

#endif