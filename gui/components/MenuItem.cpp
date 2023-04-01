#include "MenuItem.h"
#include "../../utils/Settings.h"

Image MenuItem::img;
Texture2D MenuItem::texture;

bool MenuItem::render() {
  // read image from file and draw it
  DrawRectangleRounded(rect, 0.05, 20, ColorAlpha(Color({217, 217, 217, 255}), 0.5));
  DrawTexture(texture, rect.x, rect.y, WHITE);

  DrawTextEx(Settings::font_bold, text, {rect.x + 84, rect.y + 164}, 20, 1, WHITE);
  if (IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), rect)) return true;

  return false;
}