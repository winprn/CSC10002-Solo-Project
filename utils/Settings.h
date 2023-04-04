#ifndef SETTINGS_H
#define SETTINGS_H

#include "../lib/raylib.h"
#include "../lib/gui_file_dialog.h"

namespace Settings {
    extern Font font_regular, font_bold;
    extern float BASE_X, BASE_Y;
    extern GuiFileDialogState fileDialogState;
}

#endif