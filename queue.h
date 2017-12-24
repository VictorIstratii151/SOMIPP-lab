#ifndef QUEUE_H
#define QUEUE_H

struct queueNodeStruct
{
    void * data;
    struct queueNodeStruct * nextNode;
};

typedef struct queueNodeStruct QueueNode;

struct queueStruct
{
    QueueNode * head;
    QueueNode * tail;
    int size;
};

typedef struct queueStruct Queue;

Queue * newQueue();
void push(Queue * queue, void * data);
void * pop(Queue * queue);
int isEmpty(Queue * queue);
void printQueue(Queue queue, void (* itemPrint)(void * data));
void deleteQueue(Queue * queue);

void prepend(Queue * queue, void * data);

#endif