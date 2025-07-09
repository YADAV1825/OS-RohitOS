#include "cli.h"
#include "stdio.h"
#include "string.h"
#include <stddef.h>

#define MAX_INPUT 100
#define PORT_KEYBOARD_DATA 0x60
#define PORT_KEYBOARD_STATUS 0x64

char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','+','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0,' ',
    // rest are 0
};

static inline unsigned char inb(unsigned short port) {
    unsigned char val;
    asm volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

void wait_for_keypress() {
    while (!(inb(PORT_KEYBOARD_STATUS) & 1));
}

int uptime_seconds = 0;

void delay_one_second() {
    for (volatile int i = 0; i < 50000000; i++) {
        __asm__ __volatile__("nop");
    }
    uptime_seconds++;
}

void print_number(int n) {
    char buf[16];
    int i = 0;
    if (n == 0) {
        print("0");
        return;
    }
    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    for (int j = i - 1; j >= 0; j--) {
        char str[2] = { buf[j], 0 };
        print(str);
    }
}

void int_to_hex(unsigned int num) {
    char hex[] = "0123456789ABCDEF";
    char out[11] = "0x00000000";
    for (int i = 9; i >= 2 && num > 0; i--) {
        out[i] = hex[num % 16];
        num /= 16;
    }
    print(out);
}

void int_to_bin(unsigned int num) {
    char out[33];
    out[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        out[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
    print("0b");
    print(out);
}

const char* fortunes[] = {
    "Fortune: Code is like humor. When you have to explain it, it’s bad.",
    "Fortune: First, solve the problem. Then, write the code.",
    "Fortune: Debugging is like being the detective of a murder mystery.",
    "Fortune: Experience is the name everyone gives to their mistakes.",
    "Fortune: Talk is cheap. Show me the code.",
    "Fortune: Make it work, make it right, make it fast.",
    "Fortune: Computers do what you tell them, not what you want.",
    "Fortune: Software is a gas; it expands to fill its container.",
    "Fortune: Code never lies, comments sometimes do.",
    "Fortune: Programming is the art of algorithm design and problem solving."
};
int atoi(const char *str) {
    int res = 0;
    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

void init_cli() {
    char input[MAX_INPUT];
    int index = 0;
    int last_scancode = -1;

    print("> ");

    while (1) {
        wait_for_keypress();
        unsigned char scancode = inb(PORT_KEYBOARD_DATA);

        if (scancode & 0x80) {
            last_scancode = -1;
            continue;
        }

        if (scancode == last_scancode)
            continue;
        last_scancode = scancode;

        char ch = scancode_to_ascii[scancode];
        if (!ch) continue;

        if (ch == '\b' && index > 0) {
            index--;
            print("\b \b");
        } else if (ch == '\n') {
            input[index] = '\0';
            print("\n");
            handle_command(input);
            index = 0;
            print("> ");
        } else if (index < MAX_INPUT - 1) {
            char str[2] = { ch, 0 };
            print(str);
            input[index++] = ch;
        }
    }
}

void handle_command(char* cmd) {
    while (*cmd == ' ') cmd++;

    char command[16];
    char* arg = NULL;

    int i = 0;
    while (cmd[i] && cmd[i] != ' ' && i < 15) {
        command[i] = cmd[i];
        i++;
    }
    command[i] = '\0';

    if (cmd[i] == ' ') {
        arg = &cmd[i + 1];
        while (*arg == ' ') arg++;
    }

    if (strcmp(command, "help") == 0) {
        print("\nAvailable commands:\n");
        print("  help     - Show this help\n");
        print("  echo     - Print arguments\n");
        print("  clear    - Clear screen\n");
        print("  ver      - Show OS version\n");
        print("  sysinfo  - Show system info\n");
        print("  shutdown - Shutdown the OS\n");
        print("  whoami   - Show current user\n");
        print("  uptime   - Show system uptime\n");
        print("  date     - Show build date\n");
        print("  calc     - Add two numbers (e.g. calc 4 + 5)\n");
        print("  timer    - Start countdown (e.g. timer 5)\n");
        print("  hex      - Convert decimal to hex (e.g. hex 255)\n");
        print("  bin      - Convert decimal to binary (e.g. bin 10)\n");
        print("  fortune  - Show a random fortune\n");
    }
    else if (strcmp(command, "echo") == 0) {
        print("\n");
        if (arg && *arg)
            print(arg);
        print("\n");
    }
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(command, "ver") == 0) {
        print("\nRohit OS v0.1\n");
    }
    else if (strcmp(command, "sysinfo") == 0) {
        print("\n========== System Information ==========\n");
        print("OS Version   : Rohit OS v0.1\n");
        print("Author       : Rohit Yadav (NIT Jalandhar)\n");
        print("CPU Type     : Virtual CPU (16-bit)\n");
        print("RAM          : 65 KB\n");
        print("Storage      : Simulated / Virtual\n");
        print("Build Type   : Baremetal / VM\n");
        print("========================================\n");
    }
    else if (strcmp(command, "shutdown") == 0) {
        print("\nShutting down Rohit OS CLI...\n");
        for (;;) {
            __asm__ __volatile__("hlt");
        }
    }
    else if (strcmp(command, "whoami") == 0) {
        print("\nYou are: Rohit Yadav (root)\n");
    }
    else if (strcmp(command, "uptime") == 0) {
        print("\nUptime (seconds): ");
        print_number(uptime_seconds);
        print("\n");
    }
    else if (strcmp(command, "date") == 0) {
        print("\nBuild Date: "__DATE__" at "__TIME__"\n");
    }
    else if (strcmp(command, "calc") == 0) {
        if (!arg) {
            print("Usage: calc 5 + 2\n");
            return;
        }
        int a, b;
        char op;
        if (arg) {
    int parsed = 0;
    char *p = arg;
    a = atoi(p);

    // Skip digits
    while (*p >= '0' && *p <= '9') p++;
    while (*p == ' ') p++;

    op = *p;
    p++;
    while (*p == ' ') p++;

    b = atoi(p);
    parsed = 1;

    if (parsed) {
        int result = 0;
        if (op == '+') result = a + b;
        else if (op == '-') result = a - b;
        else if (op == '*') result = a * b;
        else if (op == '/' && b != 0) result = a / b;
        else {
            print("Invalid operation.\n");
            return;
        }
        print("Result: ");
        print_number(result);
        print("\n");
    } else {
        print("Usage: calc 5 + 2\n");
    }
}

    }
    else if (strcmp(command, "timer") == 0) {
        if (!arg) {
            print("Usage: timer <seconds>\n");
            return;
        }
        int seconds = atoi(arg);
        if (seconds <= 0) {
            print("Invalid number.\n");
            return;
        }
        print("Timer: ");
        for (int t = seconds; t > 0; t--) {
            print_number(t);
            print("... ");
            delay_one_second();
        }
        print("Time's up!\n");
    }
    else if (strcmp(command, "hex") == 0) {
        if (!arg) {
            print("Usage: hex <number>\n");
            return;
        }
        int num = atoi(arg);
        int_to_hex(num);
        print("\n");
    }
    else if (strcmp(command, "bin") == 0) {
        if (!arg) {
            print("Usage: bin <number>\n");
            return;
        }
        int num = atoi(arg);
        int_to_bin(num);
        print("\n");
    }
    else if (strcmp(command, "fortune") == 0) {
        static int idx = 0;
        print("\n");
        print((char*)fortunes[idx++ % 10]);

        print("\n");
    }
    else {
        print("\nUnknown command: ");
        print(cmd);
        print("\nType 'help' for available commands\n");
    }
}
