// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 28000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* cursor;
    int h_index = hash(word);

    cursor = table[h_index];
    while(true)
    {
        if(cursor == NULL)
        {
            return false;
        }
        if(strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }


    }
}

// Hashes word to a number
unsigned int hash(const char *word)
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
{
  unsigned long hash = 5381;
    int hash_final;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    /* hash * 33 + tolower(c). the tolower makes the hash function case insensitive since all words would be converted to lowercase anyway */

    if(hash > (N - 1))
    {
        hash_final = (hash % N);
    }
    else
    {
        hash_final = hash;
    }
    return hash_final;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
   // open dict
   FILE* fp = fopen(dictionary, "r");
   if(fp == NULL)
   {
       printf("Error opening file\n");
       return false;
   }

   // read string from file
   char* file_word = malloc(sizeof(char) * LENGTH);
   while(fscanf(fp, "%s", file_word) != EOF)
   {
       // create new node
       node* np = malloc(sizeof(node));
       strcpy(np -> word, file_word);
       // hash function
       int hash_index = hash(file_word);
       // insert node into a hash table
       if(table[hash_index] == NULL)
       {
           table[hash_index] = np;
       }
       else
       {
           np -> next = table[hash_index];
           table[hash_index] = np;
       }
   }
   free(file_word);
   fclose(fp);
   return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size()
{
    int array[N];
    node* cursor;
    long total_sum = 0;
    for (int i = 0; i < N; i++)
    {
        int sum = 0;
        cursor = table[i];
        while(cursor != NULL)
        {
            sum++;
            cursor = cursor -> next;
        }
        array[i] = sum;
    }

    for(int i = 0; i < N; i++)
    {
        total_sum = total_sum + array[i];
    }
    return total_sum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* tmp;
    node* cursor;
    for(int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];

        while(cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
