// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
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
const unsigned int N = 25;

// Hash table
node *table[N];

unsigned int count_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = malloc(sizeof(node));
    cursor = table[hash(word)];
    
    while (cursor != NULL){
        if (strcasecmp(cursor->word, word) == 0){
            return true;            
        }
        cursor = cursor->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char letra = toupper(word[0]);
    unsigned int i = letra - 65;
     
    return i;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        return false;
    }
    
    char word[LENGTH + 1];

    while(scanf(dictionary, "%s", word) != EOF){
        
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL){
            unload();
            return false;    
        }
        
        strcpy(new_node->word, word);
        
        int index = hash(new_node->word);
        node *tmp = table[index];
        
        if(tmp == NULL){
            //nenhum nó por enquanto
            table[index] = new_node;
            
        }else{
            //ja tem palavras para esta letra
            //faz o novo nó apontar para o primeiro e transforma o novo em primeiro
            new_node->next = table[index];
            table[index] = new_node;
        }
    
        count_words++;
    }
    
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp = malloc(sizeof(node));
    node *cursor = table[0];
    for(int i = 0; i < 26; i++){
        cursor = table[i];
        
        while (cursor != NULL){
            temp = cursor;
            cursor = cursor->next;
            free(temp);
 
        }
    }
    return true;
}