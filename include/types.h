#ifndef TYPES_H
#define TYPES_H

#define MAX_TOKENS 1024
#define MAX_LEXEME_LENGTH 256

typedef enum {
    TOKEN_KEYWORD = 0,
    TOKEN_OPERATOR = 1,
    TOKEN_STRING = 2,
    TOKEN_CONSTANT = 3,
    TOKEN_IDENTIFIER = 4,
    TOKEN_SEPARATOR = 5
} TokenType;

typedef struct {
    int lineNum;
    TokenType type;
    char lexeme[MAX_LEXEME_LENGTH];
} Translation;

#endif // TYPES_H
