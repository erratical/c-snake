#include "../lib/input.h"
#include "../lib/const.h"
#include "../lib/terminal.h"
#include "../lib/game.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void gameProcessKeypress()
{
    int c = gameReadKey();

        switch (c)
        {
            case CTRL_KEY('q'):
                freePointers(snakeHead);
                system("clear");
                exit(0);
                break;
            
            case ARROW_DOWN:
            case 's':
                if (game.snake.direction != UP ) 
                {
                    game.snake.direction = DOWN;
                    game.snake.body = 'v';
                }
                break;

            case ARROW_UP:
            case 'w':
                if (game.snake.direction != DOWN) 
                {
                    game.snake.direction = UP;
                    game.snake.body = '^';
                }
                break;
            
            case ARROW_LEFT:
            case 'a':
                if (game.snake.direction != RIGHT) 
                {
                    game.snake.direction = LEFT;
                    game.snake.body = '<';
                }
                break;
            
            case ARROW_RIGHT:
            case 'd':
                if (game.snake.direction != LEFT) 
                {
                    game.snake.direction = RIGHT;
                    game.snake.body = '>';
                }
                break;
            
            default:
                break;
        }
}

void mainMenuSelection()
{
    int c = gameReadKey();

    switch (c)
        {
            case CTRL_KEY('q'):
                freePointers(snakeHead);
                system("clear");
                exit(0);
                break;
            
            // select hover
            case '\r':
                game.menuOption = game.hoverOption;
                if (game.hoverOption == PLAY) refreshGame();
                break;
            
            case ARROW_UP:
            case 'w':
            if (game.hoverOption > PLAY)
                game.hoverOption--;
                break;

            case ARROW_DOWN:
            case 's':
            if (game.hoverOption < EXIT)
                game.hoverOption++;
                break;
        }
}

void inputUsername()
{
    size_t bufsize = 16;
    char *buf = malloc(bufsize);
    size_t buflen = 0;

    buf[0] = '\0';

    if (game.username) 
    {
        buf = strdup(game.username);
        buflen = strlen(game.username);
    }

    int c = gameReadKey();

    // Allow for backspacing
    if ( c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE)
    {
        if (buflen != 0) buf[--buflen] = '\0';
    }
    // Ctrl-Q, cancel username
    else if (c == CTRL_KEY('q'))
    {
        game.username = NULL;
        game.menuOption = MENU;
        free(buf);
        return;
    }
    // Enter Key, save as file name
    else if (c == '\r')
    {
        if (buflen != 0)
        {
            game.username = strdup(buf);
            game.menuOption = MENU;
            updateLeaderboard();
            free(buf);
            return;
        }
    }
    // Normal character keys
    else if (!iscntrl(c) && c < 128)
    {
        if (buflen < 8)
        {
            buf[buflen++] = c;
            buf[buflen] = '\0';
        }
    }

    game.username = strdup(buf);
}