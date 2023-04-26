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
  int val;
  Vector2 curPos, newPos;
  float curOpacity = 1.0;
  bool hasValue = false, isSelected = false;
  char text[20] = "";
  Color highlightColor = Color({125, 126, 120, 255});

  ArrayGuiNode() {}
  ArrayGuiNode(Vector2 pos) : curPos{pos} {}

  Vector2 getCurPos() { return curPos; }

  bool getIsClicked() {
    if (CheckCollisionPointRec(GetMousePosition(),
                               {curPos.x, curPos.y, 70, 50})) {
      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        return true;
    }
    return false;
  }

  void render(bool isHighlight = 0) {
    Rectangle rect = {curPos.x, curPos.y, 40, 40};

    Vector2 textPos = MeasureTextEx(font_bold, TextFormat("%d", val), 22, 1);
    if (!hasValue) {
      DrawRectangleRoundedLines(rect, 0.12, 20, 0,
                                Fade(primaryColor, curOpacity));
    } else {
      DrawRectangleRounded(rect, 0.12, 20, Fade(highlightColor, (isSelected ? 1 : 0.4)));
      DrawRectangleRoundedLines(rect, 0.12, 20, 0,
                                Fade(primaryColor, curOpacity));
      DrawTextEx(font_bold, TextFormat("%d", val),
                 {curPos.x + (rect.width - textPos.x) / 2,
                  curPos.y + (rect.height - textPos.y) / 2},
                 22, 1, Fade(textColor, curOpacity));
    }
  }

  void setCurPos(Vector2 pos) { curPos = pos; }

  void setVal(int nVal) { val = nVal; }

  void setHasValue(bool nHasValue) { hasValue = nHasValue; }

  void setIsSelected(bool selected) { isSelected = selected; }
};

#endif
