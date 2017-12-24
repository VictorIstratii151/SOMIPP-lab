#include "order.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

Order * newOrder(int id, int order_length, int priority, int max_wait, MenuItem * menu_items)
{
    Order * order = malloc(sizeof(*order));

    order->id = id;
    order->order_length = order_length;
    order->priority = priority;
    order->max_wait = max_wait;
    order->items = menu_items;
    order->start_execution = 0.0;
    order->end_execution = 0.0;
    
    return order;
}

void removeOrder(Order * order)
{
    int i;

    order->id = 0;
    order->priority = 0;
    order->max_wait = 0.0;
    order->order_length = 0;
    free(order->items);
    free(order);
}

void printOrder(void * order)
{
    Order * myOrder = (Order *) order;
    int i;
    printf("\n");
    printf("Order no.%d\n", myOrder->id);
    printf("priority: %d\n", myOrder->priority);
    printf("max. wait time: %f\n", myOrder->max_wait);
    printf("menu items:\n");
    for(i = 0; i < myOrder->order_length; i++)
    {
        printItem(&(myOrder->items[i]));
    }
    printf("\n");
}