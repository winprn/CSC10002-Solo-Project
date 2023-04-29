#include "Helper.h"
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "Settings.h"
#include <bits/stdc++.h>

using namespace Settings;
using namespace std;

Color stringToColor(char* color) {
  Color res = {0};
  int len = strlen(color);
  for (int i = 0; i < len; i += 2) {
    int tmp =
        (color[i] >= 'A' ? (10 + (color[i] - 'A')) : color[i] - '0') * 16 +
        (color[i + 1] >= 'A' ? (10 + (color[i + 1] - 'A'))
                             : color[i + 1] - '0');
    if (i == 0)
      res.r = tmp;
    if (i == 2)
      res.g = tmp;
    if (i == 4)
      res.b = tmp;
  }
  res.a = 255;

  return res;
}

Color getShade(Color color, int num) {
  color.r *= (1 - 0.1 * num);
  color.g *= (1 - 0.1 * num);
  color.b *= (1 - 0.1 * num);

  return color;
}

Color getTint(Color color, int num) {
  color.r += (255 - color.r) * 0.1 * num;
  color.g += (255 - color.g) * 0.1 * num;
  color.b += (255 - color.b) * 0.1 * num;

  return color;
}

char* intToHex(int num) {
  char* res = new char[2];
  int tmp = num % 16;
  if (tmp >= 10)
    res[1] = (char)('A' + tmp - 10);
  else
    res[1] = (char)('0' + tmp);

  num /= 16;
  tmp = num % 16;
  if (tmp >= 10)
    res[0] = (char)('A' + tmp - 10);
  else
    res[0] = (char)('0' + tmp);

  return res;
}

void printColorToFile(Color color) {
  FILE* out = fopen("settings.txt", "a");
  fprintf(out, "%s%s%s\n", intToHex(color.r), intToHex(color.g),
          intToHex(color.b));
  fclose(out);
}

void loadConfig(char* filePath) {
  char* fileData = LoadFileText(filePath);
  strtok(fileData, "\n");
  int cnt = 0;
  while (fileData != NULL) {
    switch (cnt) {
      case 0:
        backgroundColor = stringToColor(fileData);
        backgroundColor2 = getTint(backgroundColor);
        break;
      case 1:
        accentColor = stringToColor(fileData);
        accentColor2 = getShade(accentColor);
        break;
      case 2:
        textColor = stringToColor(fileData);
        break;

      default:
        break;
    }
    cnt++;
    fileData = strtok(NULL, "\n");
  }
}

float getAngle(Vector2 a, Vector2 b, Vector2 c) {
  return acos((Vector2DistanceSqr(a, c) + Vector2DistanceSqr(b, c) -
               Vector2DistanceSqr(a, b)) /
              (2 * Vector2Distance(a, c) * Vector2Distance(b, c)));
}

void setCurScreen(SCENE_TYPE screen) {
  curScreen = screen;
}