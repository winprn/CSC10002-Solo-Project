#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "../../lib/raylib.h"
#include "../../lib/raygui.h"
#include <string>

bool DrawInputBox(Rectangle rect, const char *title, char *input, int &value, bool &enableInput) {
    DrawText(title, rect.x, rect.y - 20, 20, BLACK);
    bool hasChanged = false;
    if (GuiTextBox(rect, input, 10, enableInput) && strlen(input)) {
        int id = atoi(input);
        value = id;
        hasChanged = true;
        // strcpy(input, "");
    }
    if (IsMouseButtonDown(0)) {
        if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, rect)) {
            enableInput = true;
        } else enableInput = false;
    }

    return hasChanged;
}

#endif