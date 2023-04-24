#ifndef CURVE_ARROW_H
#define CURVE_ARROW_H

#include "../../lib/raylib.h"
#include "../../lib/rlgl.h"
#include "../../utils/Settings.h"
#include <math.h>

using namespace Settings;

class CurveArrow {
  Vector2 center{610, 355};
  float radius = 200;

 public:
  float startAngle, endAngle;
  int segments = 20;
  Color color = textColor;

  CurveArrow() {}

  void render() {
    if (endAngle < startAngle) {
      // Swap values
      float tmp = startAngle;
      startAngle = endAngle;
      endAngle = tmp;
    }

    int minSegments = (int)ceilf((endAngle - startAngle) / 90);

    if (segments < minSegments) {
      // Calculate the maximum angle between segments based on the error rate (usually 0.5f)
      float th = acosf(2 * powf(1 - 0.5f / radius, 2) - 1);
      segments = (int)((endAngle - startAngle) * ceilf(2 * PI / th) / 360);

      if (segments <= 0)
        segments = minSegments;
    }

    float stepLength = (endAngle - startAngle) / (float)segments;
    float angle = startAngle;
    bool showCapLines = false;
    Rectangle texShapesRec = {0.0f, 0.0f, 1.0f, 1.0f};
    Texture2D texShapes = {1, 1, 1, 1, 7};

    rlBegin(RL_LINES);

    for (int i = 0; i < segments; i++) {
      rlColor4ub(color.r, color.g, color.b, color.a);

      rlVertex2f(center.x - sinf(DEG2RAD * angle) * radius,
                 center.y - cosf(DEG2RAD * angle) * radius);
      rlVertex2f(center.x - sinf(DEG2RAD * (angle + stepLength)) * radius,
                 center.y - cosf(DEG2RAD * (angle + stepLength)) * radius);

      angle += stepLength;
    }

    rlEnd();
  }

  void setStartAngle(float angle) { startAngle = angle; }

  void setEndAngle(float angle) { endAngle = angle; }
};

#endif