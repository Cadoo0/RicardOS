#include "screen/Screen.h"

extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
    Screen::printf("Hello World!");

    while(1);
}