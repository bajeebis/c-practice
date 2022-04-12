#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define bucket 9

unsigned int hash(const char *word);

int main(void)
{
    char *user_input;

    //take in input
    printf("Input name: ");
    scanf("%m[a-z]", &user_input);
    //int count = strlen(user_input);
    //char name[count];
    //strcpy(user_input, name);

    printf("Name: %s\n", user_input);

    printf("Hash value: %i\n", hash(user_input));

    free(user_input);
}

unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        printf("int c = %i\n", c);  // Visualization of function
        hash = ((hash << 5) + hash) + tolower(c);

        printf("hash = %lu\n\n", hash);  // Visualize function
    }
    return hash % bucket;
}