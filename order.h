#ifndef ORDER_H
#define ORDER_H

#include "globals.h"
#include <time.h>

struct orderStruct 
{
    int id;
    clock_t start_execution;
    clock_t end_execution;
    int order_length;
    int priority;
    double max_wait;
    MenuItem * items;
};

typedef struct orderStruct Order;
Order * newOrder(int id, int order_length, int priority, int max_wait, MenuItem * menu_items);
void removeOrder(Order * order);
void printOrder(void * order);


#endif