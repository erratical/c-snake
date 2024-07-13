#ifndef INPUT_H
#define INPUT_H

enum gameControls
{
    BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  END_KEY,
  HOME_KEY,
  PAGE_UP,
  PAGE_DOWN
};

void gameProcessKeypress();
void mainMenuSelection();
void inputUsername();

#endif