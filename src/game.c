#include "../lib/game.h"
#include "../lib/terminal.h"
#include <stdlib.h>
#include <time.h> 

void init()
{
    snakeHead = &game.snake;
    game.snake.nextSegment = NULL;
    game.snake.posX = 10;
    game.snake.posY = 0;
    game.snake.direction = NON;
    game.spawnedBerry.exists = 0;
    game.spawnedBerry.posX = 0;
    game.spawnedBerry.posY = 0;

    if (getWindowSize(&game.screenRows, &game.screenCols) == -1) die("getWindowSize");

    for (int i = 0; i < 5; i++)
    {
        linkSegment(&snakeHead, 0, 0);
    }

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

    switch (game.snake.direction) {
        case UP:
            if (game.snake.posY <= 0) break;
            game.snake.posY--;
            break;
        case DOWN:
            if (game.snake.posY >= game.screenRows - 4) break;
            game.snake.posY++;
            break;
        case LEFT:
            if (game.snake.posX <= 0) break;
            game.snake.posX -= 2;
            break;
        case RIGHT:
            if (game.snake.posX >= game.screenCols - 6) break;
            game.snake.posX += 2;
            break;
        case NON:
            break;
    }

    updateNextSegment(snakeHead, prevPosX, prevPosY);

    if (game.snake.posX + 1 == game.spawnedBerry.posX && game.snake.posY + 1 == game.spawnedBerry.posY)
    {
        game.spawnedBerry.exists = 0;
    }
}

void updateNextSegment(Entity *segment, int posX, int posY)
{
    if (segment->nextSegment == NULL) return;
    int prevPosX = segment->nextSegment->posX;
    int prevPosY = segment->nextSegment->posY;

    segment->nextSegment->posX = posX;
    segment->nextSegment->posY = posY;

    updateNextSegment(segment->nextSegment, prevPosX, prevPosY);
}

Entity* createSegment(int posX, int posY)
{
    Entity *newSegment = (Entity*) malloc(sizeof(Entity));
    newSegment->posX = posX;
    newSegment->posY = posY;
    newSegment->nextSegment = NULL;

    return newSegment;
}
void linkSegment(Entity** head, int posX, int posY)
{
    Entity *newSegment = createSegment(posX, posY);
    
    if (*head == NULL)
    {
        *head = newSegment;
    }
    else 
    {
        Entity *temp = *head;
        while (temp->nextSegment != NULL)
        {
            temp = temp->nextSegment;
        }

        temp->nextSegment = newSegment;
    }
}

int findSnakeBody(int row, int col, Entity *head)
{
    Entity *temp = head;
    while (temp != NULL)
    {
        if ((temp->posX + 1 == col) && (temp->posY + 1 == row)) return 1;
        temp = temp->nextSegment;
    }
    return 0;
}

void freeSnake(Entity *head)
{
    Entity *temp;
    Entity *current = head->nextSegment;  // Start from the second segment
    while (current != NULL)
    {
        temp = current;
        current = current->nextSegment;
        free(temp);
    }
    head->nextSegment = NULL;  // Set the next pointer of the first segment to NULL
}

void generateBerry(int *posX, int *posY)
{
    int lowerLimit = 0;
    int upperLimitX = game.screenCols - 6;
    int upperLimitY = game.screenRows - 4;

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