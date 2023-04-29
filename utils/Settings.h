#ifndef SETTINGS_H
#define SETTINGS_H

#include "../lib/tinyfiledialogs.h"
#include "../lib/raylib.h"

namespace Settings {
extern Font font_regular, font_bold;
extern float BASE_X, BASE_Y;
extern Color primaryColor, secondaryColor, accentColor, accentColor2,
    backgroundColor, backgroundColor2, textColor;
extern int curScreen;
extern bool colorUpdated;
extern float animationSpeed;
}  // namespace Settings

#endif
