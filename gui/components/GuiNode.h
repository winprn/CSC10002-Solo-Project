#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include <cmath>

class GuiNode {
    int val;
    Vector2 curPos, newPos;
    float curOpacity = 1.0, newOpacity;
    bool isLast = false, isOutdated = false, isShifted = false;

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
            curPos.x += dx / 30;
            curPos.y += dy / 30;

            if (fabs(dx) <= 5 && fabs(dy) <= 5) {
                curPos = newPos;
                isShifted = false;
            }
        }

        DrawRectangleLines(curPos.x, curPos.y, 100, 50, Fade(BLACK, curOpacity));
        if (!isLast) {
            DrawLine(curPos.x + 100, curPos.y + 25, curPos.x + 200, curPos.y + 25, Fade(BLACK, curOpacity));
            DrawTriangleLines({curPos.x + 200, curPos.y + 25}, {curPos.x + 190, curPos.y + 15}, {curPos.x + 190, curPos.y + 35}, Fade(BLACK, curOpacity));
        }
        DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 20, 20, Fade(BLACK, curOpacity));
    }

    void setVal(int nVal) {
        val = nVal;
    }

    void setIsLast(bool isLast) {
        this->isLast = isLast;
    }

    void setNewOpacity(float opacity) {
        newOpacity = opacity;
        isOutdated = true;
        render();
    }

    void setNewPos(Vector2 pos) {
        newPos = pos;
        isShifted = true;
        render();
    }
};

#endif