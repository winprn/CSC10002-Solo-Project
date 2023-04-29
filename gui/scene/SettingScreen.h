#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H

#include "../../lib/raygui.h"
#include "../../lib/tinyfiledialogs.h"
#include "../../utils/Helper.h"
#include "../../utils/Settings.h"
#include "../components/ColorSelector.h"
#include <string.h>

using namespace Settings;

class SettingScreen {
  ColorSelector node{&primaryColor, {897, 307, 100, 100}, "Node Color"};
  ColorSelector bg{&backgroundColor, {478, 167, 100, 100}, "Background Color"};
  ColorSelector text{&textColor, {897, 167, 100, 100}, "Text Color"};
  ColorSelector button{&accentColor, {478, 307, 100, 100}, "Button Color"};

 public:
  char filePath[512] = {0};

  void render() {
    if (GuiButton({25, 35, 100, 40}, GuiIconText(118, "Back"))) {
      curScreen = 0;
    }
    bg.render();
    text.render();
    node.render();
    Color tmp = accentColor;
    button.render();
    if (tmp.r != accentColor.r || tmp.g != accentColor.g ||
        tmp.b != accentColor.b) {
      accentColor2 = getShade(accentColor);
    }
    if (colorUpdated) {
      bg.updateCurrentColor();
      text.updateCurrentColor();
      button.updateCurrentColor();
      node.updateCurrentColor();
      colorUpdated = false;
    }

    if (GuiButton({551, 465, 180, 40}, GuiIconText(2, "Save config"))) {
      printColorToFile(backgroundColor);
      printColorToFile(accentColor);
      printColorToFile(textColor);
    }
    if (GuiButton({551, 520, 180, 40}, GuiIconText(5, "Load config"))) {
      const char* filePath =
          tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
      loadConfig(filePath);
      colorUpdated = true;
    }
    if (GuiButton({551, 575, 180, 40}, GuiIconText(5, "Load font"))) {
      const char* filePath =
          tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
      CustomLog(LOG_INFO, TextFormat("Selected file: %s", filePath), 0);
      font_regular = font_bold = LoadFontEx(filePath, 96, NULL, 0);
    }
  }
};

#endif