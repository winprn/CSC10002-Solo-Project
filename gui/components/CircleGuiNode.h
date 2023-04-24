#ifndef DOUBLY_GUI_NODE_H
#define DOUBLY_GUI_NODE_H

#include "GuiNode.h"
#include "CurveArrow.h"

class CircleGuiNode : public GuiNode {
 public:
  CircleGuiNode() {}
  CircleGuiNode(Vector2 pos) { setCurPos(pos); }
  
  CurveArrow arr;
  void render() {
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

    if (isShifted) {
      double dx = newPos.x - curPos.x, dy = newPos.y - curPos.y;
      curPos.x += dx / (30 / animationSpeed);
      curPos.y += dy / (30 / animationSpeed);
      // arrNext.start = {curPos.x + 60, curPos.y + 25};

      if (fabs(dx) <= 0.05 && fabs(dy) <= 0.05) {
        curPos = newPos;
        isShifted = false;
      }
    }

    Rectangle rect = {curPos.x, curPos.y, 70, 50};
    if (isHead) {
      DrawTextEx(font_regular, "Head", {curPos.x + 10, curPos.y - 26}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }
    if (isLast) {
      DrawTextEx(font_regular, "Tail",
                 {curPos.x + 10, curPos.y - 26 + 76 * isHead}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }
    if (strlen(text) > 0) {
      DrawTextEx(font_regular, text, {curPos.x + 10, curPos.y + 50}, 24, 1,
                 ColorAlpha(textColor, curOpacity));
    }
    if (isHighlighted || isSelected) {
        DrawCircleLines(rect.x, rect.y, 50, WHITE);
    //   DrawRectangleRounded(rect, 0.12, 20, Fade(highlightColor, curOpacity));
    //   DrawRectangleRoundedLines(rect, 0.12, 20, 2,
    //                             Fade(primaryColor, curOpacity));
    //   DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
    //              Fade(WHITE, curOpacity));
    //   DrawTextEx(font_bold, TextFormat("%d", val),
    //              {curPos.x + 20, curPos.y + 16}, 22, 1,
    //              Fade(textColor, curOpacity));
    //   if (!isSelected) {
    //     DrawTextEx(font_regular, "cur", {curPos.x + 20, curPos.y + 66}, 22, 1,
    //                ColorAlpha(textColor, curOpacity));
    //   }
      if (isHighlighted)
        progress += (0.016 * animationSpeed);
      // CustomLog(LOG_DEBUG, TextFormat("%f", progress), 0);
      if (progress > highlight) {
        isDone = true;
        isHighlighted = false;
        progress = 0;
      }
    } else {
      DrawCircleLines(rect.x, rect.y, 50, WHITE);
    //   DrawRectangleRoundedLines(
    //       rect, 0.12, 20, 2,
    //       ColorAlpha(primaryColor, (unsigned char)(curOpacity * 255)));
    //   DrawLineEx({curPos.x + 52, curPos.y}, {curPos.x + 52, curPos.y + 50}, 2,
    //              Fade(primaryColor, curOpacity));
    //   DrawTextEx(font_bold, TextFormat("%d", val),
    //              {curPos.x + 20, curPos.y + 16}, 22, 1,
    //              Fade(textColor, curOpacity));
    }
    arr.render();
  }

  void setAngle(float start, float end) {
      arr.setStartAngle(start);
      arr.setEndAngle(end);
  }
};

#endif