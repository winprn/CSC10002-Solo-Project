#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include <cmath>

class GuiNode {
    int val;
    Vector2 curPos, newPos;
    float curOpacity = 1.0, newOpacity;
    bool isOutdated = false, isShifted = false;

    public:
    GuiNode() {}
    GuiNode(Vector2 pos): curPos{pos}{}

    Vector2 getCurPos() {
        return curPos;
    }

    void render() {
        if (isOutdated) {
            curOpacity -= 0.02;
            
            if (fabs(curOpacity - newOpacity) <= 0.001) {
                curOpacity = 0;
                isOutdated = false;
            }
        }

        if (isShifted) {
            double dx = newPos.x - curPos.x, dy = newPos.y - curPos.y;
            curPos.x += dx / 60;
            curPos.y += dy / 60;

            if (fabs(dx) <= 0.001 && fabs(dy) <= 0.001) {
                curPos = newPos;
                isShifted = false;
            }
        }

        DrawRectangleLines(this->curPos.x, this->curPos.y, 50, 50, Fade(BLACK, curOpacity));
    }

    void setNewOpacity(float opacity) {
        newOpacity = opacity;
        isOutdated = true;
    }

    void setNewPos(Vector2 pos) {
        newPos = pos;
        isShifted = true;
    }
};

#endif