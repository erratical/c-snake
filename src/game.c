#include "../lib/game.h"
#include "../lib/terminal.h"
#include <stdlib.h>

void init()
{
    snakeHead = &game.snake;
    game.snake.nextSegment = NULL;
    game.snake.posX = 10;
    game.snake.posY = 0;
    game.snake.direction = NON;

    if (getWindowSize(&game.screenRows, &game.screenCols) == -1) die("getWindowSize");

    for (int i = 0; i < 5; i++)
    {
        linkSegment(&snakeHead, 0, 0);
    }

}

void updateEntity()
{

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
}

void updateNextSegment(entity *segment, int posX, int posY)
{
    if (segment->nextSegment == NULL) return;
    int prevPosX = segment->nextSegment->posX;
    int prevPosY = segment->nextSegment->posY;

    segment->nextSegment->posX = posX;
    segment->nextSegment->posY = posY;

    updateNextSegment(segment->nextSegment, prevPosX, prevPosY);
}

entity* createSegment(int posX, int posY)
{
    entity *newSegment = (entity*) malloc(sizeof(entity));
    newSegment->posX = posX;
    newSegment->posY = posY;
    newSegment->nextSegment = NULL;

    return newSegment;
}
void linkSegment(entity** head, int posX, int posY)
{
    entity *newSegment = createSegment(posX, posY);
    
    if (*head == NULL)
    {
        *head = newSegment;
    }
    else 
    {
        entity *temp = *head;
        while (temp->nextSegment != NULL)
        {
            temp = temp->nextSegment;
        }

        temp->nextSegment = newSegment;
    }
}

int findSnakeBody(int row, int col, entity *head)
{
    entity *temp = head;
    while (temp != NULL)
    {
        if ((temp->posX + 1 == col) && (temp->posY + 1 == row)) return 1;
        temp = temp->nextSegment;
    }
    return 0;
}

void freeSnake(entity *head)
{
    entity *temp;
    entity *current = head->nextSegment;  // Start from the second segment
    while (current != NULL)
    {
        temp = current;
        current = current->nextSegment;
        free(temp);
    }
    head->nextSegment = NULL;  // Set the next pointer of the first segment to NULL
}