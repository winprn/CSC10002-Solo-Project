#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../utils/Settings.h"
#include "../../utils/Helper.h"
#include "./InputBox.h"

#include <string.h>

using namespace Settings;

class ColorSelector {
  Color* selectedColor;
  Rectangle rect;
  int curColor = 0;
  char *title = new char[30]{}, *currentColor = new char[30]{};
  bool enableInput = false;

 public:
  ColorSelector() : selectedColor(nullptr), rect({0, 0, 0, 0}){};
  ColorSelector(Color* color, Rectangle pos, char* title)
      : selectedColor(color), rect(pos), title(title) {
    updateCurrentColor();
  };

  void updateCurrentColor() {
    strcpy(currentColor, intToHex(selectedColor->r));
    strcat(currentColor, intToHex(selectedColor->g));
    strcat(currentColor, intToHex(selectedColor->b));
  }

  Color getSelectedColor() { return *selectedColor; }

  void render() {

    if (DrawInputBox({rect.x - 200, rect.y + 20, 150, 50}, title, currentColor,
                     curColor, enableInput)) {
      if (strlen(currentColor) == 6) {
        *selectedColor = stringToColor(currentColor);
      }
    }

    Color tmp = *selectedColor;
    *selectedColor = GuiColorPicker(rect, "", *selectedColor);
    if (tmp.r != selectedColor->r || tmp.g != selectedColor->g ||
        tmp.b != selectedColor->b) {
      updateCurrentColor();
    }
  }
};

#endif