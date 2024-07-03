#include "lib/terminal.h"
#include "lib/game.h"
#include "lib/output.h"
#include "lib/input.h"

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
      gameRefreshScreen();
      gameProcessKeypress();
    }
  
  freeSnake(snakeHead);
}