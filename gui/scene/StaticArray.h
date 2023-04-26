#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "../components/ArrayGuiNode.h"
#include <vector>

using namespace std;

class StaticArray {
  const int maxSize = 25;
  int n, val, pos, currentIndex = -1;
  bool selected[30] = {false};

 public:
  vector<ArrayGuiNode> nodes;
  StaticArray() {
    nodes.reserve(maxSize);
    n = 5 + rand() % (maxSize - 10);
    for (int i = 0; i < maxSize; i++) {
      nodes.push_back(ArrayGuiNode());
    }
    for (int i = 0; i < n; i++) {
      nodes[i].setHasValue(true);
    }
    for (int i = 0; i < nodes.capacity(); i++) {
      nodes[i].setVal(0);
      nodes[i].setCurPos({BASE_X + 42 * i, BASE_Y});
    }
  }

  void render() {
    if (GuiButton({BASE_X, BASE_Y + 100, 100, 40}, "Add")) {
      val = rand() % 100;
      CustomLog(LOG_INFO, TextFormat("Adding %d at %d", val, pos), 0);
      add(currentIndex);
    }
    for (int i = 0; i < n; i++) {
      nodes[i].setHasValue(true);
      if (nodes[i].getIsClicked()) {
        bool tmp = selected[i];
        memset(selected, false, sizeof(selected));
        selected[i] = !tmp;
        if (!selected[i])
          currentIndex = -1;
      }
      if (selected[i]) {
        nodes[i].setIsSelected(true);
        currentIndex = i;
      } else
        nodes[i].setIsSelected(false);
    }
    for (int i = 0; i < nodes.capacity(); i++) {
      nodes[i].render();
    }
  }

  void add(int pos) {
    if (n == maxSize) {
      return;
    }
    n++;
    if (pos == n) {
      nodes[pos].setVal(val);
    } else {
      for (int i = n; i > pos; i--) {
        nodes[i].setVal(nodes[i - 1].val);
      }
      nodes[pos].setVal(val);
    }
  }
};

#endif