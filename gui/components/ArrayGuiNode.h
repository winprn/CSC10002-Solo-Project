#ifndef ARRAY_GUI_NODE_H
#define ARRAY_GUI_NODE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"
#include <cmath>
#include <cstring>

using namespace Settings;

class ArrayGuiNode {
 public:
  int val = 0, index;
  Vector2 curPos, newPos;
  float curOpacity = 1.0;
  bool hasValue = false, isSelected = false, isHighlighted = false;
  char text[20] = "";
  Color highlightColor;

  ArrayGuiNode() {
    highlightColor = accentColor2;
    val = 0;
  }
  ArrayGuiNode(Vector2 pos) : curPos{pos} {}

  Vector2 getCurPos() { return curPos; }

  int getVal() { return val; }

  bool getIsClicked() {
    if (CheckCollisionPointRec(GetMousePosition(),
                               {curPos.x, curPos.y, 40, 40})) {
      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        return true;
    }
    return false;
  }

  void render(bool isHighlight = 0) {
    Rectangle rect = {curPos.x, curPos.y, 40, 40};

    if (!hasValue) {
      DrawRectangleRounded(rect, 0.12, 20, Fade(textColor, 0.1));
    } else {
      if (isHighlighted || isSelected) {
        // CustomLog(LOG_INFO, TextFormat("%d", highlightColor.r), 0);
        DrawRectangleRounded(rect, 0.12, 20, highlightColor);
      } else {
        DrawRectangleRounded(rect, 0.12, 20, Fade(textColor, 0.3));
      }
      // CustomLog(LOG_INFO, TextFormat("%d", val), 0);
      DrawRectangleRoundedLines(rect, 0.12, 20, 0,
                                Fade(primaryColor, 1));
      Vector2 textPos = MeasureTextEx(font_bold, TextFormat("%d", val), 22, 1);
      // CustomLog(LOG_INFO,
      //           TextFormat("%.2f, %.2f",
      //                      curPos.x + (rect.width - textPos.x) / 2,
      //                      curPos.y + (rect.height - textPos.y) / 2),
      //           0);
      DrawTextEx(font_bold, TextFormat("%d", val),
                 {curPos.x + (rect.width - textPos.x) / 2,
                  curPos.y + (rect.height - textPos.y) / 2},
                 22, 1, textColor);
      textPos = MeasureTextEx(font_regular, TextFormat("%d", index), 18, 1);
      DrawTextEx(font_regular, TextFormat("%d", index),
                 {curPos.x + (rect.width - textPos.x) / 2, curPos.y + 45}, 20,
                 1, textColor);
    }
  }

  void setCurPos(Vector2 pos) { curPos = pos; }

  void setVal(int nVal) { val = nVal; }

  void setIndex(int nIndex) { index = nIndex; }

  void setHasValue(bool nHasValue) { hasValue = nHasValue; }

  void setIsSelected(bool selected) { isSelected = selected; }

  void setIsHighlighted(bool nHighlighted) { isHighlighted = nHighlighted; }

  void setHighlightColor(Color nHighlightColor = accentColor2) {
    highlightColor = nHighlightColor;
  }
};

#endif
