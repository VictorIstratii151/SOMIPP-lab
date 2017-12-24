#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "queue.h"
#include "globals.h"
#include "menu_item.h"
#include "utils.h"
#include "order.h"
#include "cook.h"

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}



Queue * priority_1_orders;
Queue * priority_2_orders;
Queue * priority_3_orders;
Queue * priority_4_orders;
Queue * priority_5_orders;

struct cookingInfoStruct
{
    Order * order;
    MenuItem * item;
};

typedef struct cookingInfoStruct CookingInfo;

static Queue * order_queues[5];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int order_count = 0;

Cook * cooks;

void * preparation_thread(void * arg)
{
    printf("Item preparation thread\n");
    CookingInfo * bundle = (CookingInfo *) arg;

    Order * order = bundle->order;
    MenuItem * item = bundle->item;

    sleep(item->preparation_time * TIME_UNIT);
    item->prepared = 1;

    order->start_execution = clock();
    // printf("%Lf\n", (long double)order->start_execution);
}


void * waiter_thread(void * arg)
{
    while(1)
    {
        printf("printing queues\n\n");
        int limit = 0;
        int i;

        for(i = 0; i < MAX_PRIORITY; i++)
        {
            printf("Queue no. %d\n", i+1);
            printQueue(*order_queues[i], printOrder);
            limit += order_queues[i]->size;
            printf("%d\n", limit);
        }
        printf("\n");
        if(limit < 10)
        {
            int order_length = randInt(1, ITEM_ARRAY_SIZE);
            MenuItem * items_array = generateItems(order_length);
            int j;

            int priority = randInt(MIN_PRIORITY, MAX_PRIORITY);

            double wait_times[order_length];

            for(j = 0; j < order_length; j++)
            {
                wait_times[j] = items_array[j].preparation_time;
            }

            double max_wait = findMax(wait_times, order_length) * 1.3;

            pthread_mutex_lock(&mutex);

            order_count += 1;
            Order * order = newOrder(order_count, order_length, priority, max_wait, items_array);

            push(order_queues[priority - 1], order);

            pthread_mutex_unlock(&mutex);
        }
        sleep(randInt(1 * TIME_UNIT, 10 * TIME_UNIT));
    }
}

void * cook_thread(void * arg)
{
    Cook * working_cook = (Cook *) arg;
    printf("Cook no.%d\n", working_cook->id);

    while(1)
    {
        int i;
        int j;
        int k;
        int items_completed = 0;

        for(i = 0; i < MAX_PRIORITY; i++)
        {
            // sleep(2);
            Queue * current_order_queue = order_queues[i];
            if(!isEmpty(current_order_queue))
            {
                pthread_mutex_lock(&mutex);

                Order * executing_order = pop(current_order_queue);

                if(!isEmpty(current_order_queue))
                {
                    if (executing_order->start_execution != 0.0 && executing_order->end_execution != 0.0)
                    {
                        printf("START: %Lf\n", (long double)executing_order->start_execution);
                        printf("END: %Lf\n", (long double)executing_order->end_execution);
                    }

                    for(k = 0; k < executing_order->order_length; k++)
                    {
                        if(executing_order->items[k].prepared == 1)
                        {
                            items_completed += 1;
                        }
                    }

                    if(items_completed == executing_order->order_length)
                    {
                        clock_t end_time = clock();
                        executing_order->end_execution = end_time;
                    }

                    pthread_t test_thread[executing_order->order_length];

                    for(j = 0; j < executing_order->order_length; j++)
                    {
                        MenuItem * executing_item = &executing_order->items[j];
                        CookingInfo * info = malloc(sizeof(*info));
                        info->order = executing_order;
                        info->item = executing_item;
                        clock_t start_time = clock();
                        executing_order->start_execution = start_time;
                        
                        pthread_create(&test_thread[j], NULL, preparation_thread, (void *) info);
                    }
                    // printf("-----------------------------------------PREPARED ORDER NO. %d-------\n", executing_order->id);
                    // printOrder(executing_order);

                    for(j = 0; j < working_cook->proficiency; j++)
                    {
                        clock_t end;
                        pthread_join(test_thread[j], (void **) &end);
                    }
                }
                pthread_mutex_unlock(&mutex);
            }
        }
        sleep(1);
    }
}


int main()
{
    priority_1_orders = newQueue();
    priority_2_orders = newQueue();
    priority_3_orders = newQueue();
    priority_4_orders = newQueue();
    priority_5_orders = newQueue();

    order_queues[0] = priority_1_orders;
    order_queues[1] = priority_2_orders;
    order_queues[2] = priority_3_orders;
    order_queues[3] = priority_4_orders;
    order_queues[4] = priority_5_orders;

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    cooks = malloc(NUM_COOKS * sizeof(*cooks));
    int p_count;
    int r_count;
    int cook_index = 0;
    int cook_id = 0;
    int i;

    for(p_count = 0; p_count < 4; p_count++)
    {
        for(r_count = 0; r_count < 3; r_count++)
        {
            cook_id += 1;
            Cook * temp = newCook(cook_id, r_count + 1, p_count + 1);
            cooks[cook_index].id = cook_id;
            cooks[cook_index].rank = temp->rank;
            cooks[cook_index].proficiency = temp->proficiency;
            cook_index += 1;
        }
    }

    pthread_t threads[NUM_COOKS];
    pthread_t order_creating_thread;
    pthread_t order_creating_thread2;
    pthread_t order_creating_thread3;


    pthread_create(&order_creating_thread, NULL, waiter_thread, NULL);
    pthread_create(&order_creating_thread2, NULL, waiter_thread, NULL);
    pthread_create(&order_creating_thread3, NULL, waiter_thread, NULL);



    for(i = 0; i < NUM_COOKS; i++)
    {
        pthread_create(&threads[i], NULL, cook_thread, (void *) &cooks[i]);
    }


    pthread_join(order_creating_thread, NULL);
    pthread_join(order_creating_thread2, NULL);
    pthread_join(order_creating_thread3, NULL);


    for(i = 0; i < NUM_COOKS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    

    return 0;
}