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
    int buflen = snprintf(
        buf, sizeof(buf), "\x1b[1mSCORE: %3d\x1b[m", 
        game.score
    );
    
    if (buflen > game.screenCols) buflen = game.screenCols;
    abAppend(ab, buf, buflen);
    abAppend(ab, "\x1b[K", 3); 
}

void mainMenuRefreshScreen()
{
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);

    abAppend(&ab, "\x1b[H", 3);

    drawMainMenu(&ab);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void drawMainMenu(struct abuf *ab)
{
    for (int row = 0; row < game.screenRows - 1; row++)
    {
        abAppend(ab, "\x1b[1m", 4);
        if (row == game.screenRows / 3) displayCenteredText("Snake Game", ab);
        abAppend(ab, "\x1b[m", 3);


        if (row == game.screenRows / 3 + 3) 
        {
            if (game.hoverOption == PLAY) abAppend(ab, "\x1b[1;33m", 7);

                displayCenteredText("Play", ab);

            if (game.hoverOption == PLAY) abAppend(ab, "\x1b[m", 3);
        }

        if (row == game.screenRows / 3 + 5) 
        {   
            if (game.hoverOption == LEADERBOARDS) abAppend(ab, "\x1b[1;33m", 7);

            displayCenteredText("Leaderboards", ab);

            if (game.hoverOption == LEADERBOARDS) abAppend(ab, "\x1b[m", 3);
        }

        if (row == game.screenRows / 3 + 7) 
        {  
            if (game.hoverOption == SETTINGS) abAppend(ab, "\x1b[1;33m", 7);

            displayCenteredText("Settings", ab);

            if (game.hoverOption == SETTINGS) abAppend(ab, " \x1b[m", 3);
        }

        if (row == game.screenRows / 3 + 9) 
        {
            if (game.hoverOption == EXIT) abAppend(ab, "\x1b[1;33m", 7);

            displayCenteredText("Exit", ab);

            if (game.hoverOption == EXIT) abAppend(ab, "\x1b[m", 3);
        }

        abAppend(ab, "\x1b[K", 3); 

        if (row < game.screenRows - 1) abAppend(ab, "\r\n", 2);
    }

    char buf[128];
    int buflen = snprintf(
        buf, sizeof(buf), "\x1b[1mNAME: %s\x1b[m", 
        game.username ? game.username : ""
    );
    
    if (buflen > game.screenCols) buflen = game.screenCols;
    abAppend(ab, buf, buflen);
    abAppend(ab, "\x1b[K", 3);
    
}

void gameOverRefreshScreen()
{
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);

    abAppend(&ab, "\x1b[H", 3);

    drawGameOverScreen(&ab);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void drawGameOverScreen(struct abuf *ab)
{
    char username[] = "_ _ _ _ _ _ _ _";

    if (game.username)
    {
        int j = 0;
        for (unsigned long i = 0; i < strlen(game.username); i++)
        {
            username[j] = game.username[i];
            j += 2;
        }
    }

    for (int row = 0; row < game.screenRows - 1; row++)
    {
        if (row == (game.screenRows / 2) - 4)
        {
            abAppend(ab, "\x1b[1;31m", 7);
            displayCenteredText("GAME OVER", ab);
            abAppend(ab, "\x1b[m", 3);
        }

        if (row == ((game.screenRows / 2) - 2))
        {
            abAppend(ab, "\x1b[1m", 4);
            displayCenteredText("Enter Name", ab);
            abAppend(ab, "\x1b[m", 3);
        }

        if (row == ((game.screenRows / 2) - 1))
        {
            abAppend(ab, "\x1b[1m", 4);
            displayCenteredText(username, ab);
            abAppend(ab, "\x1b[m", 3);
        }

        abAppend(ab, "\x1b[K", 3); 

        if (row < game.screenRows - 1) abAppend(ab, "\r\n", 2);
    }

    char buf[128];
    int buflen = snprintf(
        buf, sizeof(buf), "\x1b[1mNAME: %s\x1b[m", 
        game.username ? game.username : ""
    );
    
    if (buflen > game.screenCols) buflen = game.screenCols;
    abAppend(ab, buf, buflen);
    abAppend(ab, "\x1b[K", 3);

}

void displayCenteredText(const char* s, struct abuf *ab)
{
    int len = strlen(s);

    if (len > game.screenCols) len = game.screenCols;

    int padding = (game.screenCols - len) / 2;

    while (padding--) abAppend(ab, " ", 1);

    abAppend(ab, s, len);

}