#ifndef ARROW_H
#define ARROW_H

#include "../../lib/raylib.h"
#include "../../lib/raymath.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"

using namespace Settings;

class Arrow {
 public:
  Vector2 start, end;
  bool isCycle = false;
  Arrow() : start{0, 0}, end{0, 0} {}
  Arrow(Vector2 s, Vector2 e) : start{s}, end{e} {}

  Vector2 RotatePoint(Vector2 point, Vector2 origin, float angle) {
    float s = sin(angle * DEG2RAD);
    float c = cos(angle * DEG2RAD);

    // translate point back to origin:
    point.x -= origin.x;
    point.y -= origin.y;

    // rotate point
    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    // translate point back:
    point.x = xnew + origin.x;
    point.y = ynew + origin.y;

    return point;
  }

  void render() {
    // draw a line
    if (!isCycle)
      DrawLineEx(start, end, 2, textColor);
    else {
      DrawLineEx(start, {start.x + 20, start.y}, 2, textColor);
      DrawLineEx({start.x + 20, start.y}, {start.x + 20, start.y + 55}, 2,
                 textColor);
      DrawLineEx({start.x + 20, start.y + 55}, {end.x, end.y + 30}, 2,
                 textColor);
      DrawLineEx({end.x, end.y + 30}, end, 2, textColor);
    }

    // get the first point of the triangle, which is the end of the line
    Vector2 p1 = end;
    Vector2 tmp = {0, 0};
    if (!isCycle)
      tmp = Vector2MoveTowards(end, start, 10);
    else
      tmp = Vector2MoveTowards(end, {end.x, end.y + 10}, 10);
    double dist = Vector2Distance(tmp, p1);
    // CustomLog(LOG_INFO, TextFormat("%f", dist), 0);
    Vector2 p2 = RotatePoint(tmp, p1, 45);

    // get the third point of the triangle, which is symmetric to the second point through the given line
    Vector2 p3 = RotatePoint(p2, p1, -90);

    // CustomLog(LOG_INFO, TextFormat("%f %f", tmp.x, tmp.y), 0);
    // CustomLog(LOG_INFO, TextFormat("%f %f", p1.x, p1.y), 0);
    // CustomLog(LOG_INFO, TextFormat("%f %f", p2.x, p2.y), 0);
    // CustomLog(LOG_INFO, TextFormat("%f %f", p3.x, p3.y), 0);
    // draw the triangle
    DrawTriangle(p1, p2, p3, textColor);
  }

  void setIsCycle(bool cycle) { isCycle = cycle; }
};

#endif
