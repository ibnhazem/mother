Creating a custom compiler is an ambitious project, especially when you're designing your own language. Here's an outline to guide you through the process, starting with the tokenizer you've already built. We will refine your approach and walk through the necessary components.

### 1. **Language Design**
   - **Syntax & Semantics**: Define the syntax and semantics of your custom language. For example:
     - **Instructions**: What commands exist (`add`, `subtract`, `while`, etc.)?
     - **Data Types**: Will you have specific types like integers or floats?
     - **Control Structures**: What looping, conditional, or branching mechanisms are allowed? You seem to be using a basic form of loops (e.g., `while`).
     - **Operators**: Define which operations will be allowed (e.g., `+`, `-`, etc.).

   **Deliverables**: 
   - Write a simple grammar for `.mom` language (like Backus-Naur Form if possible).
   - Clarify if your instructions are position-based (i.e., parameters like `add 1, 2` will always follow that pattern).

### 2. **Tokenizer (Lexical Analysis)**
   You've already started with the tokenizer. Here are some refinements:
   
   - **Reading Character by Character**: In the code, you're reading input character by character using `fgetc()`. Instead, you can tokenize based on spaces and newlines for clearer separation between lexemes.
   - **Keywords & Operators**: Store keywords (`add`, `subtract`, `while`, etc.) and operators (`+`, `-`, etc.) in separate arrays for faster lookup.
   
   **Refinements**:
   - Implement a state machine to handle different tokens (keywords, identifiers, constants, etc.).
   - Enhance error handling for unrecognized tokens.

### 3. **Parser (Syntax Analysis)**
   After tokenizing, you need a parser that will validate the structure based on your grammar.

   - **Abstract Syntax Tree (AST)**: Construct an AST that represents the structure of the program.
     - **Example**: `add 1, 2` would become an AST node with an `ADD` operation, with `1` and `2` as child nodes (arguments).
   - **Recursive Descent Parser**: Since your language is relatively simple, you could use a recursive descent parser to process tokens and enforce syntax rules.

   **Deliverables**:
   - Write parsing functions for each part of the grammar (e.g., functions to parse expressions, statements, loops).

### 4. **Semantic Analysis**
   During or after parsing, you'll need to check whether the program makes sense beyond the syntax:
   
   - **Type Checking**: Ensure that operations like `add 1, 2` are valid (i.e., both operands are integers).
   - **Scope Management**: Track variables and functions in scopes, if relevant to your language.

   **Deliverables**:
   - Create a symbol table to store information about variables, constants, and functions.
   - Implement a type-checking system to enforce valid operations.

### 5. **Intermediate Representation (IR)**
   After parsing and semantic checks, you'll likely want to generate an intermediate representation (IR). This could be a lower-level version of your custom language or even basic machine code instructions.

   **Example**:
   ```assembly
   ADD R1, R2  // Perform an addition operation on registers
   ```

   **Deliverables**:
   - Design an IR or use an existing intermediate language to translate `.mom` instructions.

### 6. **Code Generation**
   The final step of the compilation process is to translate the IR into machine code or bytecode. In your case, you might:
   
   - **Custom Virtual Machine**: Implement a simple virtual machine that can interpret the IR.
   - **Platform-Specific Machine Code**: Generate machine code that can be run directly on a specific processor.

   **Deliverables**:
   - Implement code generation that outputs machine code or bytecode for the `.mom` program.
   - Write a virtual machine or interpreter if you decide not to generate machine code.

### 7. **Optimization (Optional)**
   If you plan to optimize, this would be an additional stage:
   - **Peephole Optimization**: Look for small patterns in the IR or code and optimize them.
   - **Dead Code Elimination**: Remove code that is never executed.

### 8. **Testing and Debugging**
   Testing will be crucial to ensure the functionality of each stage:
   - **Unit Tests**: Test the tokenizer, parser, semantic analyzer, etc., with sample `.mom` files.
   - **Integration Tests**: Ensure the full compilation process works end to end.

### Specific to Your `.mom` Example:

- **While Loops**: You will need to ensure your parser can handle loops like `while 2;`.
- **Error Handling**: Your current program could benefit from more robust error handling in case the syntax is not valid.
  
### Immediate Next Steps (For Tokenizer Fix):
1. **Modify Tokenizer Logic**:
   - Instead of directly checking for keywords after reading each character, tokenize based on spaces or other separators.
   - After tokenizing a full lexeme, check if it's a keyword or identifier.

2. **Debugging**:
   - Ensure the tokenizer doesn’t miss tokens or split them incorrectly. Add more detailed debug output to understand what’s going wrong.
   
Let me know if you'd like help breaking down any specific steps further!