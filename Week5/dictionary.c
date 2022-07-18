// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int dictionary_word_num = 0;
// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int num = hash(word);
    for (node *tmp = table[num]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        return false;
    }
    char word[LENGTH + 1];
    int index = 0;
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (c == '\n') {\
            word[index] = '\0';
            index = 0;
            dictionary_word_num++;
            int num = hash(word);
            node *tmp = malloc(sizeof(node));
            strcpy(tmp->word, word);
            tmp->next = table[num];
            table[num] = tmp;
        } else {
            word[index++] = c;
        }

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_word_num;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (unsigned int i = 0; i < N; i++) {
        // Free table[i]
        while (table[i] != NULL) {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }

    }
    return true;
}
