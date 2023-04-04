#ifndef HIGHLIGHT_RECTANGLE_H
#define HIGHLIGHT_RECTANGLE_H

#include "../../lib/raylib.h"
#include "../../utils/Log.h"

class HighlightRectangle {
 public:
  int pos = 0;
  float time = 0, curTime = 0;
  bool isDone = false, isAnimating = false;

  bool getIsDone() { return isDone; }

  int getPos() { return pos; }

  void render(Color tmp = ColorAlpha({65, 196, 100}, 0.4)) {
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
