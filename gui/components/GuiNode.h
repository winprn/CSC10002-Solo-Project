#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include <cmath>

class GuiNode {
    int val, highlight;
    Vector2 curPos, newPos;
    float curOpacity = 1.0, newOpacity, progress = 0;
    bool isLast = false, isOutdated = false, isShifted = false, isHighlighted = false, isDone = false, isRemove = false;

    public:
    GuiNode() {}
    GuiNode(Vector2 pos): curPos{pos}{}

    Vector2 getCurPos() {
        return curPos;
    }

    float getOpacity() {
        return curOpacity;
    }

    bool getHighlight() {
        return isHighlighted;
    }

    bool getIsDone() {
        return isDone;
    }

    bool getIsRemove() {
        return isRemove;
    }

    void render(bool isHighlight = 0) {
        if (isOutdated) {
            if (newOpacity > 0) curOpacity += 0.03;
            else curOpacity -= 0.03;
            
            if (fabs(curOpacity - newOpacity) <= 0.1) {
                curOpacity = newOpacity;
                isOutdated = false;
            }
        }

        if (isShifted) {
            double dx = newPos.x - curPos.x, dy = newPos.y - curPos.y;
            curPos.x += dx / 30;
            curPos.y += dy / 30;

            if (fabs(dx) <= 0.5 && fabs(dy) <= 0.5) {
                curPos = newPos;
                isShifted = false;
            }
        }

        Rectangle rect = {curPos.x, curPos.y, 80, 50};
        if (isHighlighted) {
            DrawRectangleRounded(rect, 0.1, 20, Fade(BLACK, curOpacity));
            DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 16, 20, Fade(WHITE, curOpacity));
            progress += 0.032;
            CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
            if (progress > highlight) {
                isDone = true;
                isHighlighted = false;
                progress = 0;
            }
        } else {
            DrawRectangleRoundedLines(rect, 0.1, 20, 2, Fade(BLACK, curOpacity));
            DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 16, 20, Fade(GREEN, curOpacity));
        }
        if (!isLast) {
            DrawLine(curPos.x + 80, curPos.y + 25, curPos.x + 130, curPos.y + 25, Fade(BLACK, curOpacity));
            DrawTriangle({curPos.x + 130, curPos.y + 25}, {curPos.x + 120, curPos.y + 15}, {curPos.x + 120, curPos.y + 35}, Fade(BLACK, curOpacity));
        }
    }

    void setVal(int nVal) {
        val = nVal;
    }

    void setIsLast(bool isLast) {
        this->isLast = isLast;
    }

    void setNewHighlight(float h = 1) {
        progress = 0;
        highlight = h;
        isHighlighted = true;
        isDone = false;
        render();
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

    void setIsDone(bool isDone) {
        this->isDone = isDone;
    }

    void setIsRemove(bool isRemove) {
        this->isRemove = isRemove;
    }
};

#endif