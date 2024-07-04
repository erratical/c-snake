#include "../lib/game.h"
#include "../lib/output.h"
#include "../lib/buffer.h"
#include "../lib/const.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void gameRefreshScreen()
{ 
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);

    abAppend(&ab, "\x1b[H", 3);

    updateEntities();
    gameDraw(&ab);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void gameDraw(struct abuf *ab)
{
    Entity *segment;

    int snakePosX = game.snake.posX + 1;
    int snakePosY = game.snake.posY + 1;

    for (int row = 0; row < game.screenRows - 1; row++)
    {
        if (row == 0 || row == game.screenRows - 2)
        {
            for (int col = 0; col < game.screenCols-1; col++) 
            {
                (col % 2) ? abAppend(ab, " ", 1) : abAppend(ab, "*", 1);
            }
        }
        else
        {
            abAppend(ab, "*", 1);

            for (int col = 0; col < game.screenCols-3; col++) 
            {
                if (spawnBerry(row, col))
                {
                    char buf[16];
                    int buflen = snprintf(buf, sizeof(buf), "\x1b[%s;%sm@\x1b[m", ANSI_BOLD, ANSI_RED);
                    abAppend(ab, buf, buflen);
                }
                else if ((segment = findSnakeBody(row, col, snakeHead)))
                {
                    char buf[16];
                    int buflen = (segment == snakeHead) ?
                        snprintf(buf, sizeof(buf), "\x1b[%s;%sm%c\x1b[m", ANSI_BOLD, ANSI_YELLOW, snakeHead->body) :
                        snprintf(buf, sizeof(buf), "\x1b[%s;%sm%c\x1b[m", ANSI_BOLD, ANSI_GREEN, segment->body);
                    abAppend(ab, buf, buflen);
                }
                else abAppend(ab, " ", 1);
            }
             
            abAppend(ab, "*", 1);
        }

        abAppend(ab, "\x1b[K", 3); 
        if (row < game.screenRows - 1) abAppend(ab, "\r\n", 2);
    }

    char buf[128];
    int collision = findSnakeBody(snakePosY, snakePosX, snakeHead->nextSegment) ? 1 : 0;
    int buflen = snprintf(
        buf, sizeof(buf), "SPX: %3d, SPY: %3d, BPX: %3d, BPY: %3d COLLIDE: \x1b[1;31m%3d\x1b[m", 
        snakePosX, snakePosY, game.spawnedBerry.posX, game.spawnedBerry.posY, collision
    );
    
    if (buflen > game.screenCols) buflen = game.screenCols;
    abAppend(ab, buf, buflen);
    abAppend(ab, "\x1b[K", 3); 
}