#include "Function.h"
#include "gui/components/Arrow.h"
#include "gui/components/GuiNode.h"
#include "gui/components/MenuItem.h"
#include "gui/scene/CircularLL.h"
#include "gui/scene/DoublyLL.h"
#include "gui/scene/DynamicArray.h"
#include "gui/scene/Queue.h"
#include "gui/scene/SettingScreen.h"
#include "gui/scene/SingleLL.h"
#include "gui/scene/Stack.h"
#include "gui/scene/StaticArray.h"
#include "lib/raygui.h"
#include "lib/raylib.h"
#include "lib/rlgl.h"
#include "utils/Log.h"
#include "utils/Settings.h"
#include <bits/stdc++.h>

#define sqr(x) (x) * (x)

using namespace std;

void drawMenu() {
  DrawTextEx(Settings::font_regular, "Welcome to VisuAlgo - cloned by @winprn",
             {266, 32}, 48, 1, textColor);
  DrawTextEx(Settings::font_regular, "Ly Dinh Minh Man - 22127255 - 22CLC06",
             {424, 98}, 24, 1, textColor);
  Image logo = LoadImage("images/logo.png");
  Texture logoTexture = LoadTextureFromImage(logo);
  DrawTexture(logoTexture, 10, 25, WHITE);

  MenuItem sll = MenuItem{
      {27, 190, 260, 155}, "Singly Linked List", "images/sll_menu.png"};
  MenuItem dll = MenuItem{
      {350, 190, 260, 155}, "Doubly Linked List", "images/dll_menu.png"};
  MenuItem cll = MenuItem{
      {673, 190, 260, 155}, "Circular Linked List", "images/cll_menu.png"};
  MenuItem stack =
      MenuItem{{996, 190, 260, 155}, "Stack", "images/stack_menu.png"};
  MenuItem queue =
      MenuItem{{178, 425, 260, 155}, "Queue", "images/queue_menu.png"};
  MenuItem sa =
      MenuItem{{510, 425, 260, 155}, "Static Array", "images/sa_menu.png"};
  MenuItem da =
      MenuItem{{845, 425, 260, 155}, "Dynamic Array", "images/sa_menu.png"};
  if (sll.render())
    setCurScreen(SLL_SCREEN);
  if (dll.render())
    setCurScreen(DLL_SCREEN);
  if (cll.render())
    setCurScreen(CLL_SCREEN);
  if (stack.render())
    setCurScreen(ST_SCREEN);
  if (queue.render())
    setCurScreen(QU_SCREEN);
  if (sa.render())
    setCurScreen(SA_SCREEN);
  if (da.render())
    setCurScreen(DA_SCREEN);
}

void drawSettingButton() {
  if (GuiButton({1173, 30, 50, 50}, GuiIconText(140, ""), true)) {
    curScreen = SETTING_SCREEN;
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
  Queue qu;
  SettingScreen setting;
  StaticArray sa;
  DynamicArray da;
  ll.createRandomList(), dll.createRandomList(), cll.createRandomList(),
      st.createRandomList(), qu.createRandomList();
  GuiLoadStyle("gui/styles.rgs");
  GuiLoadIcons("gui/iconset.rgi", NULL);
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
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textColor));
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, ColorToInt(textColor));
    GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, ColorToInt(textColor));
    GuiSetFont(Settings::font_regular);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    switch (curScreen) {
      case HOME_SCREEN:
        drawMenu();
        drawSettingButton();
        break;
      case SLL_SCREEN:
        ll.render();
        break;
      case DLL_SCREEN:
        dll.render();
        break;
      case CLL_SCREEN:
        cll.render();
        break;
      case ST_SCREEN:
        st.render();
        break;
      case QU_SCREEN:
        qu.render();
        break;
      case SA_SCREEN:
        sa.render();
        break;
      case DA_SCREEN:
        da.render();
        break;
      case SETTING_SCREEN:
        setting.render();
        break;
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
