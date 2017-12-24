#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// void * foo(void * arg)
// {
//     int * sas = (int *) arg;

//     return sas;
// }

// void * bar(void * arg)
// {
//     int * sas = malloc(sizeof(*sas));
//     * sas =  * (int *) arg;

//     return sas;
// }

void printItem(void * data)
{
    printf("\n%d\n", *(int*)data);
}

int main()
{
    Queue * q = newQueue();
    push(q, (void*)1);
    push(q, (void*)2);
    push(q, (void*)3);
    push(q, (void*)4);
    push(q, (void*)5);

    printQueue(*q, printItem);

    // int aaa = 5;
    // int * bbb = &aaa;
    // prepend(q, (void*)bbb);

    // printQueue(*q, printItem);
}