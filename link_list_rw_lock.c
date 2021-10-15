#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "list_node_s.h"
#include <time.h>
#include <string.h>
#include <pthread.h>
#define n 1000
#define m 10000
#define MAX 65535
#define MIN 0
#define sample_size 500

int thread_count;
pthread_rwlock_t rw_lock;
struct list_node_s link_list;    //link list head
char operation_order[m][7] = {}; //operation order array
struct list_node_s *ptr;         //link list pointer
float m_member;
float m_insert;
float m_delete;
float time_array[sample_size]; //timie array iniate
pthread_t *thread_headler;

void *Thread_function(void *rank) //thread function
{
    long my_rank = (long)rank; //take thrad id
    float local_start, local_end, local_gap;
    // load balansing part
    local_gap = m / thread_count;
    local_start = my_rank * local_gap;
    local_end = local_start + local_gap;
    for (int loop = local_start; loop < local_end; loop++)  // accoridng to the load blancong thread exceute operation
    {
        if (strcmp(operation_order[loop], "Member") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            pthread_rwlock_rdlock(&rw_lock); //read lock
            Member(var, &link_list);
            pthread_rwlock_unlock(&rw_lock); //read unlock
        }
        else if (strcmp(operation_order[loop], "Insert") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            pthread_rwlock_wrlock(&rw_lock); //write lock
            Insert(var, &ptr);
            pthread_rwlock_unlock(&rw_lock); //write unlock
        }
        else if (strcmp(operation_order[loop], "Delete") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            pthread_rwlock_wrlock(&rw_lock);  //write lock
            Delete(var, &ptr);
            pthread_rwlock_unlock(&rw_lock);  //write unlock
        }
    }
    return NULL;
}
float time_per_sample()
{
    clock_t time; //timer initiate
    link_list.data = 2;
    link_list.next = NULL;
    ptr = &link_list;

    int *random_array_pointer = getRandom(); //get randam interger array

    for (int loop = 0; loop < n; loop++)
    {
        int var = *(loop + random_array_pointer);
        Insert(var, &ptr);   // insert random interger to the linked list
        // printf("%d ", var);
    }
// operation order list initiate
    for (int i = 0; i < m; i++)
    {
        if (i < m * m_member)
        {
            strcpy(operation_order[i], "Member");
        }
        else if (i < m * m_member + m * m_insert)
        {
            strcpy(operation_order[i], "Insert");
        }
        else if (i < m * m_member + m * m_insert + m * m_delete)
        {
            strcpy(operation_order[i], "Delete");
        }
    }

    shuffle(operation_order, m);   //operation array shuffle
    ////// thread creation and joining
    pthread_rwlock_init(&rw_lock, NULL);  // Initializing the READ-WRITE LOCK
    long thread_number = 0;
    time = clock();
    // Thread Creation
    while (thread_number < thread_count)
    {
        pthread_create(&thread_headler[thread_number], NULL, Thread_function, (void *)thread_number);
        thread_number++;
    }

    // Thread Join
    thread_number = 0;
    while (thread_number < thread_count)
    {
        pthread_join(thread_headler[thread_number], NULL);
        thread_number++;
    }

    time = clock() - time;
    float time_taken = ((float)time) / CLOCKS_PER_SEC;
    pthread_rwlock_destroy(&rw_lock);  // Destroying the read-write lock
    return time_taken;  //return execute time for the one sample
}

int main(int argc, char *argv[])
{
    thread_count = strtol(argv[1], NULL, 10);  //take thread count
    thread_headler = malloc(thread_count * sizeof(pthread_t));  // memory allocation for the thread object array

  //take fraction of basic operation
    printf("\nEnter m member fractions: ");
    scanf("%f", &m_member);

    printf("Enter m member fractions: ");
    scanf("%f", &m_insert);

    printf("Enter m member fractions: ");
    scanf("%f", &m_delete);

    float time_taken_per_sampe;
    for (size_t i = 0; i < sample_size; i++)  //sample size execution
    {
        time_taken_per_sampe = time_per_sample();
        // printf("time %ld \n", time);
        time_array[i] = time_taken_per_sampe;  //input execution time to the time array
    }

    float mean = get_mean(time_array, sample_size); //take mean of the time array
    float std = get_std(time_array, sample_size, mean); //take std od the time array


    printf("mean = %f \n", mean);
    printf("std = %f \n", std);
    free(thread_headler);   // memory free
    return 0; 
}