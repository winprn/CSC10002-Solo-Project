#include "Function.h"
#include "gui/components/Arrow.h"
#include "gui/components/GuiNode.h"
#include "gui/components/MenuItem.h"
#include "gui/scene/CircularLL.h"
#include "gui/scene/DoublyLL.h"
#include "gui/scene/SettingScreen.h"
#include "gui/scene/SingleLL.h"
#include "gui/scene/Stack.h"
#include "lib/raygui.h"
#include "lib/raylib.h"
#include "utils/Log.h"
#include "utils/Settings.h"
#include <bits/stdc++.h>

using namespace std;

void drawMenu() {
  DrawTextEx(Settings::font_regular, "Welcome to VisuAlgo - cloned by @winprn",
             {266, 32}, 48, 1, Color({233, 236, 239, 255}));
  DrawTextEx(Settings::font_regular, "Ly Dinh Minh Man - 22127255 - 22CLC06",
             {424, 98}, 24, 1, Color({233, 236, 239, 255}));

  MenuItem sll = MenuItem{
      {55, 191, 330, 200}, "Singly Linked List", "images/sll_menu.png"};
  MenuItem dll = MenuItem{
      {475, 191, 330, 200}, "Doubly Linked List", "images/dll_menu.png"};
  MenuItem cll = MenuItem{
      {895, 191, 330, 200}, "Circular Linked List", "images/cll_menu.png"};
  MenuItem stack =
      MenuItem{{55, 440, 330, 200}, "Stack", "images/stack_menu.png"};
  if (sll.render())
    curScreen = 1;
  if (dll.render())
    curScreen = 2;
  if (cll.render())
    curScreen = 3;
  if (stack.render())
    curScreen = 4;
}

void drawSettingButton() {
  if (GuiButton({1173, 30, 50, 50}, GuiIconText(140, ""), true)) {
    curScreen = 5;
  }
}

int main() {
  SetTraceLogCallback(CustomLog);
  InitWindow(1280, 720, "VisuAlgo in C++");
  SetTargetFPS(60);
  SingleLL ll;
  DoublyLL dll;
  CircularLL cll;
  Stack st;
  SettingScreen setting;
  ll.createRandomList(), dll.createRandomList(), cll.createRandomList(),
      st.createRandomList();
  GuiLoadStyle("gui/styles.rgs");
  GuiLoadIcons("gui/iconset.rgi", NULL);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
  GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
  Arrow arr({50, 300}, {100, 360});
  bool ok = 0;
  Settings::font_regular =
      LoadFontEx("gui/IBMPlexSerif-Regular.ttf", 96, NULL, 0);
  Settings::font_bold = LoadFontEx("gui/IBMPlexSerif-Bold.ttf", 96, NULL, 0);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(backgroundColor);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(accentColor));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(accentColor2));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(accentColor2));
    switch (curScreen) {
      case 0:
        drawMenu();
        drawSettingButton();
        break;
      case 1:
        ll.render();
        break;
      case 2:
        dll.render();
        break;
      case 3:
        cll.render();
        break;
      case 4:
        st.render();
        break;
      case 5:
        setting.render();
        break;
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
