#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../utils/Settings.h"
#include <string>

using namespace Settings;

bool DrawInputBox(Rectangle rect, const char* title, char* input, int& value,
                  bool& enableInput, int icon = 0);

#endif