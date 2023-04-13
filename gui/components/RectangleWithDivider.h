#ifndef RECTANGLE_WITH_DIVIDER
#define RECTANGLE_WITH_DIVIDER

#include "../../lib/raylib.h"
#include "Rectangle.h"

class RectangleWithDivider : public RectangleBase {
  float dividerX, dividerY;
  Color color = BLACK;

 public:
  RectangleWithDivider(Vector2 startPos, int w, int h)
      : RectangleBase(startPos, w, h), dividerX{startPos.x + 2 * width / 3},
        dividerY{startPos.y} {}

  void render() {
    RectangleBase::render();
    DrawLineEx((Vector2){dividerX, dividerY},
               (Vector2){dividerX, dividerY + height}, 2.0, color);
  }
};

#endif