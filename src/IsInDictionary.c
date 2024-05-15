#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define KEYWORD_DICTIONARY_SIZE 1026
#define MAX_WORD_LENGTH 100

// Function to remove all whitespace characters from a string
void removeWhitespaces(char *str) {
    char *readPtr = str, *writePtr = str;
    while (*readPtr) {
        if (!isspace(*readPtr)) {
            *writePtr++ = *readPtr;
        }
        readPtr++;
    }
    *writePtr = '\0';
}

int isInDictionary(const char *word)
{
    FILE *keywordDictionary = fopen("keywords", "r");
    if (keywordDictionary == NULL)
    {
        perror("Unable to open dictionary file");
        return 1;
    }
    
    char **dictionary = malloc(KEYWORD_DICTIONARY_SIZE * sizeof(char *));
    if (dictionary == NULL)
    {
        perror("Memory allocation failed");
        fclose(keywordDictionary);
        return 1;
    }
    
    for (int i = 0; i < KEYWORD_DICTIONARY_SIZE; i++)
    {
        dictionary[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
        if (dictionary[i] == NULL)
        {
            perror("Memory allocation failed");
            fclose(keywordDictionary);
            for (int j = 0; j < i; j++)
            {
                free(dictionary[j]);
            }
            free(dictionary);
            return 1;
        }

        if (fgets(dictionary[i], MAX_WORD_LENGTH, keywordDictionary) == NULL)
        {
            free(dictionary[i]);
            dictionary[i] = NULL;
            break;
        }
        removeWhitespaces(dictionary[i]);
        if (strcmp(word, dictionary[i]) == 0)
        {
            for (int j = 0; j <= i; j++)
            {
                free(dictionary[j]);
            }
            free(dictionary);
            fclose(keywordDictionary);
            return 0; // Word found in dictionary
        }
    }
    
    for (int i = 0; i < KEYWORD_DICTIONARY_SIZE; i++)
    {
        if (dictionary[i] != NULL)
        {
            free(dictionary[i]);
        }
    }
    free(dictionary);
    fclose(keywordDictionary);
    return 1; // Word not found
}

int main(int argc, char const *argv[])
{
    switch (isInDictionary("add"))
    {
    case 0:
        printf("True\n");
        break;
    case 1:
        printf("False\n");
        break;
    default:
        perror("Error.\n");
        break;
    }
    return 0;
}
