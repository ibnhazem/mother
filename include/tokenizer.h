#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "isInDictionary.h"
#include "types.h" // Shared definitions like TokenType and Translation

void addToken(int lineNum, TokenType type, const char* lexeme);
void tokenize(FILE *file);

#endif // TOKENIZER_H
