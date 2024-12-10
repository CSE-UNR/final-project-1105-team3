//Author: Phillip Kim, Alex Rivera, Miles Frewert
//Purpose: Final Project
//Date:12-8-24

#include <stdio.h>
#include <stdbool.h>

void readFile(const char *filename, char madlib[][100], char types[], int *lineCount, int *typeCount);
void getInputForMadlib(char types[], char inputs[][30], int typeCount);
void displayMadlib(char madlib[][100], char inputs[][30], int lineCount, int typeCount);
int strLength(const char *str);
void strCopy(char *dest, const char *src);
void strConcat(char *dest, const char *src);
bool isTypeChar(char c);


int main() {
    char madlib[100][100];    // Array to store lines of the madlib
    char types[100];          // Array to store type indicators (A, N, V)
    char inputs[100][30];     // Array to store user inputs
    int lineCount = 0;        // Number of lines in the madlib
    int typeCount = 0;        // Number of type indicators

    // Load madlib from file
    readFile("madlib2.txt", madlib, types, &lineCount, &typeCount);
    
    
    
    // Get user inputs
    getInputForMadlib(types, inputs, typeCount);
    
    
    // Display completed madlib
    displayMadlib(madlib, inputs, lineCount, typeCount);

    return 0;
}


void readFile(const char *filename, char madlib[][100], char types[], int *lineCount, int *typeCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100];
    int i = 0, t = 0;
    while (fgets(line, 100, file)) {
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
    *lineCount = i + t; // Total lines (text + type indicators)
    *typeCount = t;
}

// Function to get user input based on type indicators
void getInputForMadlib(char types[], char inputs[][30], int typeCount) {
    for (int i = 0; i < typeCount; i++) {
        if (types[i] == 'A') {
            printf("Enter an adjective: ");
        } else if (types[i] == 'N') {
            printf("Enter a noun: ");
        } else if (types[i] == 'V') {
            printf("Enter a verb: ");
        }
        fgets(inputs[i], 30, stdin);
        // Remove newline character from user input
        if (inputs[i][strLength(inputs[i]) - 1] == '\n') {
            inputs[i][strLength(inputs[i]) - 1] = '\0';
        }
    }
}

// Function to display the completed madlib
void displayMadlib(char madlib[][100], char inputs[][30], int lineCount, int typeCount) {
    int inputIndex = 0;
    for (int i = 0; i < lineCount - typeCount; i++) {
        printf("%s", madlib[i]);
        if (i < typeCount) {
            printf(" %s", inputs[inputIndex++]);
            if (madlib[i + 1][0] != '\0' && madlib[i + 1][0] != '.' &&
                madlib[i + 1][0] != ',' && madlib[i + 1][0] != '!' &&
                madlib[i + 1][0] != '?' && madlib[i + 1][0] != ';') {
                printf(" "); // Add space if the next character is not punctuation
            }
        }
    }
    printf("\n");
}

// Function to calculate the length of a string
int strLength(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Function to copy a string
void strCopy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Function to concatenate two strings
void strConcat(char *dest, const char *src) {
    int destLen = strLength(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLen++] = src[i++];
    }
    dest[destLen] = '\0';
}

// Function to check if a character is a valid type indicator
bool isTypeChar(char c) {
    return c == 'A' || c == 'N' || c == 'V';
}


