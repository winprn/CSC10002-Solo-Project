#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H

#include "../../lib/raygui.h"
#include "../../lib/gui_file_dialog.h"
#include "../../utils/Helper.h"
#include "../../utils/Settings.h"
#include "../components/ColorSelector.h"
#include <string.h>

using namespace Settings;

class SettingScreen {
  ColorSelector bg{&backgroundColor, {478, 167, 100, 100}, "Background Color"};
  ColorSelector text{&textColor, {897, 167, 100, 100}, "Text Color"};
  ColorSelector button{&accentColor, {478, 307, 100, 100}, "Button Color"};

 public:
  char filePath[512] = {0};
  GuiFileDialogState fileDialogState = InitGuiFileDialog(GetWorkingDirectory());

  void render() {
    if (GuiButton({25, 35, 100, 40}, GuiIconText(118, "Back"))) {
      curScreen = 0;
    }
    bg.render();
    text.render();
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
      colorUpdated = false;
    }

    if (GuiButton({701, 309, 180, 40}, GuiIconText(2, "Save config"))) {
      printColorToFile(backgroundColor);
      printColorToFile(accentColor);
      printColorToFile(textColor);
    }
    if (GuiButton({701, 367, 180, 40}, GuiIconText(5, "Load config"))) {
      fileDialogState.windowActive = true;
    }
    if (fileDialogState.windowActive)
      GuiLock();
    GuiUnlock();
    if (fileDialogState.SelectFilePressed) {
      if (IsFileExtension(fileDialogState.fileNameText, ".txt")) {
        strcpy(filePath, fileDialogState.fileNameText);
        CustomLog(LOG_INFO, TextFormat("Selected file: %s", filePath), 0);
        loadConfig(filePath);
        colorUpdated = true;
      }
      fileDialogState.SelectFilePressed = false;
    }
    GuiFileDialog(&fileDialogState);
  }
};

#endif