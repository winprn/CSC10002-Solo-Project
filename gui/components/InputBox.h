#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "../../lib/raylib.h"
#include "../../lib/raygui.h"
#include <string>

bool DrawInputBox(Rectangle rect, const char *title, char *input, int &value, bool &enableInput, int icon = 0);

#endif