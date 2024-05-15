#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define KEYWORD_DICTIONARY_SIZE 1024
#define MAX_LEXEME_LENGTH 256

typedef enum
{
    TOKEN_KEYWORD = 0,
    TOKEN_OPERATOR = 1,
    TOKEN_STRING = 2,
    TOKEN_CONSTANT = 3,
    TOKEN_IDENTIFIER = 4,
    TOKEN_SEPERATOR = 5
} TokenType;

typedef struct
{
    int lineNum;
    TokenType type;
    char *lexeme;
} Translation;

#define MAX_TOKENS 1024

Translation tokens[MAX_TOKENS];
int tokenCount = 0;

// Lexical tokenizer where the lexeme, a string, would be the parameter and the function would then check if the lexeme is a token or not
void addToken(int lineNum, TokenType type, const char* lexeme) {
    if (tokenCount < MAX_TOKENS) {
        tokens[tokenCount].lineNum = lineNum;
        tokens[tokenCount].type = type;
        tokens[tokenCount].lexeme = strdup(lexeme);  // Duplicate the string for storage
        tokenCount++;
    }
}

void freeTokens() {
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i].lexeme);  // Free the duplicated strings
    }
}

void pickUpLine(FILE *wya, char *lexeme)
{
    int lineCounter = 1; // Start at 1 to count the first line
    char word[256];
    char *curString;
    int found = 0;

    // Read lines until the end of the file
    while ((curString = fgets(word, sizeof(word), wya)) != NULL)
    {
        // Check if the current line contains the lexeme
        if (strstr(curString, lexeme) != NULL)
        {
            printf("'%s' found at line: %d\n",lexeme, lineCounter);
            found = 1;
        }

        // Count lines by newline characters
        if (strchr(curString, '\n') != NULL)
        {
            lineCounter++;
        }
    }

    // If lexeme is not found, print an error
    if (!found)
    {
        perror("Lexeme not found in the file");
    }
}

// Compare lexeme with a keyword dictionary file to check if lexeme is a keyword or not.
// Function to check if the word is in the dictionary. FILE used is keywords.
int isInDictionary(char *word)
{
    FILE *keywordDictionary = fopen("keywords", "r");
    if (keywordDictionary == NULL)
    {
        perror("Unable to open dictionary");
        return EXIT_FAILURE;
    }
    char *dictionary[KEYWORD_DICTIONARY_SIZE] = {NULL};
    fgets(dictionary, sizeof(dictionary), keywordDictionary);

    int i = 0;

    while (i < KEYWORD_DICTIONARY_SIZE && dictionary[i] != NULL)
    {
        if (strcmp(word, dictionary[i]) == 0)
        {
            return EXIT_SUCCESS; // Word found in dictionary
        }
        i++;
    }
    return EXIT_FAILURE; // Word not found
}

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
        dictionary[i] = malloc(MAX_LEXEME_LENGTH * sizeof(char));
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

        if (fgets(dictionary[i], MAX_LEXEME_LENGTH, keywordDictionary) == NULL)
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

int main(int argc, char *const argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Incorrect usage. Correct usage...\n");
        fprintf(stderr, "./compiler <inputfile>.mom\n");
        return EXIT_FAILURE;
    }

    // printf(" %s\n", argv[1]); // Debugging argument file

    FILE *dot_mom = fopen(argv[1], "r"); // Open .mom file to read code. FILE used is test.mom

    int scanChar = fgetc(dot_mom);   // Character being inputed from file

    if (dot_mom == NULL)
    {
        fprintf(stderr, "Error when opening .mom file.\n");
        return EXIT_FAILURE;
    }

    char lexeme[MAX_LEXEME_LENGTH] = {NULL};    // Temporary array to hold lexeme
    int i = 0;

    while (scanChar != EOF)
    {
        // If a lexeme starts with a alphanumerical character, the lexeme is then stored in a buffer till end of lexeme (EOL). The EOL
        // is then compared with a dictionary of keywords. If it is a keyword, translate to token. Else, add to dictionary of identifiers (temp file of all identifiers)
        if (isalnum(scanChar))
        {
            
        }
        i++;
        putchar(scanChar);
    }
    printf("%c", '\n');

    fclose(dot_mom);

    return EXIT_SUCCESS;
}
