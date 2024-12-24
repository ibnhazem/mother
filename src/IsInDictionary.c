#include <stdio.h>
#include <string.h>

const char* keywords[] = {"MOV", "ADD", "SUB", "MUL", "DIV", "WHILE", "ENDWHILE", "JMP", "CMP", "RETURN"};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int isInDictionary(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // Found
        }
    }
    return 0; // Not found
}
