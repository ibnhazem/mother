#ifndef TYPES_H
#define TYPES_H

#define MAX_TOKENS 1024
#define MAX_LEXEME_LENGTH 256
#define NUM_REGISTERS 16

// Enum for supported commands
typedef enum {
    CMD_MOV,       // Move constant to register
    CMD_ADD,       // Add two registers
    CMD_SUB,       // Subtract one register from another
    CMD_MUL,       // Multiply two registers
    CMD_DIV,       // Divide one register by another
    CMD_WHILE,     // Start of a WHILE loop
    CMD_ENDWHILE,  // End of a WHILE loop
    CMD_JMP,       // Jump to a label
    CMD_CMP,       // Compare two registers
    CMD_RETURN,    // Return from the program or loop
    CMD_LABEL      // Represents a label in the program (e.g., "LABEL:")
} CommandType;


// Enum for argument types
typedef enum {
    ARG_REGISTER,  // For registers like R1, R2, etc.
    ARG_CONSTANT,  // For numeric constants
    ARG_LABEL      // For jump labels
} ArgType;

// Struct to represent a single argument
typedef struct {
    ArgType type;
    union {
        int reg;                         // For registers (e.g., R1, R2)
        int constant;                    // For constants (e.g., 5, 10)
        char label[MAX_LEXEME_LENGTH];   // For labels (e.g., "END")
    };
} Argument;

// Struct for storing a token
typedef struct {
    int lineNum;                   // Line number in the source code
    CommandType command;           // The command (e.g., CMD_ADD)
    Argument args[2];              // Arguments (up to 2 for most commands)
    int argCount;                  // Number of arguments the command takes
} Token;

#endif // TYPES_H
