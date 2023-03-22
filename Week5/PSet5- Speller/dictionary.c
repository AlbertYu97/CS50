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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Word count
unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash work to obtain a hash value
    unsigned int index = hash(word);

    // Access linked list at the index
    node *pointer = table[index];

    // Traverse linked list
    while (pointer)
    {
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Add all the letters and mod the sum by 25
    unsigned int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // Check return value

    if (file == NULL)
    {
        printf("Unable to open the dictionary\n");
        return false;
    }

    // Declare variable
    char word[LENGTH + 1];

    //Scan dictionary until reach EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // create a Node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Run out of memory\n");
            return false;
        }

        // Copy the word to the node
        strcpy(n->word, word);

        // Insert the node to the hash table
        unsigned int index = hash(word);

        // Set the pointer to the head of the linkedlist
        n->next = table[index];

        // Reset head to be the node
        table[index] = n;

        // Increase word count
        count += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go to each linked list
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // If cursor is not NULL, free memory
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
