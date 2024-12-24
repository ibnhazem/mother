#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputfile>.mom\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", argv[1]);
        return EXIT_FAILURE;
    }

    tokenize(file);
    fclose(file);

    if (!validateTokens()) {
        return EXIT_FAILURE; // Exit if validation fails
    }

    executeTokens();

    return EXIT_SUCCESS;
}
