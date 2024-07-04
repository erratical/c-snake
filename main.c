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

  

  while (1)
  {
    if (game.menuOption == MENU)
    {
      mainMenuRefreshScreen();
      mainMenuSelection();
    }

    else if (game.menuOption == PLAY)
    {
      gameRefreshScreen();
      usleep(75000); // / 1000 for milliseconds
      gameProcessKeypress();
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
      break;
    }
  }

  freeSnake(snakeHead);
}