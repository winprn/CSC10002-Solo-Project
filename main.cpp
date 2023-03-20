#include "Function.h"
#include "gui/components/GuiNode.h"
#include "gui/scene/SingleLL.h"
#include "lib/raygui.h"
#include "lib/raylib.h"
#include "utils/Log.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
  SetTraceLogCallback(CustomLog);
  InitWindow(1280, 720, "testss");

  SetTargetFPS(60);
  SingleLL ll;
  // ll.getRandom();
  ll.add(10, 1);
  GuiLoadStyle("gui/styles.rgs");
  CustomLog(LOG_DEBUG, TextFormat("%d", ll.getHead()), 0);
  // float angle = 30;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    ll.render();
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
