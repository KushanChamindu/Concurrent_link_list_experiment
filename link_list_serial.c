#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "list_node_s.h"
#include <sys/time.h>
#include <string.h>
#define n 1000
#define m 10000
#define MAX 65535
#define MIN 0
#define sample_size 500

struct list_node_s link_list;  //link list head
struct list_node_s *ptr; //link list pointer
char operation_order[m][7] = {};  //operation order array
float m_member;
float m_insert;
float m_delete;

float time_per_sample()
{
    clock_t time; //timer initiate
    link_list.data = 2;
    link_list.next = NULL;

    ptr = &link_list; 

    int *random_array_pointer = getRandom();   //get randam interger array

    for (int loop = 0; loop < n; loop++)
    {
        int var = *(loop + random_array_pointer);
        Insert(var, &ptr);  // insert random interger to the linked list
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
    shuffle(operation_order, m);  //operation array shuffle

    long loop = 0; 
    time = clock();  // timmer initiate
    while (loop < m)  // operation execute according to the shuffle operation order list
    {

        if (strcmp(operation_order[loop], "Member") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            Member(var, &link_list);
        }
        else if (strcmp(operation_order[loop], "Insert") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            Insert(var, &ptr);
        }
        else if (strcmp(operation_order[loop], "Delete") == 0)
        {
            int var = rand() % (MAX + 1 - MIN) + MIN; // radomly generated value for execute the basic operations
            Delete(var, &ptr);
        }
        loop++;
    }
    
    time = clock() - time;
    float time_taken = ((float)time) / CLOCKS_PER_SEC;
    return time_taken; //return execute time for the one sample
}

int main(int argc, char *argv[])
{

    float time_array[sample_size]; //initiate time array
    //take fraction of basic operation
    printf("\nEnter m member fractions: ");
    scanf("%f", &m_member);

    printf("Enter m insert fractions: ");
    scanf("%f", &m_insert);

    printf("Enter m delete fractions: ");
    scanf("%f", &m_delete);


    float time_taken_per_sampe;
    for (size_t i = 0; i < sample_size; i++)  //sample size execution
    {
        time_taken_per_sampe = time_per_sample();
        // printf("time %ld \n", time);
        time_array[i] = time_taken_per_sampe;  //input execution time to the time array
    }

    float mean = get_mean(time_array, sample_size);  //take mean of the time array
    float std = get_std(time_array, sample_size, mean); //take std od the time array

    printf("mean = %f \n", mean);
    printf("std = %f \n", std);

    return 0;
}

// gcc -g -Wall -o .\link_list_serial .\link_list_serial.c  .\insert.c .\member.c .\delete.c      =================  code run