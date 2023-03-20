#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include <cmath>

class GuiNode {
    int val, highlight;
    Vector2 curPos, newPos;
    float curOpacity = 1.0, newOpacity, progress = 0, curLength = 0, lineLength = 0, angle;
    bool isLast = false, isOutdated = false, isShifted = false, isHighlighted = false, isDone = false, isRemove = false, isLengthChanged = false, isRotateArrow = false;

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

            if (fabs(dx) <= 0.05 && fabs(dy) <= 0.05) {
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
            if (isRotateArrow) {
                DrawLine(curPos.x + 80, curPos.y + 25, curPos.x + 80 + curLength, curPos.y + 25 + 80 * tan(angle * PI / 180), Fade(BLACK, curOpacity));
                DrawTriangle({curPos.x + 80 + curLength, curPos.y + 25 + 80 * tan(angle * PI / 180)}, {curPos.x + 70 + curLength + 20 * cos(PI/4) * tan(angle * PI / 180), curPos.y + 15 + 80 * tan(angle * PI / 180)}, {curPos.x + 70 + curLength, curPos.y + 35 - 20 * cos(PI/4) * tan(angle * PI / 180) + 80 * tan(angle * PI / 180)}, Fade(BLACK, 1.0));
                if (curLength == lineLength) {
                    isLengthChanged = false;
                    angle -= 0.5;
                    if (angle < 0) {
                        angle = 0;
                        isRotateArrow = false;
                    }
                } else curLength++;
            } else {
                DrawLine(curPos.x + 80, curPos.y + 25, curPos.x + 130, curPos.y + 25, Fade(BLACK, curOpacity));
                DrawTriangle({curPos.x + 130, curPos.y + 25}, {curPos.x + 120, curPos.y + 15}, {curPos.x + 120, curPos.y + 35}, Fade(BLACK, curOpacity));
            }
        }
        
        if (isLast && isLengthChanged) {
            DrawLine(curPos.x + 80, curPos.y + 25, curPos.x + 80 + curLength, curPos.y + 25, Fade(BLACK, curOpacity));
            DrawTriangle({curPos.x + 80 + curLength, curPos.y + 25}, {curPos.x + 70 + curLength, curPos.y + 15}, {curPos.x + 70 + curLength, curPos.y + 35}, Fade(BLACK, curOpacity));
            curLength--;
            if (curLength == lineLength) {
                isLengthChanged = false;
            }
        }
    }

    void setVal(int nVal) {
        val = nVal;
    }

    void setIsLast(bool isLast) {
        this->isLast = isLast;
        if (!isLast) {
            lineLength = 50;
        } else lineLength = 0;
        isLengthChanged = fabs(curLength - lineLength) > 1;
        // render();
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

    void setAngle(int angle) {
        this->angle = angle;
    }

    void setIsRotateArrow(bool isRotate) {
        isRotateArrow = isRotate;
        angle = 30;
        render();
    }
};

#endif