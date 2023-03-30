#include "Settings.h"

Font Settings::font = {0};
float Settings::BASE_X = 110;
float Settings::BASE_Y = 135;
GuiFileDialogState Settings::fileDialogState = InitGuiFileDialog(GetWorkingDirectory());