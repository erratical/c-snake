#ifndef OUTPUT_H
#define OUTPUT_H

#include "../lib/buffer.h"
#include "../lib/game.h"

void gameRefreshScreen();
void gameDraw(struct abuf *ab);
void mainMenuRefreshScreen();
void drawMainMenu(struct abuf *ab);
void gameOverRefreshScreen();
void drawGameOverScreen(struct abuf *ab);
void displayCenteredText(const char* s, struct abuf *ab);


#endif 