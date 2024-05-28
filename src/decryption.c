#include "../include/decryption.h"
#include "../include/encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // Include stdbool.h for bool type

void decryptFile(const char *inputFile, const char *outputFile, char key) {
    FILE *inFile = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "w");
    char ch;
    bool newLine = true;

    if (inFile == NULL || outFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while ((ch = fgetc(inFile)) != EOF) {
        char decryptedChar = encryptDecryptChar(ch, key);
        if (decryptedChar == '[') {
            if (!newLine) {
                fputc('\n', outFile);
            }
            newLine = false;
        }
        fputc(decryptedChar, outFile);
        if (decryptedChar == '\n') {
            newLine = true;
        }
    }

    // Ensure the last line ends with a newline
    if (!newLine) {
        fputc('\n', outFile);
    }

    fclose(inFile);
    fclose(outFile);
}
