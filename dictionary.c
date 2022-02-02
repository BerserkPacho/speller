// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 ;

// Hash table
node *table[N];

int words = 0;
  //global integer that the count function will be able to acess




// Hashes word to a number
unsigned int hash(const char *word)
{

    char first_letter = tolower(word[0]);
    int number = first_letter - 'a';
    //a, in ASCII, is 097 (http://sticksandstones.kstrom.com/appen.html) and b is 098, c is 099, etc...
    return number;
}
// Loads dictionary into memory, returning true if successful, else false


bool load(const char *dictionary)
{



   FILE *ptr = fopen(dictionary, "r");
    if( ptr == NULL)
    {
        return false;
    }
    char string[LENGTH + 1];

    /*string = malloc(sizeof(char) * 10);
    while(fread(string, sizeof(char), 1, ptr) != 0)
    {
        I tried to use fread, but it just seems too complicated
    } */

    while(fscanf(ptr, "%s", string) != EOF)
    {

        words++;
        //%s refers to a string, it will "automatically" parse the words, instead of you having to do the hard work with fread;
        node *newNode = malloc(sizeof(node));
        if(newNode == NULL)
        {

            return false;
        }


        strcpy(newNode->word,string);
        int position = hash(newNode->word);
       if(table[position] == NULL)
        {
            newNode->next = NULL;
            table[position] = newNode;
        }
        else
        {
            newNode->next = table[position];
            table[position] = newNode;
        }




    }

    fclose(ptr);
    return true;

}
bool check(const char *word)
{
    int index = hash(word);
    node *tmp;
    for(tmp = table[index]; tmp !=NULL; tmp = tmp->next)
    {
        if(strcasecmp(word, tmp->word) == 0)
        {
            return true;

        }
           }


    return false;
}

unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *next = table[i];
        while(next != NULL)
        {
            node *tmp = next;
            next = next->next;
            free(tmp);


        }

    }
    return true;

}
