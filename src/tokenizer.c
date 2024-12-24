#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

Token tokens[MAX_TOKENS];
int tokenCount = 0;

void addToken(int lineNum, CommandType command, Argument *args, int argCount) {
    if (tokenCount < MAX_TOKENS) {
        tokens[tokenCount].lineNum = lineNum;
        tokens[tokenCount].command = command;
        tokens[tokenCount].argCount = argCount;

        for (int i = 0; i < argCount; i++) {
            tokens[tokenCount].args[i] = args[i];
        }

        tokenCount++;
    } else {
        fprintf(stderr, "Error: Token limit exceeded.\n");
    }
}

void tokenize(FILE *file) {
    char line[MAX_LEXEME_LENGTH];
    int lineNum = 1;

    while (fgets(line, sizeof(line), file)) {
        char *commandStr = strtok(line, " ;\n"); // Treat semicolon as a delimiter
        if (!commandStr) continue;

        CommandType command;
        Argument args[2];
        int argCount = 0;

        // Check for labels (e.g., "LABEL:")
        if (strchr(commandStr, ':')) {
            command = CMD_LABEL;
            args[0].type = ARG_LABEL;
            strncpy(args[0].label, commandStr, MAX_LEXEME_LENGTH - 1);
            args[0].label[strlen(commandStr) - 1] = '\0'; // Remove the trailing ':'
            addToken(lineNum, command, args, 1);
            continue;
        }

        // Handle commands
        if (strcmp(commandStr, "MOV") == 0) command = CMD_MOV;
        else if (strcmp(commandStr, "ADD") == 0) command = CMD_ADD;
        else if (strcmp(commandStr, "SUB") == 0) command = CMD_SUB;
        else if (strcmp(commandStr, "MUL") == 0) command = CMD_MUL;
        else if (strcmp(commandStr, "DIV") == 0) command = CMD_DIV;
        else if (strcmp(commandStr, "WHILE") == 0) command = CMD_WHILE;
        else if (strcmp(commandStr, "ENDWHILE") == 0) command = CMD_ENDWHILE;
        else if (strcmp(commandStr, "RETURN") == 0) command = CMD_RETURN;
        else if (strcmp(commandStr, "JMP") == 0) command = CMD_JMP;
        else if (strcmp(commandStr, "CMP") == 0) command = CMD_CMP;
        else {
            fprintf(stderr, "Error: Invalid command '%s' at line %d.\n", commandStr, lineNum);
            continue;
        }

        // Parse arguments
        char *argStr;
        while ((argStr = strtok(NULL, ", ;\n")) != NULL && argCount < 2) {
            if (argStr[0] == 'R') { // Register argument
                args[argCount].type = ARG_REGISTER;
                args[argCount].reg = atoi(argStr + 1);
            } else if (isdigit(argStr[0])) { // Constant argument
                args[argCount].type = ARG_CONSTANT;
                args[argCount].constant = atoi(argStr);
            } else { // Label argument
                args[argCount].type = ARG_LABEL;
                strncpy(args[argCount].label, argStr, MAX_LEXEME_LENGTH - 1);
                args[argCount].label[MAX_LEXEME_LENGTH - 1] = '\0';
            }
            argCount++;
        }

        // Validate argument count
        if ((command == CMD_MOV || command == CMD_ADD || command == CMD_SUB || command == CMD_MUL || command == CMD_DIV) && argCount != 2) {
            fprintf(stderr, "Error: Invalid argument count for '%s' at line %d.\n", commandStr, lineNum);
            continue;
        } else if ((command == CMD_JMP || command == CMD_CMP || command == CMD_WHILE) && argCount != 1) {
            fprintf(stderr, "Error: Invalid argument count for '%s' at line %d.\n", commandStr, lineNum);
            continue;
        } else if (command == CMD_RETURN && argCount != 0) {
            fprintf(stderr, "Error: 'RETURN' should have no arguments at line %d.\n", lineNum);
            continue;
        }

        addToken(lineNum, command, args, argCount);
        lineNum++;
    }
}
