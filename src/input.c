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
            // Exit Key 'Ctrl + Q'
            case CTRL_KEY('q'):
                freeSnake(snakeHead);
                system("clear");
                exit(0);
                break;
            
            case ARROW_DOWN:
            case 's':
                if (game.snake.direction != UP) game.snake.direction = DOWN;
                break;

            case ARROW_UP:
            case 'w':
                if (game.snake.direction != DOWN) game.snake.direction = UP;
                break;
            
            case ARROW_LEFT:
            case 'a':
                if (game.snake.direction != RIGHT) game.snake.direction = LEFT;
                break;
            
            case ARROW_RIGHT:
            case 'd':
                if (game.snake.direction != LEFT) game.snake.direction = RIGHT;
                break;
            
            default:
                break;
        }
}