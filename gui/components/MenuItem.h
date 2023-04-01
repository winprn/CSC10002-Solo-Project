#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include "../../lib/raylib.h"
#include "../../lib/raygui.h"

class MenuItem {
    public:
    Rectangle rect;
    char *text;
    static Image img;
    static Texture2D texture;

    MenuItem(Rectangle r, char *t, char *path) {
        rect = r;
        text = t;
        this->img = LoadImage(path);
        this->texture = LoadTextureFromImage(img);
    }

    bool render();
};

bool drawRectangleMenu(Rectangle rect, char *text, char *imgPath);

#endif