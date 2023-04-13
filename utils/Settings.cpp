#include "Settings.h"

Font Settings::font_regular = {0};
Font Settings::font_bold = {0};
float Settings::BASE_X = 110;
float Settings::BASE_Y = 135;
GuiFileDialogState Settings::fileDialogState =
    InitGuiFileDialog(GetWorkingDirectory());
Color Settings::primaryColor = WHITE;
Color Settings::secondaryColor = Color({164, 144, 124, 255});
Color Settings::accentColor = Color({62, 137, 137, 255});
Color Settings::accentColor2 = Color({43, 96, 96, 255});
Color Settings::backgroundColor = Color({23, 25, 26, 255});
Color Settings::backgroundColor2 = Color({36, 37, 38, 255});
Color Settings::textColor = Color({228, 230, 235, 255});
int Settings::curScreen = 0;
bool Settings::colorUpdated = false;
