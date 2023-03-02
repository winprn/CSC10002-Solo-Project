#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../../lib/raylib.h"

class RectangleBase {
    public:
    Vector2 startPos;
    int width, height;
    Color color = BLACK;
    bool isOutdated = false;
    RectangleBase(Vector2 startPos, int w, int h, Color c = BLACK)
      : startPos{startPos}, width{w}, height{h}, color{c} {}

    void render() {
        if (isOutdated) {
            color.a -= 25;
            
            if (color.a <= 0) {
                color.a = 0;
                isOutdated = false;
            }
        }

        DrawRectangleLines(this->startPos.x, this->startPos.y, this->width, this->height, color);
    }

    void fadeOut() {
        isOutdated = true;
    }
};

#endif