#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // Size of bucket
    int length = 5;
    node *table[length];

    for (int i = 0; i < length; i++)
    {
        table[i] = NULL;
        if (table[i] == NULL)
        {
            printf("@ %i: NULL\n", i);
        }
    }

    node *n = malloc(sizeof(node));
    n->number = 1;
    n->next = NULL;

    table[5] = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(table[5]);
        return 1;
    }

    n->number = 5;
    n->next = NULL;

    n->next = table[5]; // pointing to previous linked node
    table[5] = n;

    for (node *tmp = table[5]; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    while (table[5] != NULL)
    {
        node *tmp = table[5]->next;
        free(table[5]);
        table[5] = tmp;
    }

    return 0;
}