#include "SingleLL.h"
#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../utils/Log.h"
#include "../components/GuiNode.h"
#include "../components/InputBox.h"

#include <string>
using namespace std;

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
  if (pos)
    search();
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  newNode->guiNode = GuiNode({(float)(50 * pos), 80});
  newNode->guiNode.setVal(val);

  if (pos == 0) {
    newNode->next = head;
    head = newNode;
    if (getSize() == 1)
      head->guiNode.setIsLast(true);
  } else if (pos == getSize()) {
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      head->guiNode.setIsLast(true);
    } else {
      tail->next = newNode;
      tail->guiNode.setIsLast(false);
      tail = newNode;
      tail->guiNode.setIsLast(true);
      tail->guiNode.setNewOpacity(0);
    }
  } else {
    int idx = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
      if (idx + 1 == pos) {
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
      if (DrawInputBox({150, 220, 100, 50}, "Add to first", input,
                       enableInput)) {
        add(input, 0);
      }
      if (DrawInputBox({300, 220, 100, 50}, "Add to last", input,
                       enableInput2)) {
        add(input, getSize());
      }
      break;
    case 1:
      if (GuiButton({100, 220, 150, 50}, "Delete head")) {
        remove(0);
      }
      if (GuiButton({300, 220, 150, 50}, "Delete tail")) {
        remove(getSize() - 1);
      }
      if (DrawInputBox({500, 220, 150, 50}, "Input index to delete", input,
                       enableInput)) {
        remove(input);
      }
      break;
    case 2:
      if (DrawInputBox({500, 220, 150, 50}, "Input value to search", input,
                       enableInput)) {
        searchDone = false;
        search(input);
      }
      break;

    default:
      break;
  }
  if (GuiButton({0, 0, 150, 50}, "highlight head")) {
    head->guiNode.setNewHighlight();
    CustomLog(LOG_INFO, TextFormat("%d", head->guiNode.getIsDone()), 0);
  }

  active = GuiComboBox((Rectangle){150, 150, 120, 50}, options, active);
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (cur->guiNode.getIsDone() && !animDone) {
      if (cur->next != nullptr) {
        if (cur->next->val == input) {
          cur->next->guiNode.setNewHighlight(2);
          animDone = true;
        } else
          cur->next->guiNode.setNewHighlight();
      } else {
        animDone = true;
      }
      if (cur->val != input) {
        cur->guiNode.setIsDone(false);
      }
    }
    cur->guiNode.setNewPos({(float)(50 + 130 * idx), 50});
  }

  if (animDone) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
      cur->guiNode.setNewOpacity(1);
    }
  }
}

void SingleLL::getRandom() {
  // removeAll();
  int n = 1;
  for (int i = 0; i < n; i++) {
    add(rand() % 20, 0);
  }
}

void SingleLL::remove(int id) {
  int idx = 0;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (idx == id) {
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

void SingleLL::search(int val) {
  CustomLog(LOG_DEBUG, "inside search", 0);
  if (head == nullptr)
    return;
  animDone = false;
  head->guiNode.setNewHighlight();
}