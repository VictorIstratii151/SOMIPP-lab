#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue * newQueue()
{
    Queue * queue = malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    queue->size = 0;

    return queue;
}

int isEmpty(Queue * queue)
{
    return queue->size == 0;
}

void push(Queue * queue, void * data)
{
    QueueNode * newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->nextNode = NULL;
    if(isEmpty(queue))
    {
        queue->head = queue->tail = newNode;
    }
    else
    {
        queue->tail->nextNode = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

void * pop(Queue * queue)
{
    if(isEmpty(queue))
    {
        return NULL;
    }

    QueueNode * temp = queue->head;
    void * retrieveData = queue->head->data;

    queue->head = queue->head->nextNode;
    
    free(temp);
    queue->size--;

    return retrieveData;
}

void printQueue(Queue queue, void (* itemPrint)(void * data))
{
    if(isEmpty(&queue))
    {
        printf("Queue empty.\n");
    }
    else
    {
        QueueNode * temp = queue.head;
        while(temp)
        {
            (* itemPrint)(temp->data);
            temp = temp->nextNode;
        }
    }
}

void deleteQueue(Queue * queue)
{
    if(isEmpty(queue))
    {
        free(queue);
    }
    else
    {
        QueueNode * temp = queue->head;
        while(temp)
        {
            printf("%zd\n", sizeof(queue));
            QueueNode * temp1 = temp;
            temp = temp->nextNode;
            free(temp1);
            queue->size -= 1;
        }

        queue->head = queue->tail = NULL;
    }
}

void prepend(Queue * queue, void * data)
{
    QueueNode * newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->nextNode = NULL;
    if(isEmpty(queue))
    {
        queue->head = queue->tail = newNode;
    }
    else
    {
        newNode->nextNode = queue->head;
        queue->head = newNode;
    }

    queue->size++;
}