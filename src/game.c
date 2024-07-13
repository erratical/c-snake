#include "../lib/game.h"
#include "../lib/terminal.h"
#include "../lib/const.h"
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>

void init()
{
    snakeHead = &game.snake;

    refreshGame();

    game.menuOption = MENU;
    game.hoverOption = PLAY;
    game.username = NULL;

    if (getWindowSize(&game.screenRows, &game.screenCols) == -1) die("getWindowSize");
}

void refreshGame()
{
    game.snake.nextSegment = NULL;
    game.snake.posX = 10;
    game.snake.posY = 0;
    game.snake.direction = NON;
    game.snake.body = '&';

    game.spawnedBerry.exists = 0;
    game.spawnedBerry.posX = 0;
    game.spawnedBerry.posY = 0;

    game.score = 0;
}

void updateEntities()
{

    if (!game.spawnedBerry.exists) 
    {
        generateBerry(&game.spawnedBerry.posX, &game.spawnedBerry.posY);
        game.spawnedBerry.exists = 1;
    }
        
    
    int prevPosX = game.snake.posX;
    int prevPosY = game.snake.posY;
    int prevDirection = game.snake.direction;

    switch (game.snake.direction) {
        case UP:
            if (game.snake.posY <= 0) 
            {
                gameOver();
                break;
            }
            game.snake.posY--;
            break;
        case DOWN:
            if (game.snake.posY >= game.screenRows - 4) 
            {
                gameOver();
                break;
            }
            game.snake.posY++;
            break;
        case LEFT:
            if (game.snake.posX <= 0) 
            {
                gameOver();
                break;
            }
            game.snake.posX -= 2;
            break;
        case RIGHT:
            if (game.snake.posX >= game.screenCols - 6) 
            {
                gameOver();
                break;
            }
            game.snake.posX += 2;
            break;
        case NON:
            break;
    }

    updateNextSegment(snakeHead, prevPosX, prevPosY, prevDirection);

    if (game.snake.posX + 1 == game.spawnedBerry.posX && game.snake.posY + 1 == game.spawnedBerry.posY)
    {
        game.score++;

        write(STDOUT_FILENO, "\a", 1);
        game.spawnedBerry.exists = 0;
        linkSegment(&snakeHead, prevPosX, prevPosY);
    }

    if (findSnakeBody(game.snake.posY + 1, game.snake.posX + 1, snakeHead->nextSegment))
        gameOver();
    
}

void gameOver()
{
    write(STDOUT_FILENO, "\a", 1);
    game.menuOption = GAME_OVER;
    freePointers(snakeHead);
    refreshGame();
}

void updateNextSegment(Entity *segment, int posX, int posY, int direction)
{
    if (segment->nextSegment == NULL) return;
    int prevPosX = segment->nextSegment->posX;
    int prevPosY = segment->nextSegment->posY;
    int prevDirection = segment->nextSegment->direction;

    segment->nextSegment->posX = posX;
    segment->nextSegment->posY = posY;
    segment->nextSegment->direction = direction;

    if (segment->nextSegment->direction == UP || segment->nextSegment->direction == DOWN)
    {
        segment->nextSegment->body = '|';
    } else segment->nextSegment->body = '-';

    updateNextSegment(segment->nextSegment, prevPosX, prevPosY, prevDirection);
}

Entity* createSegment()
{
    Entity *newSegment = (Entity*) malloc(sizeof(Entity));
    newSegment->nextSegment = NULL;

    return newSegment;
}
void linkSegment(Entity** head, int posX, int posY)
{
    Entity *newSegment = createSegment();
    
    if (*head == NULL)
    {
        *head = newSegment;
        newSegment->posX = 0;
        newSegment->posY = 0;
    }
    else 
    {
        Entity *temp = *head;
        while (temp->nextSegment != NULL)
        {
            temp = temp->nextSegment;
        }

        temp->nextSegment = newSegment;
        newSegment->posX = posX;
        newSegment->posY = posY;
        newSegment->direction = temp->direction;
        
        if (newSegment->direction == UP || newSegment->direction == DOWN)
        {
            newSegment->body = '|';
        } else newSegment->body = '-';
    } 
}

Entity* findSnakeBody(int row, int col, Entity *head)
{
    if (head == NULL) return NULL;
    
    Entity *temp = head;

    if ((head->posX + 1 == col) && (head->posY + 1 == row)) return head;

    if (temp->nextSegment == NULL) return NULL;

    temp = temp->nextSegment;

    while (temp != NULL)
    {
        int snakePosX = temp->posX + 1;
        int snakePosY = temp->posY + 1;

        if ((snakePosX == col) && (snakePosY == row)) return temp;
        temp = temp->nextSegment;
    }
    return NULL;
}

void freePointers(Entity *head)
{
    Entity *temp;
    Entity *current = head->nextSegment;
    while (current != NULL)
    {
        temp = current;
        current = current->nextSegment;
        free(temp);
    }
    head->nextSegment = NULL;

    free(game.username);
}

void generateBerry(int *posX, int *posY)
{
    int lowerLimit = 1;
    int upperLimitX = game.screenCols - 6;
    int upperLimitY = game.screenRows - 4;

    srand(time(NULL));

    int randX = (rand() % (upperLimitX - lowerLimit + 1)) + lowerLimit;
    int randY = (rand() % (upperLimitY - lowerLimit + 1)) + lowerLimit;

    *posX = (randX % 2 == 0) ? randX + 1 : randX;
    *posY = randY;
}

int spawnBerry(int row, int col)
{
    if (col == game.spawnedBerry.posX && row == game.spawnedBerry.posY)
    {
        return 1;
    }
    return 0;
}