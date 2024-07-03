#ifndef OUTPUT_H
#define OUTPUT_H

#include "../lib/buffer.h"
#include "../lib/game.h"

void gameRefreshScreen();
void gameDrawBox(struct abuf *ab);
int findSnakeBody(int row, int col, entity *head);

#endif 