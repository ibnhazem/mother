#include <stdio.h>
#include <string.h>

// Define the keywords as a static array
const char* keywords[] = {"add", "subtract", "divide", "modulos", "shift", "while", "print", "return"};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Function to check if a word is in the dictionary
int isInDictionary(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

// Main function for testing
int main(int argc, char const *argv[]) {
    const char* testWord = "add"; // Replace with input word for testing

    if (isInDictionary(testWord)) {
        printf("True: '%s' is a keyword.\n", testWord);
    } else {
        printf("False: '%s' is not a keyword.\n", testWord);
    }

    return 0;
}
