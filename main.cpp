#include "Function.h"
#include "gui/components/GuiNode.h"
#include "gui/components/Arrow.h"
#include "gui/scene/SingleLL.h"
#include "gui/scene/DoublyLL.h"
#include "lib/raygui.h"
#include "lib/raylib.h"
#include "utils/Log.h"
#include "utils/Settings.h"
#include <bits/stdc++.h>

using namespace std;

bool drawRectangleMenu(Rectangle rect, char *text, char *imgPath) {
  Image img = LoadImage(imgPath);
  // read image from file and draw it
  DrawRectangleRounded(rect, 0.05, 20, Color({233, 236, 239, 255}));
  Texture2D texture = LoadTextureFromImage(img);
  DrawTexture(texture, rect.x, rect.y, WHITE);

  DrawTextEx(Settings::font, text, {rect.x + 84, rect.y + 164}, 20, 1, Color({0, 0, 0, 255}));
  // ImageDrawRectangle(&img, rect.x, rect.y, rect.width, rect.height, Color({233, 236, 239, 255})); 
  if (IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), rect)) return true;

  return false;
}

void drawMenu(int &screen) {
  DrawTextEx(Settings::font, "Welcome to VisuAlgo - cloned by @winprn", {266, 32}, 40, 1, Color({233, 236, 239, 255}));
  DrawTextEx(Settings::font, "Ly Dinh Minh Man - 22127255 - 22CLC06", {424, 98}, 24, 1, Color({233, 236, 239, 255}));
  if (drawRectangleMenu({56, 191, 330, 200}, "Singly Linked List", "images/sll_menu.png")) {
    screen = 1;
  }
  if (drawRectangleMenu({475, 191, 330, 200}, "Doubly Linked List", "images/dll_menu.png")) {
    screen = 1;
  }
  if (drawRectangleMenu({895, 191, 330, 200}, "Circular Linked List", "images/cll_menu.png")) {
    screen = 1;
  }
}

int main() {
  SetTraceLogCallback(CustomLog);
  InitWindow(1280, 720, "testss");
  SetTargetFPS(60);
  SingleLL ll;
  DoublyLL dll;
  // ll.getRandom();
  ll.add(10, 1);
  GuiLoadStyle("gui/styles.rgs");
  GuiLoadIcons("gui/iconset.rgi", NULL);
  Arrow arr({50, 300}, {100, 360});
  bool ok = 0;
  CustomLog(LOG_DEBUG, TextFormat("%d", ll.getHead()), 0);
  // float angle = 30;
  Settings::font = LoadFontEx("gui/Roboto-Regular.ttf", 100, NULL, 0);
  int screen = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Color({52, 58, 64, 255}));

    switch (screen) {
      case 0:
        drawMenu(screen);
        break;
      case 1:
        ll.render();
        break;
      case 2:
        dll.render();
        break;
    }
    // Vector2 curPos{50, 500};
    // DrawTriangle({curPos.x + 130, curPos.y + 25}, {curPos.x + 120 + 20 * cos(PI/4) * tan(angle * PI / 180), curPos.y + 15}, {curPos.x + 120, curPos.y + 35 - 20 * cos(PI/4) * tan(angle * PI / 180)}, Fade(BLACK, 1.0));
    // angle -= 0.5;
    // if (angle < 0) {
    //   angle = 0;
    // }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
