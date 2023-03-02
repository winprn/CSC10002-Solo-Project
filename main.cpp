#include <bits/stdc++.h>
#include "lib/raylib.h"
#include "lib/raygui.h"
#include "Function.h"
#include "gui/components/GuiNode.h"
#include "gui/scene/SingleLL.h"

using namespace std;

int main()
{
    InitWindow(1280, 720, "test");
    
    SetTargetFPS(60);
    GuiNode node((Vector2){100, 100});
    SingleLL ll;
    ll.getRandom();
    bool printed = false;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!printed) {
                // printf("Size: %s", ll.getSize());
                printed = true;
            }
            DrawText(ll.getSize(), 100, 100, 20, BLACK);
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
