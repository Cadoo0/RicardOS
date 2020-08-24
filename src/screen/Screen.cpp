#include "Screen.h"

unsigned int Screen::x = 0;
unsigned int Screen::y = 0;

unsigned short* Screen::VideoMemory = (unsigned short*) 0xb8000;

void Screen::printf(char *string) {
    for(int i = 0; string[i] != '\0'; ++i) {
        unsigned int currentLocation = x + (y * screenHeight);

        VideoMemory[currentLocation] = (VideoMemory[currentLocation] & 0xff00) | string[i];

        x++;
        if (x > screenWidth) {
            x = 0;
            y++;
        }
    }
}