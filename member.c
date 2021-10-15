#include <stdio.h>
#include <stdlib.h>
#include "list_node_s.h"
#include "functions.h"
/* Member */
int Member(int value, struct list_node_s* head_p)
{
    struct list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }

} 