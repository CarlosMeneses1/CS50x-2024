// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the 'index' of the 'hash table'
    int index = hash(word);

    // Iterate throug each node on the link list
    node *cursor = table[index];

    while (cursor != NULL)
    {
        // Compare the 'word in the text' with the 'word in the dictionary'
        // If it is the word, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Else, point to the next node
        else
        {
            cursor = cursor->next;
        }
    }
    // If it is point to NULL, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    // Read each word of the dictionary
    char buffer[LENGTH + 1];

    while (fscanf(input, "%s", buffer) != EOF)
    {
        // Created a 'node'
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // For the 'word' section, copy each word of the dictionary and add into 'word' section of
        // the 'node'
        strcpy(n->word, buffer);
        n->next = NULL;

        // Get the 'index' of the 'hash table'
        int index = hash(n->word);

        // Update de 'hash table' with the new node
        n->next = table[index];
        table[index] = n;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;

    // Iterate throug each ith position of the 'hash table'
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Iterate throug each 'node' of the 'link list'
        while (cursor != NULL)
        {
            // Count each word
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate throug each ith position of the 'hast table'
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        // Iterate throug each node of the list link in ith position of the 'hash table'
        while (cursor != NULL)
        {
            // Free all malloc memory on each node
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
