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

    Rectangle rect = {897, 420, 70, 50};
    DrawRectangleRoundedLines(rect, 0.12, 20, 2, primaryColor);
    DrawLineEx({rect.x + 52, rect.y}, {rect.x + 52, rect.y + 50}, 2,
               primaryColor);

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
          tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 1);
      CustomLog(LOG_INFO, TextFormat("Selected file: %s", filePath), 0);
      char* regularPath = (char*)malloc(strlen(filePath) + 1);
      char* boldPath = (char*)malloc(strlen(filePath) + 1);

      // read the file path until meets the pipe character
      int i = 0;
      while (filePath[i] != '|') {
        boldPath[i] = filePath[i];
        i++;
      }
      boldPath[i] = '\0';
      i++;
      int j = 0;
      while (filePath[i] != '\0') {
        regularPath[j] = filePath[i];
        i++;
        j++;
      }
      regularPath[j] = '\0';

      // load the font into font_regular and font_bold
      font_regular = LoadFontEx(regularPath, 96, NULL, 0);
      font_bold = LoadFontEx(boldPath, 96, NULL, 0);
    }
  }
};

#endif