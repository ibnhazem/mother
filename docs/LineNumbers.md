# pickUpLine

## Input
FILE*, which should 'point' to where the lexeme is at in the file.

## Output
An integer representing the line number the lexeme is at

We can track the line numbers by using a counter triggered by seperators

counter triggered by seperators (;,{,})

pickUpLine(FILE*,char*)
    while(fgetc(c) != EOF)
        if(c = ;)
            counter++
        