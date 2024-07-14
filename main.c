#include "lib/terminal.h"
#include "lib/game.h"
#include "lib/output.h"
#include "lib/input.h"
#include "lib/const.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
  enterRawMode();
  init();
  loadLeaderboard();
  
  while (1)
  {
    if (game.menuOption == MENU)
    {
      mainMenuRefreshScreen();
      mainMenuSelection();
    }

    else if (game.menuOption == PLAY)
    {
      // add a way to init game?
      gameRefreshScreen();
      usleep(65000); // / 1000 for milliseconds
      gameProcessKeypress();
    }
    else if (game.menuOption == GAME_OVER)
    {
      gameOverRefreshScreen();
      inputUsername();
    }
    else if (game.menuOption == LEADERBOARDS)
    {
      //TODO
    }
    else if (game.menuOption == SETTINGS)
    {
      //TODO
    }
    else if (game.menuOption == EXIT)
    {
      saveLeaderboard();
      system("clear");
      break;
    }
  }

  freePointers(snakeHead);
  exitRawMode();
}