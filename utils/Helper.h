#ifndef HELPER_H
#define HELPER_H

#include "../lib/raylib.h"
#include <string.h>

enum SCENE_TYPE {
  HOME_SCREEN,
  SLL_SCREEN,
  DLL_SCREEN,
  CLL_SCREEN,
  ST_SCREEN,
  QU_SCREEN,
  SA_SCREEN,
  DA_SCREEN,
  SETTING_SCREEN,
};

Color stringToColor(char* color);

Color getShade(Color color, int num = 3);

Color getTint(Color color, int num = 3);

char* intToHex(int num);

void printColorToFile(Color color);

void loadConfig(const char* filePath);

float getAngle(Vector2 a, Vector2 b, Vector2 c);

void setCurScreen(SCENE_TYPE screen);

#endif