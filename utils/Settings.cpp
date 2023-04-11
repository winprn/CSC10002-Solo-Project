#include "Settings.h"

Font Settings::font_regular = {0};
Font Settings::font_bold = {0};
float Settings::BASE_X = 110;
float Settings::BASE_Y = 135;
GuiFileDialogState Settings::fileDialogState =
    InitGuiFileDialog(GetWorkingDirectory());
Color Settings::primaryColor = WHITE;
Color Settings::secondaryColor = Color({164, 144, 124, 255});
Color Settings::accentColor = Color({180, 210, 115, 255});
Color Settings::backgroundColor = Color({39, 40, 34, 255});
Color Settings::textColor = WHITE;
int Settings::curScreen = 0;
