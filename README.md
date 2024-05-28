# keyloggerInC

# Keylogger in C

## Overview

Welcome to the Keylogger in C project! This simple keylogger application logs keystrokes along with timestamps and encrypts the logged data for security. You can also decrypt the data to view the original keystrokes. The project is structured into several modules for better organization and maintainability.

## Features

- Logs keystrokes along with timestamps.
- Encrypts logged data using XOR encryption.
- Decrypts data to view the original keystrokes.
- Modular design for ease of maintenance and extension.

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- Windows OS (required for the Windows API functions)

### Building the Project

1. **Clone the repository:**

    ```sh
    git clone https://github.com/codecodingcodecode/keyloggerInC.git
    cd keylogger-in-c/src
    ```

2. **Compile the project:**

    ```sh
    gcc -I../include -o keylogger main.c keylogger.c decryption.c encryption.c timestamp.c -luser32
    ```

### Running the Keylogger

To start logging keystrokes:
    ./keylogger log K encrypted.txt

- `log`: Indicates logging mode.
- `K`: Encryption key (a single character).
- `encrypted.txt`: Output file for encrypted logs.

### Decrypting the Logs

To decrypt the logged data:
    ./keylogger decrypt K encrypted.txt decrypted.txt

- `decrypt`: Indicates decryption mode.
- `K`: Encryption key (must be the same key used for logging).
- `encrypted.txt`: Input file with encrypted logs.
- `decrypted.txt`: Output file for decrypted logs.

## Directory Structure

project/
├── include/
│   ├── keylogger.h
│   ├── decryption.h
│   ├── encryption.h
│   └── timestamp.h
├── src/
│   ├── main.c
│   ├── keylogger.c
│   ├── decryption.c
│   ├── encryption.c
│   └── timestamp.c
└── README.md

## How It Works

### Logging Keystrokes

The keylogger runs in an infinite loop, checking the state of each key. When a key is pressed, it records the keystroke and adds a timestamp every 5 seconds. The data is encrypted using XOR encryption before being written to the output file.

### Decrypting Logs

The decryption tool reads the encrypted log file, decrypts it using the same XOR key, and writes the original keystrokes and timestamps to an output file.

## Disclaimer

This project is intended for educational purposes only. Please use it responsibly and ensure that you have proper authorization before running the keylogger on any system.
