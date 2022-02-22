#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const unsigned int N = 28000;

unsigned int hash(const char *word);

int main()
{
   char* word = "seamanlike";
   unsigned int hash_index = hash(word);
   printf("%i\n", hash_index);
}

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