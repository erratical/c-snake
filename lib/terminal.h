#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

void enterRawMode();
void exitRawMode();
void die(const char *str);
int gameReadKey();
int getWindowSize(int *rows, int *cols);
int getCursorPosition(int *rows, int *cols);

#endif