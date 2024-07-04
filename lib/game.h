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

} Entity;

typedef struct berryObject 
{
    int exists;
    int posX;
    int posY;
} Berry;


struct gameConfig
{
    int screenRows;
    int screenCols;
    Entity snake;
    Berry spawnedBerry;
    struct termios terminalSettings; 
};

struct gameConfig game;
Entity *snakeHead;

Entity* createSegment(int posX, int posY);
void linkSegment(Entity** head, int posX, int posY);
void init();
void updateEntities();
void updateNextSegment(Entity* segment, int posX, int posY);
int findSnakeBody(int row, int col, Entity *head);
void freeSnake(Entity* head);
void generateBerry(int *posX, int *posY);
int spawnBerry(int posX, int posY);

#endif