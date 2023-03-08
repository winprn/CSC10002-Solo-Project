#include <bits/stdc++.h>
#include "lib/raylib.h"
#include "lib/raygui.h"
#include "Function.h"
#include "gui/components/GuiNode.h"
#include "gui/scene/SingleLL.h"
#include "utils/Log.h"

using namespace std;

int main()
{
    SetTraceLogCallback(CustomLog);
    InitWindow(1280, 720, "testss");
    
    SetTargetFPS(60);
    SingleLL ll;
    // ll.getRandom();
    ll.add(10, 0);
    GuiLoadStyle("gui/styles.rgs");
    CustomLog(LOG_DEBUG, TextFormat("%d", ll.getHead()), 0);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            ll.render();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
