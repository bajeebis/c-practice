// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Number words in the dictionary
unsigned int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int n = hash(word);

    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(tmp->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*
    djb2 hash function
    source: http://www.cse.yorku.ca/%7Eoz/hash.html
    */

    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        //printf("int c = %i\n", c);  // For visualization
        hash = ((hash << 5) + hash) + tolower(c);

        //printf("hash = %lu\n\n", hash);  // For visualization
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict_file = fopen(dictionary, "r");

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char buffer[LENGTH];
    while (fscanf(dict_file, "%s", buffer) != EOF)
    {
        // Initiate node
        node *n = malloc(sizeof(node));

        if (n != NULL)
        {
            strcpy(n->word, buffer);  // Copying into the buffer
            n->next = NULL;

            int location = hash(buffer);  // Get the hash value for the table location
            //printf("Hash value: %i\n", location);

            wordCount += 1;

            /*
            This check is for the first value and subsequent checks
            if there is something it's pointing to. Then this check will
            switch pointers
            */
            if (table[location] != NULL)
            {
                //printf("At second location\n");
                n->next = table[location];
                table[location] = n;
            }
            else
            {
                table[location] = n;
            }
        }
    }

    /*
    This part is for print check, to see whether
    the words in the dictionary loaded onto the memory
    */
    /*(for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            printf("\n%s\t\nWord length:%lu\n", tmp->word, strlen(tmp->word));
        }

    }*/

    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordCount > 0)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
