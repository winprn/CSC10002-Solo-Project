#ifndef SETTINGS_H
#define SETTINGS_H

#include "../lib/gui_file_dialog.h"
#include "../lib/raylib.h"

namespace Settings {
extern Font font_regular, font_bold;
extern float BASE_X, BASE_Y;
extern GuiFileDialogState fileDialogState;
extern Color primaryColor, secondaryColor, accentColor, backgroundColor,
    textColor;
}  // namespace Settings

#endif
