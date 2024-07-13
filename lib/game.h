#ifndef GAME_H
#define GAME_H

#include <termios.h>

enum directions  
{
    UP = 900,
    DOWN,
    LEFT,
    RIGHT,
    NON
};

enum segmentTypes
{
    HEAD = 100,
    BODY
};

typedef struct playerEntity
{
    //int length;
    int posX;
    int posY;
    int direction;
    char body; 
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
    int score;
    int menuOption;
    int hoverOption;
    char *username;
    struct termios terminalSettings; 
};

struct gameConfig game;
Entity *snakeHead;

Entity* createSegment();
void linkSegment(Entity** head, int posX, int posY);
void refreshGame();
void init();
void updateEntities();
void updateNextSegment(Entity* segment, int posX, int posY, int direction);
Entity* findSnakeBody(int row, int col, Entity *head);
void freePointers(Entity* head);
void generateBerry(int *posX, int *posY);
int spawnBerry(int posX, int posY);
void gameOver();

#endif