#include "kernel.h"
#include "cli.h"
#include "stdio.h"
#include <stddef.h>  // ✅ FIX for NULL

const char* splash_msg[] = {
    "",
    "   \x2B-----------------------------------------------------------------------\x2B   ", // '+' = ASCII 43
    "   \x7C                                                                       \x7C   ", // '|' = ASCII 124
    "   \x7C         _____    ____   _    _  _  _______     ____     _____         \x7C   ",
    "   \x7C        |  __ \\  / __ \\ | |  | || ||__   __|   / __ \\   / ____|        \x7C   ",
    "   \x7C        | |__) || |  | || |__| || |   | |     | |  | | | (___          \x7C   ",
    "   \x7C        |  _  / | |  | ||  __  || |   | |     | |  | |  \\___ \\         \x7C   ",
    "   \x7C        | | \\ \\ | |__| || |  | || |   | |     | |__| |  ____) |        \x7C   ",
    "   \x7C        |_|  \\_\\ \\____/ |_|  |_||_|   |_|      \\____/  |_____/         \x7C   ",
    "   \x7C                                                                       \x7C   ",
    "   \x7C                             ROHIT OS v0.1                             \x7C   ",
    "   \x7C                          Made by: Rohit Yadav                         \x7C   ",
    "   \x7C                        NIT Jalandhar | 3rd Year                       \x7C   ",
    "   \x7C                                                                       \x7C   ",
    "   \x7C                         [ BOOTING SYSTEM... ]                         \x7C   ",
    "   \x2B-----------------------------------------------------------------------\x2B   ",
    "",
    NULL
};

// const char* splash_msg[] = {
//     "",
//     "   \x2B--------------------------------------------------\x2B   ",
//     "   \x7C                                                  \x7C   ",
//     "   \x7C  _____  ____  _   _ _    _ _______   ____  _____  \x7C   ",
//     "   \x7C |  __ \\|  _ \\| | | | |  | |__   __| / __ \\|  __ \\ \x7C   ",
//     "   \x7C | |__) | |_) | | | | |  | |  | |  | |  | | | |__) |\x7C   ",
//     "   \x7C |  _  /|  _ <| | | | |  | |  | |  | |  | | |  _  / \x7C   ",
//     "   \x7C | | \\ \\| |_) | |_| | |__| |  | |  | |__| | | | \\ \\ \x7C   ",
//     "   \x7C |_|  \\_\\____/ \\___/ \\____/   |_|   \\____/  |_|  \\_\\\x7C   ",
//     "   \x7C                                                  \x7C   ",
//     "   \x7C               ROHIT OS v0.1                      \x7C   ",
//     "   \x7C        Made by: Rohit Yadav                      \x7C   ",
//     "   \x7C        NIT Jalandhar | 3rd Year                  \x7C   ",
//     "   \x7C                                                  \x7C   ",
//     "   \x7C               [ BOOTING SYSTEM... ]              \x7C   ",
//     "   \x2B--------------------------------------------------\x2B   ",
//     "",
//     NULL
// };

void show_splash() {
    for (int i = 0; splash_msg[i] != NULL; i++) {
        print((char*)splash_msg[i]);  // ✅ Cast to match print(char*)
        print("\n");
    }
}

void show_progress_bar() {
    print("\nLoading: [");
    int bar_len = 30;
    int delay = 15000000;  // Adjust this if it feels too fast or slow

    // Move cursor back inside brackets
    for (int i = 0; i < bar_len + 1; i++) {
        print("\b");
    }

    // Fill the bar block by block, with delay AFTER each block
    for (int i = 0; i < bar_len; i++) {
        print("\xDB");  // █ block

        // Small delay **after printing block**
        for (volatile int j = 0; j < delay; j++) {
            __asm__ __volatile__("nop");
        }
    }

    print("] Done.\n\n");
}


void kernel_main() {
    clear_screen();
    show_splash();
    show_progress_bar();

    print("Type 'help' for available commands\n");
    init_cli();
}
