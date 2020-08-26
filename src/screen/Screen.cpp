#include "Screen.h"

unsigned int Screen::x = 0;
unsigned int Screen::y = 0;

unsigned short* Screen::VideoMemory = (unsigned short*) 0xb8000;

void Screen::printf(char *string) {
    for(int i = 0; string[i] != '\0'; ++i) {
        if (y > screenHeight) {
            scroll();
        }

        if (string[i] == '\n') {
            x = 0;
            y++;

            continue;
        }

        unsigned int currentLocation = x + (y * screenWidth);
        VideoMemory[currentLocation] = (VideoMemory[currentLocation] & 0xff00) | string[i];

        x++;
        if (x > screenWidth) {
            x = 0;
            y++;
        }
    }
}

void Screen::scroll() {
    for(int vertical = 0; vertical <= screenHeight; vertical++) {
        for(int horizontal = 0; horizontal <= screenWidth; horizontal++) {
            unsigned int newLocation = horizontal + (vertical - 1) * screenWidth;
            unsigned int oldLocation = horizontal + vertical * screenWidth;

            VideoMemory[newLocation] = VideoMemory[oldLocation];
        }
    }

    x = 0;
    if (y > 1) {
        y--;
    }
}