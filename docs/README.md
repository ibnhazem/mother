# Custom Compiler for .mom Language: Mother

## Overview
This project is a custom compiler for a simple, assembly-like programming language called `.mom`. It processes `.mom` files, tokenizes the input, validates the syntax, and executes the commands. The language supports basic arithmetic, control flow, and jump operations.

The compiler is written in C, following a modular design that separates functionality into tokenization, parsing, and execution stages.

---

## Language Features

### Supported Commands
| **Command**     | **Description**                                     | **Example**              |
|------------------|-----------------------------------------------------|--------------------------|
| `MOV`           | Assigns a constant to a register.                   | `MOV R1, 5;`             |
| `ADD`           | Adds the values of two registers.                   | `ADD R1, R2;`            |
| `SUB`           | Subtracts the second register from the first.       | `SUB R1, R2;`            |
| `MUL`           | Multiplies the values of two registers.             | `MUL R1, R2;`            |
| `DIV`           | Divides the first register by the second.           | `DIV R1, R2;`            |
| `WHILE`         | Starts a loop that continues while the condition is true. | `WHILE R1;`          |
| `ENDWHILE`      | Ends a `WHILE` loop.                                | `ENDWHILE;`              |
| `JMP`           | Jumps to a specified label in the program.          | `JMP END;`               |
| `CMP`           | Compares the values of two registers.               | `CMP R1, R2;`            |
| `RETURN`        | Ends the program or current loop.                   | `RETURN;`                |
| `LABEL`         | Marks a location in the code for `JMP`.             | `START:`                 |

### Language Rules
1. Each command must end with a semicolon (`;`).
2. Arguments are separated by commas (`,`) where applicable.
3. Labels are followed by a colon (`:`) and must be unique.
4. Registers are represented as `R1`, `R2`, etc.
5. Constants are numeric values (e.g., `5`, `10`).

---

## Example Programs

### 1. Arithmetic Operations
```mom
MOV R1, 5;
MOV R2, 10;
ADD R1, R2;
SUB R1, R2;
MUL R1, R2;
DIV R1, R2;
RETURN;
```

### 2. Loops
```mom
MOV R1, 5;
WHILE R1;
    SUB R1, 1;
ENDWHILE;
RETURN;
```

### 3. Jumps and Labels
```mom
MOV R1, 5;
START:
SUB R1, 1;
CMP R1, 0;
JMP START;
RETURN;
```

---

## Project Structure
```
compiler/
├── include/               # Header files
│   ├── executor.h
│   ├── isInDictionary.h
│   ├── parser.h
│   ├── tokenizer.h
│   ├── types.h
├── src/                   # Source files
│   ├── executor.c
│   ├── isInDictionary.c
│   ├── main.c
│   ├── parser.c
│   ├── tokenizer.c
├── tests/                 # Test cases
│   ├── test_mov.mom
│   ├── test_add.mom
│   ├── test_sub.mom
│   ├── test_mul.mom
│   ├── test_div.mom
│   ├── test_while.mom
│   ├── test_jmp_cmp.mom
│   ├── test_invalid.mom
├── Makefile               # Makefile for building the project
├── README.md              # Project documentation
```

---

## How to Build

Use the provided `Makefile` to build the project:
```bash
make
```

This compiles the source files into an executable named `compiler`.

---

## How to Run

To run the compiler on a `.mom` file:
```bash
./compiler <path_to_mom_file>
```

### Examples
1. Running a valid program:
   ```bash
   ./compiler tests/test_mov.mom
   ```

2. Running an invalid program:
   ```bash
   ./compiler tests/test_invalid.mom
   ```

---

## Expected Outputs

### For `tests/test_mov.mom`
Input:
```text
MOV R1, 5;
MOV R2, 10;
RETURN;
```

Output:
```text
MOV R1 = 5
MOV R2 = 10
Return command executed.
```

### For `tests/test_invalid.mom`
Input:
```text
MOV R1;
ADD R1;
CMP R1, abc;
JMP UNKNOWN_LABEL;
```

Output:
```text
Error: 'MOV' expects a register and a constant at line 1.
Error: 'ADD' expects two registers at line 2.
Error: Invalid argument type for 'CMP' at line 3.
Error: Undefined label 'UNKNOWN_LABEL' at line 4.
```

---

## Features of the Compiler

### 1. Tokenization
The input program is tokenized into commands and arguments, using the following data structure:
```c
typedef struct {
    int lineNum;
    CommandType command;
    Argument args[2];
    int argCount;
} Token;
```

### 2. Parsing
The parser validates the syntax and ensures:
- Commands have the correct number and type of arguments.
- Labels are defined and used properly.
- Loops (`WHILE` and `ENDWHILE`) are matched.

### 3. Execution
The executor runs the validated program, interpreting commands like `ADD`, `SUB`, `WHILE`, and `JMP`.

---

## Test Cases

### Valid Tests
- **Arithmetic Commands**: `test_add.mom`, `test_sub.mom`, etc.
- **Control Flow**: `test_while.mom`, `test_jmp_cmp.mom`.
- **Combined Features**: `test_all.mom`.

### Invalid Tests
- **Syntax Errors**: Missing arguments or invalid syntax.
- **Logic Errors**: Undefined labels or mismatched loops.

---

## Future Improvements
1. Add support for:
   - Conditional jumps (`JMP IF`).
   - Variable declarations and assignments.
   - Additional control structures (e.g., `IF-ELSE`).
2. Optimize execution for larger programs.
3. Improve error reporting with detailed line and column information.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.