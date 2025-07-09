#ifndef CLI_H
#define CLI_H

void init_cli();
void handle_command(char* cmd);
void read_input(char* buffer, int max_length);

#endif