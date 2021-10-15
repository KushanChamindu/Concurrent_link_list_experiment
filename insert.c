#include <stdio.h>
#include <stdlib.h>
#include "list_node_s.h"
#include "functions.h"

int Insert(int value, struct list_node_s** head_pp)
{
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;
    while (curr_p != NULL && curr_p -> data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL) // New first node
            *head_pp = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    }
    else
    { // value  already in list
        return 0;
    }
} //insert