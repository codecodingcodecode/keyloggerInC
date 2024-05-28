#include "../include/encryption.h"

char encryptDecryptChar(char ch, char key) {
    return ch ^ key;
}
