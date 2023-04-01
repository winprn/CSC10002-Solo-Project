#include "Settings.h"

Font Settings::font_regular = {0};
Font Settings::font_bold = {0};
float Settings::BASE_X = 110;
float Settings::BASE_Y = 135;
GuiFileDialogState Settings::fileDialogState = InitGuiFileDialog(GetWorkingDirectory());