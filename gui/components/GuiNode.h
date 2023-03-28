#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "Arrow.h"
#include <cmath>

class GuiNode {
    int val, highlight;
    Vector2 curPos, newPos;
    float curOpacity = 1.0, newOpacity, progress = 0, curLength = 0, lineLength = 0, angle;
    bool isLast = false, isOutdated = false, isShifted = false, isHighlighted = false, isDone = false, isRemove = false, isLengthChanged = false, isHead = false;
    Arrow arr;

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

    bool getIsLast() {
        return isLast;
    }

    bool getIsOutdate() {
        return isOutdated;
    }

    bool getIsShifted() {
        return isShifted;
    }

    bool getIsLengthChanged() {
        return isLengthChanged;
    }

    Vector2 getArrow() {
        return arr.start;
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
            arr.start = {curPos.x + 80, curPos.y + 25};

            if (fabs(dx) <= 0.05 && fabs(dy) <= 0.05) {
                curPos = newPos;
                isShifted = false;
            }
        }

        Rectangle rect = {curPos.x, curPos.y, 80, 50};
        if (isHead) {
            DrawText("Head", curPos.x + 20, curPos.y - 20, 20, Fade(BLACK, curOpacity));
        }
        if (isHighlighted) {
            DrawRectangleRounded(rect, 0.1, 20, Fade(BLACK, curOpacity));
            DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 16, 20, Fade(WHITE, curOpacity));
            DrawText("cur", curPos.x + 20, curPos.y + 66, 20, Fade(BLACK, curOpacity));
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
            arr.render();
        }
    }

    void setVal(int nVal) {
        val = nVal;
    }

    void setIsLast(bool isLast) {
        this->isLast = isLast;
        // render();
    }

    void setNewHighlight(float h = 1) {
        progress = 0;
        highlight = h;
        isHighlighted = true;
        isDone = false;
        // render();
    }

    void setNewOpacity(float opacity) {
        newOpacity = opacity;
        isOutdated = true;
        // render();
    }

    void setNewPos(Vector2 pos) {
        newPos = pos;
        if (fabs(curPos.x - newPos.x) > 0.05 || fabs(curPos.y - newPos.y) > 0.05) {
            isShifted = true;
        } else isShifted = false;
        // render();
    }

    void setIsDone(bool isDone) {
        this->isDone = isDone;
    }

    void setIsRemove(bool isRemove) {
        this->isRemove = isRemove;
    }

    void setAngle(int angle) {
        this->angle = angle;
    }

    void setArrow(Vector2 s, Vector2 e) {
        arr = Arrow(s, e);
        // render();
    }

    void setIsHead(bool isHead) {
        this->isHead = isHead;
    }
};

#endif