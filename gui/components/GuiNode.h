#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"
#include "Arrow.h"
#include <cmath>

using namespace Settings;

class GuiNode {
  int val;
  Vector2 curPos, newPos;
  float curOpacity = 1.0, newOpacity, progress = 0, highlight = 0,
        curLength = 0, lineLength = 0, angle;
  bool isLast = false, isOutdated = false, isShifted = false,
       isHighlighted = false, isDone = false, isRemove = false,
       isLengthChanged = false, isHead = false, shouldRenderArrow = false;
  Arrow arrNext, arrPrev;
  Color highlightColor = BLACK;

 public:
  GuiNode() {}
  GuiNode(Vector2 pos) : curPos{pos} {}

  Vector2 getCurPos() { return curPos; }

  float getOpacity() { return curOpacity; }

  bool getHighlight() { return isHighlighted; }

  bool getIsDone() { return isDone; }

  bool getIsRemove() { return isRemove; }

  bool getIsLast() { return isLast; }

  bool getIsOutdate() { return isOutdated; }

  bool getIsShifted() { return isShifted; }

  bool getIsLengthChanged() { return isLengthChanged; }

  float getProgress() { return progress / highlight; }

  Vector2 getArrow() { return arrNext.start; }

  void render(bool isHighlight = 0) {
    if (isOutdated) {
      if (newOpacity > 0)
        curOpacity += 0.03;
      else
        curOpacity -= 0.03;

      if (fabs(curOpacity - newOpacity) <= 0.1) {
        curOpacity = newOpacity;
        isOutdated = false;
      }
    }

    if (isShifted) {
      double dx = newPos.x - curPos.x, dy = newPos.y - curPos.y;
      curPos.x += dx / 30;
      curPos.y += dy / 30;
      arrNext.start = {curPos.x + 60, curPos.y + 25};

      if (fabs(dx) <= 0.05 && fabs(dy) <= 0.05) {
        curPos = newPos;
        isShifted = false;
      }
    }

    Rectangle rect = {curPos.x, curPos.y, 70, 50};
    if (isHead) {
      DrawText("Head", curPos.x + 10, curPos.y - 20, 20,
               ColorAlpha(textColor, curOpacity));
    }
    if (isLast) {
      DrawText("Tail", curPos.x + 10, curPos.y - 20 + 70 * isHead, 20,
               ColorAlpha(textColor, curOpacity));
    }
    if (isHighlighted) {
      DrawRectangleRounded(rect, 0.15, 20, Fade(highlightColor, curOpacity));
      DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                 Fade(WHITE, curOpacity));
      DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 16, 20,
               Fade(WHITE, curOpacity));
      DrawText("cur", curPos.x + 20, curPos.y + 66, 20,
               ColorAlpha(textColor, curOpacity));
      progress += 0.016;
      // CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
      if (progress > highlight) {
        isDone = true;
        isHighlighted = false;
        progress = 0;
      }
    } else {
      DrawRectangleRounded(
          rect, 0.15, 20,
          ColorAlpha(primaryColor, (unsigned char)(curOpacity * 255)));
      DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                 Fade(BLACK, curOpacity));
      DrawText(TextFormat("%d", val), curPos.x + 20, curPos.y + 16, 20,
               Fade(BLACK, curOpacity));
    }
    if (shouldRenderArrow && !isRemove && arrNext.end.x != 0) {
      arrNext.render();
    }
  }

  void setVal(int nVal) { val = nVal; }

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
    } else
      isShifted = false;
    // render();
  }

  void setIsDone(bool isDone) { this->isDone = isDone; }

  void setIsRemove(bool isRemove) { this->isRemove = isRemove; }

  void setAngle(int angle) { this->angle = angle; }

  void setArrowNext(Vector2 s, Vector2 e) {
    arrNext = Arrow(s, e);
    // render();
  }

  void setArrowPrev(Vector2 s, Vector2 e) {
    arrPrev = Arrow(s, e);
    // render();
  }

  void setIsHead(bool isHead) { this->isHead = isHead; }

  void setHighLightColor(Color color) { highlightColor = color; }

  void setShouldRenderArrow(bool shouldRender) {
    shouldRenderArrow = shouldRender;
  }
};

#endif
