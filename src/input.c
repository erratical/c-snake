#include "../lib/input.h"
#include "../lib/const.h"
#include "../lib/terminal.h"
#include "../lib/game.h"
#include <stdlib.h>

void gameProcessKeypress()
{
    int c = gameReadKey();

        switch (c)
        {
            case CTRL_KEY('q'):
                freeSnake(snakeHead);
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
                freeSnake(snakeHead);
                system("clear");
                exit(0);
                break;
            
            // select hover
            case '\r':
                game.menuOption = game.hoverOption;
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