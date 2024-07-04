#include "../lib/terminal.h"
#include "../lib/game.h"

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>

void enterRawMode()
{
    if (tcgetattr(STDIN_FILENO, &(game.terminalSettings)) == -1) die("tcgetattr");

    atexit(exitRawMode);

    struct termios raw = game.terminalSettings;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1; // read time out

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr"); 
}

void exitRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &(game.terminalSettings)) == -1) die("tcsetattr"); 
}

void die(const char *str)
{
    system("clear");
    perror(str);
    exit(1);
}

int gameReadKey()
{
    char c = '\0';

    read(STDIN_FILENO, &c, 1);

    if (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 'w';
                case 'B': return 's';
                case 'C': return 'd';
                case 'D': return 'a';
            }
        }

        return '\x1b';
  } 
  else 
  {
    return c;
  }
}

int getWindowSize(int* rows, int* cols)
{
    struct winsize ws;

    // If ioctl has failed, manually position cursor to the bottom right
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
    {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
        
        return getCursorPosition(rows, cols);
    }
    
    else 
    {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

int getCursorPosition(int* rows, int* cols)
{
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
    
    while (i < sizeof(buf) - 1)
    {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }

    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

    return 0;
}
