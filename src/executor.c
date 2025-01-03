#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "executor.h"

#define MAX_LOOP_DEPTH 16 // Maximum depth of nested loops
int loopStack[MAX_LOOP_DEPTH];
int loopStackTop = -1; // Initialize stack top to -1

// Simulate a register file
int registers[NUM_REGISTERS] = {0};

extern Token tokens[MAX_TOKENS];
extern int tokenCount;

void printRegisters() {
    printf("Register states:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("R%d = %d\n", i, registers[i]);
    }
}

void executeTokens() {
    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        // // Debug: Print the token being executed
        // printf("Executing token: command=%d, argCount=%d, lineNum=%d\n", 
        //        token.command, token.argCount, token.lineNum);

        switch (token.command) {
            case CMD_MOV:
                registers[token.args[0].reg] = token.args[1].constant;
                printf("MOV R%d = %d\n", token.args[0].reg, registers[token.args[0].reg]);
                break;

            case CMD_ADD:
                registers[token.args[0].reg] += registers[token.args[1].reg];
                printf("ADD R%d = %d\n", token.args[0].reg, registers[token.args[0].reg]);
                break;

            case CMD_SUB:
                registers[token.args[0].reg] -= registers[token.args[1].reg];
                printf("SUB R%d = %d\n", token.args[0].reg, registers[token.args[0].reg]);
                break;

            case CMD_MUL:
                registers[token.args[0].reg] *= registers[token.args[1].reg];
                printf("MUL R%d = %d\n", token.args[0].reg, registers[token.args[0].reg]);
                break;

            case CMD_DIV:
                registers[token.args[0].reg] /= registers[token.args[1].reg];
                printf("DIV R%d = %d\n", token.args[0].reg, registers[token.args[0].reg]);
                break;

            case CMD_CMP:
                if (token.argCount != 2 || 
                    token.args[0].type != ARG_REGISTER || 
                    token.args[1].type != ARG_REGISTER || 
                    token.args[0].reg < 0 || 
                    token.args[0].reg >= NUM_REGISTERS || 
                    token.args[1].reg < 0 || 
                    token.args[1].reg >= NUM_REGISTERS) {
                    fprintf(stderr, "Error: 'CMP' expects two valid registers at line %d.\n", token.lineNum);
                    return;
                }
                break;


            case CMD_JMP:
                if (token.argCount != 1 || token.args[0].type != ARG_LABEL) {
                    fprintf(stderr, "Error: 'JMP' expects one valid label at line %d.\n", token.lineNum);
                    return;
                }
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
                    return;
                }
                break;

            case CMD_WHILE:
                if (registers[token.args[0].reg] != 0) {
                    // Condition is true, push the current token index onto the stack
                    if (loopStackTop < MAX_LOOP_DEPTH - 1) {
                        loopStack[++loopStackTop] = i;
                        printf("WHILE loop starting (R%d = %d).\n", token.args[0].reg, registers[token.args[0].reg]);
                    } else {
                        fprintf(stderr, "Error: Loop nesting too deep at line %d.\n", token.lineNum);
                        return;
                    }
                } else {
                    // Skip to the matching ENDWHILE
                    int nestedWhileCount = 1;
                    while (nestedWhileCount > 0 && ++i < tokenCount) {
                        if (tokens[i].command == CMD_WHILE) nestedWhileCount++;
                        if (tokens[i].command == CMD_ENDWHILE) nestedWhileCount--;
                    }
                    if (nestedWhileCount > 0) {
                        fprintf(stderr, "Error: Unmatched 'WHILE' at line %d.\n", token.lineNum);
                        return;
                    }
                }
                break;

            case CMD_ENDWHILE:
                if (loopStackTop >= 0) {
                    // Pop the loop stack and jump back to the corresponding WHILE
                    i = loopStack[loopStackTop--] - 1; // Adjust for the loop iteration
                    printf("ENDWHILE loop. Returning to WHILE.\n");
                } else {
                    fprintf(stderr, "Error: Unmatched 'ENDWHILE' at line %d.\n", token.lineNum);
                    return;
                }
                break;

            case CMD_RETURN:
            case CMD_DUMP:
                printf("DUMP command executed. Register states:\n");
                printRegisters();
                break;

            default:
                fprintf(stderr, "Error: Unknown command at line %d.\n", token.lineNum);
                return;
        }
    }
}
