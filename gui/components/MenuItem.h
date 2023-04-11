#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "../../lib/raygui.h"
#include "../../lib/raylib.h"

class MenuItem {
 public:
  Rectangle rect;
  char* text;
  Image img;
  Texture2D texture;

  MenuItem(Rectangle r, char* t, char* path) {
    rect = r;
    text = t;
    this->img = LoadImage(path);
    this->texture = LoadTextureFromImage(img);
  }

  bool render();
};

bool drawRectangleMenu(Rectangle rect, char* text, char* imgPath);

#endif
