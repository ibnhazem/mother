#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "executor.h"

extern Translation tokens[MAX_TOKENS];
extern int tokenCount;

void executeTokens() {
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(tokens[i].lexeme, "add") == 0) {
            int arg1 = atoi(tokens[i + 1].lexeme);
            int arg2 = atoi(tokens[i + 2].lexeme);
            printf("%d + %d = %d\n", arg1, arg2, arg1 + arg2);
            i += 2; // Skip arguments
        } else if (strcmp(tokens[i].lexeme, "return") == 0) {
            printf("Return command executed.\n");
            return;
        }
    }
}
