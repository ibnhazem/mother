# Tokenizer

## Input: 
A line --what defines a line is a string of characters between 2 seperators (;)
## Output:
A 2D array of the line. [][3], the 3 columns, line number, TokenType, and char*.
Each line is numbered. Each line has its 2D array lexeme analysis result, "translation."

### Example
#### Input: 
1   int x;
2   int a;
3   x = a + 2;

#### Result after tokenization,
[(1,keyword,int), (1,identifier,x), (1,seperator,;),
 (2,keyword,int), (2,identifier,a), (2,seperator,;),
 (3,identifier,x), (3,operator,=), (3,identifier,a), (3,operator,+), (3,constant,2), (3,seperator,;)]

| Line | Token Type  | Token Value |
|------|-------------|-------------|
| 1    | keyword     | int         |
| 1    | identifier  | x           |
| 1    | separator   | ;           |
| 2    | keyword     | int         |
| 2    | identifier  | a           |
| 2    | separator   | ;           |
| 3    | identifier  | x           |
| 3    | operator    | =           |
| 3    | identifier  | a           |
| 3    | operator    | +           |
| 3    | constant    | 2           |
| 3    | separator   | ;           |
| .    |     .       |     .       |
| .    |     .       |     .       |

