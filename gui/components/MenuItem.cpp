#include "MenuItem.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"

using namespace Settings;

bool MenuItem::render() {
  // read image from file and draw it
  DrawRectangleRoundedLines(
      {rect.x - 1, rect.y - 1, rect.width + 2, rect.height + 2}, 0.05, 20, 2,
      ColorAlpha(textColor, 0.6));
  DrawRectangleRounded(rect, 0.05, 20, backgroundColor);
  DrawTexture(texture, rect.x + 1, rect.y, WHITE);

  Vector2 pos = MeasureTextEx(font_bold, text, 20, 1);
  DrawTextEx(font_bold, text, {rect.x + (rect.width - pos.x) / 2, rect.y + 127},
             20, 1, textColor);
  if (IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), rect))
    return true;

  return false;
}
