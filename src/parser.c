#include <stdio.h>
#include <string.h>
#include "parser.h"

extern Token tokens[MAX_TOKENS];
extern int tokenCount;

int validateTokens() {
    int whileCount = 0; // Track WHILE-ENDWHILE matching

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        // // Debug: Print the token being validated
        // printf("Validating token: command=%d, argCount=%d, lineNum=%d\n", 
        //        token.command, token.argCount, token.lineNum);

        switch (token.command) {
            case CMD_MOV:
                if (token.argCount != 2 || token.args[0].type != ARG_REGISTER || token.args[1].type != ARG_CONSTANT) {
                    fprintf(stderr, "Error: 'MOV' expects a register and a constant at line %d.\n", token.lineNum);
                    return 0;
                }
                break;

            case CMD_ADD:
            case CMD_SUB:
            case CMD_MUL:
            case CMD_DIV:
                if (token.argCount != 2 || token.args[0].type != ARG_REGISTER || token.args[1].type != ARG_REGISTER) {
                    fprintf(stderr, "Error: Arithmetic commands expect two registers at line %d.\n", token.lineNum);
                    return 0;
                }
                if (token.command == CMD_DIV && token.args[1].reg == 0) { // Example: DIV R1, 0
                    fprintf(stderr, "Error: Division by zero at line %d.\n", token.lineNum);
                    return 0;
                }
                break;

            case CMD_CMP:
                if (token.argCount != 2 || token.args[0].type != ARG_REGISTER || token.args[1].type != ARG_REGISTER) {
                    fprintf(stderr, "Error: 'CMP' expects two registers at line %d.\n", token.lineNum);
                    return 0;
                }
                break;

            case CMD_JMP: {
                if (token.argCount != 1 || token.args[0].type != ARG_LABEL) {
                    fprintf(stderr, "Error: 'JMP' expects one label at line %d.\n", token.lineNum);
                    return 0;
                }

                // Validate label existence
                int labelFound = 0;
                for (int j = 0; j < tokenCount; j++) {
                    if (tokens[j].command == CMD_LABEL &&
                        strcmp(tokens[j].args[0].label, token.args[0].label) == 0) {
                        labelFound = 1;
                        break;
                    }
                }
                if (!labelFound) {
                    fprintf(stderr, "Error: Undefined label '%s' at line %d.\n", token.args[0].label, token.lineNum);
                    return 0;
                }
                break;
            }

            case CMD_WHILE:
                if (token.argCount != 1 || token.args[0].type != ARG_REGISTER) {
                    fprintf(stderr, "Error: 'WHILE' expects one register at line %d.\n", token.lineNum);
                    return 0;
                }
                whileCount++;
                break;

            case CMD_ENDWHILE:
                if (whileCount == 0) {
                    fprintf(stderr, "Error: Unmatched 'ENDWHILE' at line %d.\n", token.lineNum);
                    return 0;
                }
                whileCount--;
                break;

            case CMD_RETURN:
                if (token.argCount != 0) {
                    fprintf(stderr, "Error: 'RETURN' should have no arguments at line %d.\n", token.lineNum);
                    return 0;
                }
                break;

            case CMD_DUMP:
                if (token.argCount != 0) {
                    fprintf(stderr, "Error: 'DUMP' should have no arguments at line %d.\n", token.lineNum);
                    return 0;
                }
                break;

            default:
                fprintf(stderr, "Error: Unknown command at line %d.\n", token.lineNum);
                return 0;
        }
    }


    if (whileCount > 0) {
        fprintf(stderr, "Error: Unmatched 'WHILE' loop.\n");
        return 0;
    }

    return 1; // All tokens are valid
}
