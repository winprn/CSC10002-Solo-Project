#ifndef HIGHLIGHT_RECTANGLE_H
#define HIGHLIGHT_RECTANGLE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"

using namespace Settings;

class HighlightRectangle {
 public:
  int pos = 0;
  float time = 0, curTime = 0;
  bool isDone = true, isAnimating = false;

  bool getIsDone() { return isDone; }

  int getPos() { return pos; }

  void render(Color tmp = ColorAlpha(accentColor, 0.4)) {
    if (!isDone) {
      DrawRectangle(895, 535 + 24 * pos, 385, 22, tmp);
      curTime += 0.016;
      if (curTime >= time) {
        isDone = true;
        isAnimating = false;
        curTime = 0;
      }
    }
  }

  void update(int index, float t) {
    pos = index;
    time = t;
    isDone = false;
    isAnimating = true;
  }
};

#endif
