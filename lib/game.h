#ifndef GAME_H
#define GAME_H

#include <termios.h>

enum directions  
{
    UP = 1000,
    DOWN,
    LEFT,
    RIGHT,
    NON
};

typedef struct playerEntity
{
    //int length;
    int posX;
    int posY;
    int direction; 
    struct playerEntity *nextSegment;

} entity;

struct gameConfig
{
    int screenRows;
    int screenCols;
    entity snake;
    struct termios terminalSettings; 
};

struct gameConfig game;
entity *snakeHead;

entity* createSegment(int posX, int posY);
void linkSegment(entity** head, int posX, int posY);
void init();
void updateEntity();
void updateNextSegment(entity** segment, int posX, int posY);
int findSnakeBody(int row, int col, entity *head);
void freeSnake(entity* head);

#endif