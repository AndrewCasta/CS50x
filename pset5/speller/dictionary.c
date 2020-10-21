// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

int dictCnt = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // take word *word
    // hash word to go to list
    int h = hash(word);
    node *cursor = table[h];

    // check through linked list, running strcasecmp (case insensitive)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = 31 * hash + tolower(word[i]);
    }
    return hash % 1000;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // open dictionary file, fopen
    FILE *file = fopen(dictionary, "r");
    // return false if not enough memory or file cannot be opened (return = NULL)
    if (!file)
    {
        return false;
    }

    // read strings from file, one at a time
    // repeat until fscanf returns EOF
    char *word = malloc(sizeof(char) * LENGTH + 1);
    while (fscanf(file, "%s", word) != EOF)
    {
        // create new 'node' for the word
        // allocate memory to store node (n = addess of node)
        node *n = malloc(sizeof(node));
        // check for NULL
        if (n == NULL)
        {
            return false;
        }
        // copy the string into n*.word (or n->word)
        strcpy(n->word, word);

        // run over a hash function, to get hash index
        int hashIndex = hash(word);

        // point new node at first node, then point the hash at the new node
        n->next = table[hashIndex];
        table[hashIndex] = n;

        dictCnt++;
    }
    free(word);
    fclose(file);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictCnt;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N + 1; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}
