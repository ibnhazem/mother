#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1; // EXIT_FAILURE
    }

    FILE *testFile = fopen(argv[1], "r");
    if (testFile == NULL)
    {
        perror("Failed to open file");
        return 1; // EXIT_FAILURE
    }

    pickUpLine(testFile, "add");

    fclose(testFile);
    return 0; // EXIT_SUCCESS
}
