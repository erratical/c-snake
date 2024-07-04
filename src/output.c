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
    //editorScroll();
    
    struct abuf ab = ABUF_INIT;

    // Hide cursor
    abAppend(&ab, "\x1b[?25l", 6);

    // Move cursor to top left
    abAppend(&ab, "\x1b[H", 3);

    updateEntities();
    gameDraw(&ab);
    

    //char buf[32];

    // if file exists, offset cursor to make space for line number

    //abAppend(&ab, buf, strlen(buf));

    // Show cursor
    //abAppend(&ab, "\x1b[?25h", 6);

    // Executes command
    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void gameDraw(struct abuf *ab)
{
    int segment;

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
            // BORDER
            abAppend(ab, "*", 1);

            for (int col = 0; col < game.screenCols-3; col++) 
            {
                if (spawnBerry(row, col))
                {
                    char buf[16];
                    int buflen = snprintf(buf, sizeof(buf), "\x1b[%s;%sm@\x1b[m", ANSI_BOLD, ANSI_RED);
                    abAppend(ab, buf, buflen);
                }
                else if ((segment = findSnakeBody(row, col, snakeHead)) != -1)
                {
                    char buf[16];
                    int buflen = (segment == 1) ?
                        snprintf(buf, sizeof(buf), "\x1b[%s;%sm@\x1b[m", ANSI_BOLD, ANSI_YELLOW) :
                        snprintf(buf, sizeof(buf), "\x1b[%s;%sm@\x1b[m", ANSI_BOLD, ANSI_GREEN);
                    abAppend(ab, buf, buflen);
                }
                else abAppend(ab, " ", 1);
            }
             
            // BORDER
            abAppend(ab, "*", 1);
        }

        abAppend(ab, "\x1b[K", 3); 
        if (row < game.screenRows - 1) abAppend(ab, "\r\n", 2);
    }

    char buf[128];
    int buflen = snprintf(
        buf, sizeof(buf), "GSX: %3d SPX: %3d, GSY: %3d, SPY: %3d, BPX: %3d, BPY: %3d",
        game.snake.posX, snakePosX, game.snake.posY, snakePosY, game.spawnedBerry.posX, game.spawnedBerry.posY
    );
    
    if (buflen > game.screenCols) buflen = game.screenCols;
    abAppend(ab, buf, buflen);
    abAppend(ab, "\x1b[K", 3); 
}