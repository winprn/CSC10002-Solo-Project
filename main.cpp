#include <bits/stdc++.h>
#include "lib/raylib.h"
#include "lib/raygui.h"
#include "Function.h"
#include "gui/components/GuiNode.h"
#include "gui/scene/SingleLL.h"

using namespace std;

void CustomLog(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

int main()
{
    SetTraceLogCallback(CustomLog);
    InitWindow(1280, 720, "testss");
    
    SetTargetFPS(60);
    SingleLL ll;
    ll.getRandom();
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
