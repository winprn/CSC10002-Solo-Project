#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"
#include "Arrow.h"
#include <cmath>
#include <cstring>

using namespace Settings;

class GuiNode {
 public:
  int val;
  Vector2 curPos, newPos;
  float curOpacity = 1.0, newOpacity, progress = 0, highlight = 0,
        curLength = 0, lineLength = 0, angle;
  bool isLast = false, isOutdated = false, isShifted = false,
       isHighlighted = false, isDone = false, isRemove = false,
       isLengthChanged = false, isHead = false, isSelected = false,
       shouldRenderArrowNext = false, shouldRenderArrowPrev = false,
       isDoublyNode = false, isStackNode = false;
  char text[20] = "";
  Arrow arrNext, arrPrev;
  Color highlightColor = Color({125, 126, 120, 255});

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

  bool getIsClicked() {
    if (CheckCollisionPointRec(GetMousePosition(),
                               {curPos.x, curPos.y, 70, 50})) {
      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        return true;
    }
    return false;
  }

  void render(bool isHighlight = 0) {
    if (isShifted) {
      double dx = newPos.x - curPos.x, dy = newPos.y - curPos.y;
      if (isStackNode) {
        if (isRemove) {
          if (fabs(dy) <= 1) {
            if (isOutdated) {
              if (newOpacity > 0)
                curOpacity += (0.03 / animationSpeed);
              else
                curOpacity -= 0.03;

              if (fabs(curOpacity - newOpacity) <= 0.1) {
                curOpacity = newOpacity;
                isOutdated = false;
              }
            }
            if (fabs(dx) <= 0.5) {
              curPos = newPos;
              isShifted = false;
            } else {
              curPos.x += dx / (30 / animationSpeed);
            }
          } else {
            curPos.y += dy / (30 / animationSpeed);
          }
        } else {
          if (fabs(dx) <= 0.5) {
            if (fabs(dy) <= 0.5) {
              curPos = newPos;
              isShifted = false;
            } else {
              curPos.y += dy / (30 / animationSpeed);
            }
          } else {
            curPos.x += dx / (30 / animationSpeed);
          }
        }
      } else {
        curPos.x += dx / (30 / animationSpeed);
        curPos.y += dy / (30 / animationSpeed);
        // arrNext.start = {curPos.x + 60, curPos.y + 25};

        if (fabs(dx) <= 0.05 && fabs(dy) <= 0.05) {
          curPos = newPos;
          isShifted = false;
        }
      }
    }

    Rectangle rect = {curPos.x, curPos.y, 0, 0};
    if (isStackNode) {
      rect.width = 110;
      rect.height = 40;
    } else {
      rect.width = 70;
      rect.height = 50;
    }
    if (isHead && !isStackNode) {
      DrawTextEx(font_regular, "Head", {curPos.x + 10, curPos.y - 26}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }
    if (isLast && !isStackNode) {
      DrawTextEx(font_regular, "Tail",
                 {curPos.x + 10, curPos.y - 26 + 76 * isHead}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }
    if (strlen(text) > 0 && !isStackNode) {
      DrawTextEx(font_regular, text, {curPos.x + 10, curPos.y + 50}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }

    if (isStackNode) {
      DrawRectangleRoundedLines(rect, 0.12, 20, 2,
                                Fade(primaryColor, curOpacity));
      DrawTextEx(font_bold, TextFormat("%d", val),
                 {curPos.x + 45, curPos.y + 8}, 22, 1,
                 Fade(textColor, curOpacity));
      if (isHighlighted)
        progress += (0.016 * animationSpeed);
      // CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
      if (progress > highlight) {
        isDone = true;
        isHighlighted = false;
        progress = 0;
      }
    } else if (!isDoublyNode) {
      if (isHighlighted || isSelected) {
        DrawRectangleRounded(rect, 0.12, 20, Fade(highlightColor, curOpacity));
        DrawRectangleRoundedLines(rect, 0.12, 20, 2,
                                  Fade(primaryColor, curOpacity));
        DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                   Fade(WHITE, curOpacity));
        DrawTextEx(font_bold, TextFormat("%d", val),
                   {curPos.x + 20, curPos.y + 16}, 22, 1,
                   Fade(textColor, curOpacity));
        if (!isSelected) {
          DrawTextEx(font_regular, "cur", {curPos.x + 20, curPos.y + 66}, 22, 1,
                     ColorAlpha(textColor, curOpacity));
        }
        if (isHighlighted)
          progress += (0.016 * animationSpeed);
        // CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
        if (progress > highlight) {
          isDone = true;
          isHighlighted = false;
          progress = 0;
        }
      } else {
        DrawRectangleRoundedLines(
            rect, 0.12, 20, 2,
            ColorAlpha(primaryColor, (unsigned char)(curOpacity * 255)));
        DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                   Fade(primaryColor, curOpacity));
        DrawTextEx(font_bold, TextFormat("%d", val),
                   {curPos.x + 20, curPos.y + 16}, 22, 1,
                   Fade(textColor, curOpacity));
      }
    } else {
      if (isHighlighted || isSelected) {
        DrawRectangleRounded(rect, 0.12, 20, Fade(highlightColor, curOpacity));
        DrawRectangleRoundedLines(rect, 0.12, 20, 2,
                                  Fade(primaryColor, curOpacity));
        DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                   Fade(WHITE, curOpacity));
        DrawLineEx({curPos.x + 18, curPos.y}, {curPos.x + 18, curPos.y + 50}, 2,
                   Fade(WHITE, curOpacity));
        DrawTextEx(font_bold, TextFormat("%d", val),
                   {curPos.x + 25, curPos.y + 16}, 22, 1,
                   Fade(textColor, curOpacity));
        if (!isSelected) {
          DrawTextEx(font_regular, "cur", {curPos.x + 20, curPos.y + 66}, 22, 1,
                     ColorAlpha(textColor, curOpacity));
        }
        if (isHighlighted)
          progress += (0.016 * animationSpeed);
        // CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
        if (progress > highlight) {
          isDone = true;
          isHighlighted = false;
          progress = 0;
        }
      } else {
        DrawRectangleRoundedLines(
            rect, 0.12, 20, 2,
            ColorAlpha(primaryColor, (unsigned char)(curOpacity * 255)));
        DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
                   Fade(primaryColor, curOpacity));
        DrawLineEx({curPos.x + 18, curPos.y}, {curPos.x + 18, curPos.y + 50}, 2,
                   Fade(WHITE, curOpacity));
        DrawTextEx(font_bold, TextFormat("%d", val),
                   {curPos.x + 25, curPos.y + 16}, 22, 1,
                   Fade(textColor, curOpacity));
      }
    }

    if (!isStackNode) {
      if (shouldRenderArrowNext && !isRemove) {
        if (arrNext.end.x != 0)
          arrNext.render();
      }
      if (shouldRenderArrowPrev && !isRemove) {
        if (arrPrev.end.x != 0)
          arrPrev.render();
      }
    }
  }

  void setCurPos(Vector2 pos) { curPos = pos; }

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

  void setHighLightColor(Color color = Color({125, 126, 120, 255})) {
    highlightColor = color;
  }

  void setShouldRenderArrowNext(bool shouldRender) {
    shouldRenderArrowNext = shouldRender;
  }

  void setShouldRenderArrowPrev(bool shouldRender) {
    shouldRenderArrowPrev = shouldRender;
  }

  void setText(const char* t) { strcpy(text, t); }

  void setIsSelected(bool selected) { isSelected = selected; }

  void setIsCycle(bool cycle) { arrNext.setIsCycle(cycle); }

  void setIsDoublyNode(bool isDoubly) { isDoublyNode = isDoubly; }

  void setIsStackNode(bool isStack) { isStackNode = isStack; }
};

#endif
