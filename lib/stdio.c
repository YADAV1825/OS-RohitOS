#include "stdio.h"

volatile char* video = (volatile char*)0xB8000;
int cursor = 0;

void print(char* str) {
    while(*str) {
        if(*str == '\n') {
            // Move to next line
            int current_line = cursor / 160;
            cursor = (current_line + 1) * 160;
        } else {
            video[cursor++] = *str;
            video[cursor++] = 0x0F;  // White on black
        }
        str++;
    }
}

void clear_screen() {
    for(int i = 0; i < 80*25*2; i += 2) {
        video[i] = ' ';
        video[i+1] = 0x0F;
    }
    cursor = 0;
}