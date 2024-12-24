### **1. Core Functionality**
   - **Input**: Read a `.mom` file.
   - **Output**: Either execute the commands (interpretation) or generate an intermediate representation (IR) for later use.
   - **Features to Highlight**:
     - A tokenizer that recognizes basic commands and arguments.
     - A parser that validates the syntax.
     - Execution or pseudo-code generation.

   **What to Showcase**:
   - A `.mom` file with clear examples of commands like `MOV`, `ADD`, `SUB`, and `WHILE`.
   - An explanation in your README that this demonstrates the basics of compiler design.

---

### **2. Minimal Language Specification**
   - **Commands**:
     - `MOV R1, 5`: Assigns the value `5` to `R1`.
     - `ADD R1, R2`: Adds the value of `R2` to `R1`.
     - `SUB R1, R2`: Subtracts the value of `R2` from `R1`.
     - `WHILE R1`: Starts a loop that continues while `R1 != 0`.
     - `RETURN`: Ends the program or loop.

   - **Syntax Rules**:
     - Commands with consistent two-argument or one-argument formats.
     - Registers (`R1`, `R2`, etc.) and constants as arguments.

---

### **3. Minimum Code Deliverables**
   - **Tokenizer**:
     - Reads the input file and splits it into commands and arguments.
     - Recognizes registers, constants, and keywords.

   - **Parser**:
     - Validates that each command has the correct syntax and arguments.

   - **Executor/Interpreter**:
     - Executes the commands directly, updating register values.

---

### **4. Code Example**
   Write clean, commented code with:
   - A `main` function that ties together the tokenizer, parser, and executor.
   - Clear structs for tokens and basic error handling.
   - Example `.mom` files and a script to run the program.

---

### **5. Project Structure**
   - **Code**:
     - Place all the C files in a `src` directory.
   - **Documentation**:
     - A README.md file with:
       - Project purpose (e.g., "A basic custom compiler to showcase parsing and interpretation of a simple custom language.").
       - Instructions for running the program.
       - Example `.mom` programs.
   - **Example Files**:
     - Include one or two `.mom` files with sample code like:
       ```text
       MOV R1, 5
       WHILE R1
           SUB R1, 1
       ENDWHILE
       RETURN
       ```

---

### **6. GitHub and Resume**
   - **GitHub Repository**:
     - Make the repo public with:
       - A concise description.
       - Proper documentation in the README.
       - Example outputs or screenshots.
   - **Resume Entry**:
     - Project Title: **Custom Compiler for Simple Language**.
     - Description: 
       > Designed and implemented a compiler for a custom assembly-like language in C. Features include lexical analysis, syntax parsing, and execution of basic arithmetic and control-flow operations.

---

### **Why This Works for a Resume**
- **Key Deliverables**:
  - Demonstrates knowledge of compiler fundamentals (tokenization, parsing, and execution).
  - Includes concrete examples and a working implementation.
  - Clearly documented, making it easy for others to understand.

- **Minimal Time Investment**:
  - Focuses only on the essentials, skipping advanced features.
  - Makes the project look polished without extra complexity.
