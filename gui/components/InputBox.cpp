#include "InputBox.h"

bool DrawInputBox(Rectangle rect, const char* title, char* input, int& value,
                  bool& enableInput, int icon) {
  DrawTextEx(font_bold, title, {rect.x, rect.y - 20}, 22, 1, textColor);
  bool hasChanged = false;
  if (GuiTextBox(rect, input, 30, enableInput) && strlen(input)) {
    int id = atoi(input);
    value = id;
    hasChanged = true;
    // strcpy(input, "");
  }
  if (IsMouseButtonDown(0)) {
    if (CheckCollisionPointRec(
            (Vector2){(float)GetMouseX(), (float)GetMouseY()}, rect)) {
      enableInput = true;
    } else
      enableInput = false;
  }
  // GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  return GuiButton({rect.x + rect.width + 10, rect.y, 30, 30},
                   GuiIconText(icon, ""), true);
}