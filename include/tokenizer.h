#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "types.h"
#include <stdio.h>

// Functions
void tokenize(FILE *file);
void addToken(int lineNum, CommandType command, Argument *args, int argCount);

#endif // TOKENIZER_H
