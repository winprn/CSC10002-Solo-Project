#include "DoublyLL.h"
#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../lib/gui_file_dialog.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"
#include "../components/GuiNode.h"
#include "../components/InputBox.h"

#include <string>
using namespace std;
using namespace Settings;

void DoublyLL::render() {
  ClearBackground(RAYWHITE);
  int idx = 0;
  // CustomLog(LOG_INFO, "here", 0);
  removeFromLL();
  DrawTextEx(font, "Singly Linked List", {501, 31}, 40, 1, BLACK);

  if (GuiButton({100, 415, 100, 40}, "Create")) {
    reset();
    showCreateButtons = true;
  }
  if (GuiButton({100, 475, 100, 40}, "Add")) {
    reset();
    showAddButtons = true;
  }
  if (GuiButton({100, 535, 100, 40}, "Delete")) {
    reset();
    showDeleteButtons = true;
  }
  if (GuiButton({100, 595, 100, 40}, "Search")) {
    reset();
    showSearchButtons = true;
  }
  if (GuiButton({100, 655, 100, 40}, "Update")) {
    reset();
    showUpdateButtons = true;
  }

  if (showCreateButtons) {
    if (GuiButton({280, 415, 100, 40}, "Random")) {
      createRandomList();
    }
    if (GuiButton({400, 415, 100, 40}, "From file")) {
      fileDialogState.windowActive = true;
    }
    if (fileDialogState.windowActive) GuiLock();
    GuiUnlock();
    if (fileDialogState.SelectFilePressed)
    {
      if (IsFileExtension(fileDialogState.fileNameText, ".txt"))
      {
        strcpy(filePath, fileDialogState.fileNameText);
        CustomLog(LOG_INFO, TextFormat("Selected file: %s", filePath), 0);
        addFromFile();
      }
      fileDialogState.SelectFilePressed = false;
    }
    GuiFileDialog(&fileDialogState);
  }
  if (showAddButtons) {
    if (GuiButton({280, 475, 100, 40}, "Add to head")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      showInputBox[0] = true;
    }
    if (showInputBox[0]) {
      if (DrawInputBox({280, 535, 60, 30}, "", input[0], value[0], enableInput[0], ICON_PLUS)) {
        index = 1;
        add(value[0], 1);
        showInputBox[0] = false;
        strcpy(input[0], "");
      }
    }
    if (GuiButton({400, 475, 100, 40}, "Add to tail")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      showInputBox[1] = true;
    }
    if (showInputBox[1]) {
      if (DrawInputBox({400, 535, 60, 30}, "", input[0], value[0], enableInput[0], ICON_PLUS)) {
        index = getSize() + 1;
        add(value[0], getSize() + 1);
        showInputBox[1] = false;
        strcpy(input[0], "");
      }
    }
    if (GuiButton({520, 475, 100, 40}, "Add to index")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      showInputBox[2] = true;
    }
    if (showInputBox[2]) {
      if (GuiTextBox({520, 535, 30, 30}, input[0], 10, enableInput[0]) && strlen(input[0])) {
        int id = atoi(input[0]);
        value[0] = id;
      }
      if (IsMouseButtonDown(0)) {
        if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, {520, 535, 30, 30})) {
          enableInput[0] = true;
        } else enableInput[0] = false;
      }
      if (GuiTextBox({555, 535, 30, 30}, input[1], 10, enableInput[1]) && strlen(input[1])) {
        int id = atoi(input[1]);
        value[1] = id;
      }
      if (IsMouseButtonDown(0)) {
        if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, {555, 535, 30, 30})) {
            enableInput[1] = true;
        } else enableInput[1] = false;
      }
      if (GuiButton({590, 535, 30, 30}, GuiIconText(ICON_PLUS, ""))) {
        index = value[0];
        add(value[1], value[0]);
        showInputBox[2] = false;
        strcpy(input[0], "");
        strcpy(input[1], "");
      }
    }
  }
  if (showDeleteButtons) {
    if (GuiButton({280, 535, 100, 40}, "Delete head")) {
      index = 1;
      remove(index);
    }
    if (GuiButton({400, 535, 100, 40}, "Delete tail")) {
      index = getSize();
      remove(index);
    }
    if (GuiButton({520, 535, 100, 40}, "Delete at index")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      showInputBox[0] = true;
    }
    if (showInputBox[0]) {
      if (DrawInputBox({520, 595, 60, 30}, "", input[0], value[0], enableInput[0], ICON_MINUS)) {
        index = value[0];
        remove(index);
        showInputBox[1] = false;
        strcpy(input[0], "");
      }
    }
  }
  if (showSearchButtons) {
    if(DrawInputBox({240, 595, 50, 30}, "", input[0], value[0], enableInput[0], ICON_LENS)) {
      index = value[0];
      isSearching = true;
      search(index);
      strcpy(input[0], "");
    }
  }
  if (showUpdateButtons) {
    // if(DrawInputBox({240, 655, 50, 30}, "", input[0], value[0], enableInput[0], ICON_REPEAT_FILL)) {
    //   memset(showInputBox, 0, sizeof(showInputBox));
    //   showInputBox[0] = true;
    // }
    if (GuiTextBox({240, 655, 30, 30}, input[0], 10, enableInput[0]) && strlen(input[0])) {
      int id = atoi(input[0]);
      value[0] = id;
    }
    if (IsMouseButtonDown(0)) {
      if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, {240, 655, 30, 30})) {
        enableInput[0] = true;
      } else enableInput[0] = false;
    }
    if (GuiTextBox({275, 655, 30, 30}, input[1], 10, enableInput[1]) && strlen(input[1])) {
      int id = atoi(input[1]);
      value[1] = id;
    }
    if (IsMouseButtonDown(0)) {
      if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, {275, 655, 30, 30})) {
          enableInput[1] = true;
      } else enableInput[1] = false;
    }
    if (GuiButton({310, 655, 30, 30}, GuiIconText(ICON_REPEAT_FILL, ""))) {
      index = value[0];
      newVal = value[1];
      // CustomLog(LOG_INFO, TextFormat("%d", newVal), 0);
      update();
      // add(value[1], value[0]);
      showInputBox[2] = false;
      strcpy(input[0], "");
      strcpy(input[1], "");
    }
  }

  // switch (active) {
  //   case 0:
  //     DrawInputBox({150, 220, 100, 50}, "Add to first", input[0], value[0],
  //                      enableInput[0]);
  //     DrawInputBox({300, 220, 100, 50}, "Add to last", input[1], value[1],
  //                      enableInput[1]);
  //     DrawInputBox({450, 220, 100, 50}, "Value", input[2], value[2],
  //                      enableInput[2]);
  //     DrawInputBox({600, 220, 100, 50}, "Index", input[3], value[3], enableInput[3]);

  //     // GuiSetStyle(DEFAULT, TEXT_SIZE, 20);  
  //     if (GuiButton({150, 300, 100, 50}, "Add") || GetKeyPressed() == KEY_ENTER) {
  //       if (value[0]) {
  //         index = 1;
  //         add(value[0], 1);
  //       }
  //       else if (value[1]) {
  //         index = getSize() + 1;
  //         add(value[1], getSize() + 1);
  //       }
  //       else if (value[2] && value[3]) {
  //         index = value[3];
  //         add(value[2], value[3]);
  //       }
  //       strcpy(input[0], "");
  //       strcpy(input[1], "");
  //       strcpy(input[2], "");
  //       strcpy(input[3], "");
  //       value[0] = value[1] = value[2] = value[3] = 0;
  //     }
  //     break;
  //   case 1:
  //     if (GuiButton({100, 220, 150, 50}, "Delete head")) {
  //       remove(1);
  //       isDeleting = true;
  //     }
  //     if (GuiButton({300, 220, 150, 50}, "Delete tail")) {
  //       remove(getSize());
  //       isDeleting = true;
  //     }
  //     if (DrawInputBox({500, 220, 150, 50}, "Input index to delete", input[0], value[0],
  //                      enableInput[0])) {
  //       remove(value[0]);
  //       isDeleting = true;
  //       strcpy(input[0], "");
  //       value[0] = 0;
  //     }
  //     break;
  //   case 2:
  //     if (DrawInputBox({500, 220, 150, 50}, "Input value to search", input[0], value[0],
  //                      enableInput[0])) {
  //       searchDone = false;
  //       search(value[0]);
  //       strcpy(input[0], "");
  //     }
  //     break;

  //   default:
  //     break;
  // }

  // active = GuiComboBox((Rectangle){150, 150, 120, 50}, options, active);
  idx = 1;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (cur != head) cur->guiNode.setIsHead(false);
    else cur->guiNode.setIsHead(true);
    cur->guiNode.render();
    if (cur->guiNode.getIsRemove()) continue;
    if (!cur->guiNode.getIsLast()) {
      cur->guiNode.setArrowNext({cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25}, {cur->next->guiNode.getCurPos().x, cur->next->guiNode.getCurPos().y + 25});
    }
    if (cur != head) {
        cur->guiNode.setArrowPrev({cur->next->guiNode.getCurPos().x, cur->next->guiNode.getCurPos().y + 25}, {cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25});
    }
    if (!animDone) {
      if (cur->guiNode.getIsDone()) {
        if (cur->next && !cur->next->guiNode.getHighlight() && !cur->next->guiNode.getIsDone()) {
          if (cur->next->val == value[0] || idx + 1 == index) {
            if (isUpdating) {
              cur->next->guiNode.setVal(newVal);
              cur->next->guiNode.setHighLightColor(GREEN);
              isUpdating = false;
            }
            if (isSearching) {
              cur->next->guiNode.setHighLightColor(GREEN);
              isSearching = false;
            }
            cur->next->guiNode.setNewHighlight(3);
            animDone = true;
          } else if (idx + 1 < index) cur->next->guiNode.setNewHighlight(1);
        } else if (!cur->next && cur->guiNode.getIsDone()) animDone = true;
      }
      // CustomLog(LOG_DEBUG, TextFormat("idx: %d, index: %d, isDone: %d", idx, index, head->guiNode.getIsDone()), 0);
      if (index == 1 && head->next && head->next->guiNode.getIsDone()) animDone = true;
      if (getSize() == 1) {
        if (isUpdating) {
          head->guiNode.setVal(newVal);
          head->val = newVal;
          isUpdating = false;
        }
        animDone = true;
      }
    }
    // if (cur->next != nullptr && cur->guiNode.getIsLast() && fabs(cur->next->guiNode.getCurPos().y - cur->guiNode.getCurPos().y) < 5) {
    //   cur->guiNode.setIsLast(false);
    // }
    if (idx != index || isUpdating || isSearching) {
      if (!cur->guiNode.getIsRemove()) cur->guiNode.setNewPos({(float)(50 + BASE_X * idx), BASE_Y});
    } else if (!cur->guiNode.getIsRemove()) {
      cur->guiNode.setNewPos({(float)(50 + BASE_X * idx), BASE_Y + 50});
    }
  }

  CustomLog(LOG_INFO, TextFormat("animDone = %d", animDone), 0);
  if (animDone) {
    idx = 1;
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
      if (cur->guiNode.getIsRemove()) continue;
      if (idx + 1 == index && cur->next) {
        cur->guiNode.setIsLast(false);
        cur->guiNode.setArrowNext({cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25}, {cur->next->guiNode.getCurPos().x, cur->next->guiNode.getCurPos().y + 25});
      } else if (idx == index || index == 1) {
        if (cur->next) {
          cur->guiNode.setIsLast(false);
          cur->guiNode.setArrowNext({cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25}, {cur->next->guiNode.getCurPos().x, cur->next->guiNode.getCurPos().y + 25});
        }
        index = -1;
      } else if (cur->next) {
        cur->guiNode.setIsLast(false);
        cur->guiNode.setArrowNext({cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25}, {cur->next->guiNode.getCurPos().x, cur->next->guiNode.getCurPos().y + 25});
      }
    }
    // if (randomSize) {
    //   if (index == -10 || tail->guiNode.getIsDone() || getSize() == 1) {
    //     index = getSize() + 1;
    //     add(rand() % 100, index);
    //     randomSize--;
    //   }
    // } else index = -10;
    // if (fileData != nullptr) {
    //   if (index == -10 || tail->guiNode.getIsDone()) {
    //     index = getSize() + 1;
    //     add(atoi(fileData), index);
    //     fileData = strtok(nullptr, ",");
    //   }
    // } else if (!randomSize && animDone) index = -10;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
      if (!cur->guiNode.getIsRemove()) cur->guiNode.setNewOpacity(1);
      cur->guiNode.setIsDone(false);
      if (cur->guiNode.getIsDone()) cur->guiNode.setHighLightColor(BLACK);
    }
  }
}

int DoublyLL::getSize() {
  int sz = 0;
  for (Node* cur = head; cur != nullptr; cur = cur->next) {
    sz++;
  }
  return sz;
}

int DoublyLL::getHead() {
  if (head == nullptr)
    return 123;
  return head->val;
}

bool DoublyLL::add(int val, int pos, bool hasAnimation) {
  if (getSize() >= 10)
    return false;
  // if (pos)
  //   // search();
  CustomLog(LOG_INFO, TextFormat("hasAnimation = %d", hasAnimation), 0);
  if (head && hasAnimation) {
    animate();
  }
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (pos > 1 && pos <= getSize()) newNode->guiNode = GuiNode({(float)(50 + BASE_X * (pos)), BASE_Y + 50});
  else newNode->guiNode = GuiNode({(float)(50 + BASE_X * pos), BASE_Y + 50});
  newNode->guiNode.setVal(val);
  newNode->guiNode.setNewOpacity(1);
  newNode->guiNode.setIsLast(true);

  if (pos == 1) {
    newNode->next = head;
    head = newNode;
    if (getSize() == 1) {
      head->guiNode.setIsLast(true);
      tail = newNode;
    }
    // CustomLog(LOG_ERROR, TextFormat("head is last: %d", head->guiNode.getIsLast()), 0);
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
        newNode->prev = tail;
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
        cur->guiNode.setIsLast(true);
        cur->guiNode.setArrowNext({0, 0}, {0, 0});
        newNode->next = cur->next;
        newNode->prev = cur;
        cur->next = newNode;
        break;
      }
    }
    // newNode->guiNode.setArrow({newNode->guiNode.getCurPos().x + 80, newNode->guiNode.getCurPos().y + 25}, {newNode->next->guiNode.getCurPos().x, newNode->next->guiNode.getCurPos().y + 25});
  }
  if (head) {
    head->guiNode.setIsHead(true);
  }
  if (tail != nullptr)
    tail->guiNode.setIsLast(true);
  return true;
}

void DoublyLL::getRandom() {
  randomSize = max(1, rand() % 11);
  while (randomSize--) {
    add(rand() % 100, getSize() + 1, false);
  }
}

void DoublyLL::remove(int id) {
  int idx = 1;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (idx == id) {
      // CustomLog(LOG_DEBUG, "found == tail", 0);
      cur->guiNode.setNewPos({(float)(50 + BASE_X * idx), BASE_Y + 50});
      cur->guiNode.setNewOpacity(0);
      cur->guiNode.setIsRemove(true);
    }
  }
}

void DoublyLL::removeAll() {
  while (head != nullptr) {
    Node *tmp = head;
    head = head->next;
    delete tmp;
  }
}

void DoublyLL::removeFromLL() {
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
        CustomLog(LOG_DEBUG, "found == tail", 0);
        CustomLog(LOG_DEBUG, TextFormat("%d", prev->val), 0);
        tail = prev;
        tail->guiNode.setIsLast(true);
        tail->guiNode.setArrowNext({0, 0}, {0, 0});
      }
      prev->next = found->next;
    }
    delete found;
    // render();
  }
}

void DoublyLL::animate() {
  if (head == nullptr)
    return;
  head->guiNode.setNewHighlight(1);
  animDone = false;
}

void DoublyLL::search(int val) {
  CustomLog(LOG_DEBUG, "inside search", 0);
  if (head == nullptr)
    return;
  head->guiNode.setNewHighlight();
  animDone = false;
}

void DoublyLL::reset() {
  showCreateButtons = false;
  showAddButtons = false;
  showDeleteButtons = false;
  showSearchButtons = false;
  showUpdateButtons = false;
  memset(showInputBox, 0, sizeof(showInputBox));
}

void DoublyLL::createRandomList() {
  removeAll();
  getRandom();
  setIsLast();
}

void DoublyLL::addFromFile() {
  removeAll();
  fileData = LoadFileText(filePath);
  strtok(fileData, ",");
  while (fileData != NULL) {
    add(atoi(fileData), getSize() + 1, false);
    fileData = strtok(NULL, ",");
  }
  setIsLast();
}

void DoublyLL::setIsLast() {
  for (Node* cur = head; cur != nullptr; cur = cur->next) {
    if (cur->next) {
      cur->guiNode.setIsLast(false);
    }
  }
}

void DoublyLL::update() {
  isUpdating = true;
  animate();
}