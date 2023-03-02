#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include <cmath>

class GuiNode {
    int val;
    Vector2 curPos;
    float curOpacity = 1.0, newOpacity;
    bool isOutdated = false;

    public:
    GuiNode(Vector2 pos): curPos{pos}{}

    Vector2 getCurPos() {
        return curPos;
    }

    void render() {
        if (isOutdated) {
            curOpacity -= 0.05;
            
            if (fabs(curOpacity - newOpacity) <= 0.05) {
                curOpacity = 0;
                isOutdated = false;
            }
        }

        DrawRectangleLines(this->curPos.x, this->curPos.y, 50, 50, Fade(BLACK, curOpacity));
    }

    void setNewOpacity(float opacity) {
        newOpacity = opacity;
        isOutdated = true;
    }
};

#endif