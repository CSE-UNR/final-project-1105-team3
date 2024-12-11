//Author: Phillip Kim, Alex Rivera, Miles Frewert
//Purpose: Final Project
//Date: 12/8/24

#include <stdio.h>
#include <stdbool.h>

#define MAX_LINES 100
#define MAX_LENGTH 100
#define MAX_INPUT 30

// Function that reads file.
void readFile(const char *filename, char madlib[][MAX_LENGTH], char types[], int *lineCount, int *typeCount);
// Function that get users input for madlib.
void getInputForMadlib(char types[], char inputs[][MAX_INPUT], int typeCount);
// Function that displays madlib.
void displayMadlib(char madlib[][MAX_LENGTH], char inputs[][MAX_INPUT], int lineCount, int typeCount);
// Function that calculates length of a string.
int strLength(const char *str);
// Function that copies a string into another.
void strCopy(char *dest, const char *src);
// Function that checks if character is A, N, or V.
bool isTypeChar(char c);

int main(int c, char *v[]) {
// Lets user pick which file they would like to use. 
if (c < 2) {
        printf("Usage: %s <madlib_filename>\n", v[0]);
        return 1;
    }

char madlib[MAX_LINES][MAX_LENGTH];    // Array to store lines of the madlib
char types[MAX_LINES];                 // Array to store type indicators (A, N, V)
char inputs[MAX_LINES][MAX_INPUT];     // Array to store user inputs
int lineCount = 0;                     // Number of lines in the madlib
int typeCount = 0;                     // Number of type indicators

// Load madlib from file
readFile(v[1], madlib, types, &lineCount, &typeCount);
// Get user inputs
getInputForMadlib(types, inputs, typeCount);
// Display madlib
displayMadlib(madlib, inputs, lineCount, typeCount);

return 0;
}

void readFile(const char *filename, char madlib[][MAX_LENGTH], char types[], int *lineCount, int *typeCount) {
FILE *file = fopen(filename, "r");
if (file == NULL) {
printf("Error opening file.\n");
return;
    }

char line[MAX_LENGTH];
int i = 0, t = 0;
while (fgets(line, MAX_LENGTH, file)) {
// Remove newline character from the line
if (line[strLength(line) - 1] == '\n') {
line[strLength(line) - 1] = '\0';
}
if (isTypeChar(line[0]) && strLength(line) == 1) {
types[t++] = line[0]; // Store type indicator
} else {
strCopy(madlib[i++], line); // Store madlib text
}
}
fclose(file);
*lineCount = i; // Total lines of text
*typeCount = t; // Total type indicators
}

void getInputForMadlib(char types[], char inputs[][MAX_INPUT], int typeCount) {
for (int i = 0; i < typeCount; i++) {
if (types[i] == 'A') {
printf("Enter an adjective: ");
} else if (types[i] == 'N') {
printf("Enter a noun: ");
        } else if (types[i] == 'V') {
            printf("Enter a verb: ");
        }
        fgets(inputs[i], MAX_INPUT, stdin);
        if (inputs[i][strLength(inputs[i]) - 1] == '\n') {
            inputs[i][strLength(inputs[i]) - 1] = '\0';
        }
    }
}

void displayMadlib(char madlib[][MAX_LENGTH], char inputs[][MAX_INPUT], int lineCount, int typeCount) {
    int inputIndex = 0;
    for (int i = 0; i < lineCount; i++) {
        printf("%s", madlib[i]);
        if (inputIndex < typeCount) {
            printf(" %s", inputs[inputIndex++]);
// Add space if the next character is not punctuation
            if (i + 1 < lineCount && madlib[i + 1][0] != '\0' &&
                madlib[i + 1][0] != '.' && madlib[i + 1][0] != ',' &&
                madlib[i + 1][0] != '!' && madlib[i + 1][0] != '?' && madlib[i + 1][0] != ';') {
                printf(" ");
            }
        }
    }
    printf("\n");
}

int strLength(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void strCopy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool isTypeChar(char c) {
    return c == 'A' || c == 'N' || c == 'V';
}


