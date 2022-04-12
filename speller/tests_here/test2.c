#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char* word);

#define ALLOCATION 10

typedef struct node
{
    char name[ALLOCATION + 1];
    struct node *next;
}
node;

const unsigned int size = 4;

node *name_table[size];

int main(void)
{

    node *n = malloc(sizeof(node));

    char first_name[7] = "julian";

    strcpy(n->name, first_name);
    n->next = NULL;

    name_table = n;

    node *p = malloc(sizeof(node));

    char second_name[8] = "richard";
    strcpy(p->name, second_name);
    p->next = NULL;

    p->next = name_table;
    name_table = p;

    for (node *tmp = name_table; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(tmp->name, "julian") == 0)
        {
            printf("Found julian!\n");
        }
    }

    while (name_table != NULL)
    {
        node *tmp = name_table->next;
        free(name_table);
        name_table = tmp;
    }

}

unsigned int hash(const char* word)
{
    
}