#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

Translation tokens[MAX_TOKENS];
int tokenCount = 0;

void addToken(int lineNum, TokenType type, const char* lexeme) {
    if (tokenCount < MAX_TOKENS) {
        tokens[tokenCount].lineNum = lineNum;
        tokens[tokenCount].type = type;
        strncpy(tokens[tokenCount].lexeme, lexeme, MAX_LEXEME_LENGTH - 1);
        tokens[tokenCount].lexeme[MAX_LEXEME_LENGTH - 1] = '\0'; // Null termination
        tokenCount++;
    } else {
        fprintf(stderr, "Error: Token limit exceeded.\n");
    }
}

void tokenize(FILE *file) {
    char line[MAX_LEXEME_LENGTH];
    int lineNum = 1;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " ,;\n");
        while (token) {
            TokenType type = isInDictionary(token) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
            addToken(lineNum, type, token);
            token = strtok(NULL, " ,;\n");
        }
        lineNum++;
    }
}
