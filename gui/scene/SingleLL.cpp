#include "SingleLL.h"
#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../components/GuiNode.h"
#include "../components/InputBox.h"

#include <string>
using namespace std;

void SingleLL::render() {
  int idx = 0;
  removeFromLL();
  // if (GuiButton({100, 200, 100, 50}, "Delete")) {
  //     remove(0);
  // }
  // if (GuiButton({250, 200, 100, 50}, "New List")) {
  //     getRandom();
  // }
  // if (GuiTextBox({100, 300, 100, 50}, input, 10, true) && strlen(input)) {
  //     bool result = add(atoi(input));
  //     if (!result) {
  //         // CustomLog(LOG_DEBUG, "Cannot add more", 0);
  //     } else {
  //         // CustomLog(LOG_DEBUG, TextFormat("Added %d", atoi(s)), 0);
  //     }
  //     strcpy(input, "");
  // }

  switch (active) {
    case 0:
      DrawInputBox({150, 220, 100, 50}, "Add to first", input[0], value[0],
                       enableInput[0]);
      DrawInputBox({300, 220, 100, 50}, "Add to last", input[1], value[1],
                       enableInput[1]);
      DrawInputBox({450, 220, 100, 50}, "Value", input[2], value[2],
                       enableInput[2]);
      DrawInputBox({600, 220, 100, 50}, "Index", input[3], value[3], enableInput[3]);
        
      if (GuiButton({150, 300, 100, 50}, "Add") || GetKeyPressed() == KEY_ENTER) {
        if (value[0]) {
          index = 1;
          add(value[0], 1);
        }
        else if (value[1]) {
          index = getSize() + 1;
          add(value[1], getSize() + 1);
        }
        else if (value[2] && value[3]) {
          index = value[3];
          add(value[2], value[3]);
        }
        strcpy(input[0], "");
        strcpy(input[1], "");
        strcpy(input[2], "");
        strcpy(input[3], "");
        value[0] = value[1] = value[2] = value[3] = 0;
      }
      break;
    case 1:
      if (GuiButton({100, 220, 150, 50}, "Delete head")) {
        remove(1);
        isDeleting = true;
      }
      if (GuiButton({300, 220, 150, 50}, "Delete tail")) {
        remove(getSize());
        isDeleting = true;
      }
      if (DrawInputBox({500, 220, 150, 50}, "Input index to delete", input[0], value[0],
                       enableInput[0])) {
        remove(value[0]);
        isDeleting = true;
        strcpy(input[0], "");
        value[0] = 0;
      }
      break;
    case 2:
      if (DrawInputBox({500, 220, 150, 50}, "Input value to search", input[0], value[0],
                       enableInput[0])) {
        searchDone = false;
        search(value[0]);
        strcpy(input[0], "");
      }
      break;

    default:
      break;
  }
  if (GuiButton({0, 0, 150, 50}, "play animation")) {
    animate();
  }
  if (GuiButton({200, 0, 150, 50}, "rotate arrow")) {
    head->guiNode.setIsRotateArrow(true);
  }

  active = GuiComboBox((Rectangle){150, 150, 120, 50}, options, active);
  idx = 1;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (!animDone) {
      if (cur->guiNode.getIsDone()) {
        if (cur->next && !cur->next->guiNode.getHighlight() && !cur->next->guiNode.getIsDone()) {
          if (cur->next->val == value[0] || idx + 1 == index) {
            cur->next->guiNode.setNewHighlight(3);
            animDone = true;
          } else cur->next->guiNode.setNewHighlight(1);
        } else if (!cur->next && cur->guiNode.getIsDone()) animDone = true;
      }
    }
    // if (cur->next != nullptr && cur->guiNode.getIsLast() && fabs(cur->next->guiNode.getCurPos().y - cur->guiNode.getCurPos().y) < 5) {
    //   cur->guiNode.setIsLast(false);
    // }
    if (idx != index || index == 1) {
      if (!cur->guiNode.getIsRemove()) cur->guiNode.setNewPos({(float)(50 + 130 * idx), 50});
    } else {
      if (idx > 1 && idx <= getSize() - 1) cur->guiNode.setNewPos({(float)(50 + 130 * (idx)), 120});
      else cur->guiNode.setNewPos({(float)(50 + 130 * idx), 120});
    }
  }

  if (animDone) {
    idx = 1;
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
      if (idx + 1 == index) {
        cur->guiNode.setIsLast(false);
        cur->guiNode.setIsRotateArrow(true);
        if (!cur->guiNode.getIsLengthChanged()) index = -1;
      }
    }
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
      if (!cur->guiNode.getIsRemove()) cur->guiNode.setNewOpacity(1);
      cur->guiNode.setIsDone(false);
    }
  }
}

int SingleLL::getSize() {
  int sz = 0;
  for (Node* cur = head; cur != nullptr; cur = cur->next) {
    sz++;
  }
  return sz;
}

int SingleLL::getHead() {
  if (head == nullptr)
    return 123;
  return head->val;
}

bool SingleLL::add(int val, int pos) {
  if (getSize() >= 10)
    return false;
  // if (pos)
  //   // search();
  if (pos > 1) animate();
  CustomLog(LOG_DEBUG, TextFormat("pos = %d, getSize() = %d", pos, getSize()), 0);
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  if (pos > 1 && pos <= getSize()) newNode->guiNode = GuiNode({(float)(50 + 130 * (pos)), 120});
  else newNode->guiNode = GuiNode({(float)(50 + 130 * pos), 120});
  newNode->guiNode.setVal(val);
  newNode->guiNode.setNewOpacity(1);

  if (pos == 1) {
    newNode->next = head;
    head = newNode;
    if (getSize() == 1) {
      head->guiNode.setIsLast(true);
      tail = newNode;
    }
  } else if (pos > getSize()) {
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      head->guiNode.setIsLast(true);
    } else {
      if (tail == nullptr) {
        // CustomLog(LOG_ERROR, "hihihi", 0);
      } else {
        tail->next = newNode;
        // tail->guiNode.setIsRotateArrow(true);
        tail = newNode;
        tail->guiNode.setIsLast(true);
      }
    }
  } else {
    int idx = 1;
    for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
      if (idx + 1 == pos) {
        // cur->guiNode.setIsRotateArrow(true);
        newNode->next = cur->next;
        cur->next = newNode;
        break;
      }
    }
  }
  if (tail != nullptr)
    tail->guiNode.setIsLast(true);
  return true;
}

void SingleLL::getRandom() {
  // removeAll();
  int n = 1;
  for (int i = 0; i < n; i++) {
    add(rand() % 20, 0);
  }
}

void SingleLL::remove(int id) {
  int idx = 1;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (idx == id) {
      cur->guiNode.setNewPos({(float)(50 + 130 * idx), 120});
      cur->guiNode.setNewOpacity(0);
      cur->guiNode.setIsRemove(true);
    }
  }
}

void SingleLL::removeAll() {
  while (head != nullptr) {
    remove(0);
  }
}

void SingleLL::removeFromLL() {
  Node* found = nullptr;
  int idx = 0;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (cur->guiNode.getIsRemove() && cur->guiNode.getOpacity() < 0.0005) {
      found = cur;
      break;
    }
  }

  if (found != nullptr) {
    if (found == head) {
      head = head->next;
    } else {
      Node* prev = head;
      while (prev->next != found) {
        prev = prev->next;
      }
      if (found == tail) {
        tail = prev;
        tail->guiNode.setIsLast(true);
      }
      prev->next = found->next;
    }
    delete found;
    render();
  }
}

void SingleLL::animate() {
  head->guiNode.setNewHighlight(1);
  animDone = false;
}

void SingleLL::search(int val) {
  CustomLog(LOG_DEBUG, "inside search", 0);
  if (head == nullptr)
    return;
  head->guiNode.setNewHighlight();
  animDone = false;
}