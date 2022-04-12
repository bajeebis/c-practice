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

    if (table[3] == NULL)
    {
        printf("Nothing at 3\n");
    }

    node *n = malloc(sizeof(node));
    n->number = 1;
    n->next = NULL;

    table[3] = n;

    if (table[3] != NULL)
    {
        printf("There's something inside\n");
    }

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(table[3]);
        return 1;
    }

    n->number = 3;
    n->next = NULL;

    n->next = table[3]; // pointing to previous linked node
    table[3] = n;

    for (node *tmp = table[3]; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    while (table[3] != NULL)
    {
        node *tmp = table[3]->next;
        free(table[3]);
        table[3] = tmp;
    }

    return 0;
}