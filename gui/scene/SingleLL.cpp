#include "SingleLL.h"
#include "../../lib/raygui.h"
#include "../../lib/raylib.h"
#include "../../lib/tinyfiledialogs.h"
#include "../../utils/Log.h"
#include "../../utils/Settings.h"
#include "../components/GuiNode.h"
#include "../components/InputBox.h"

#include <chrono>
#include <string>
#include <thread>
using namespace std;
using namespace Settings;

void SingleLL::render() {
  ClearBackground(backgroundColor);
  int idx = 0;
  // CustomLog(LOG_INFO, "here", 0);
  removeFromLL();
  DrawTextEx(font_bold, "Singly Linked List", {501, 31}, 40, 1, WHITE);
  if (GuiButton({25, 35, 100, 40}, GuiIconText(118, "Back"))) {
    curScreen = 0;
  }

  DrawRectangleRounded({80, 335, 160, 310}, 0.12, 20, backgroundColor2);
  DrawRectangleRoundedLines({80, 335, 160, 310}, 0.12, 20, 2,
                            ColorAlpha(textColor, 0.6));

  if (GuiButton({115, 290, 30, 30}, GuiIconText(ICON_ARROW_LEFT_FILL, ""),
                true)) {
    if (animationSpeed > 0.5)
      animationSpeed -= 0.5;
  }
  DrawTextEx(font_bold, TextFormat("%.1f", animationSpeed), {150, 295}, 20, 1,
             textColor);
  if (GuiButton({180, 290, 30, 30}, GuiIconText(ICON_ARROW_RIGHT_FILL, ""),
                true)) {
    if (animationSpeed < 2)
      animationSpeed += 0.5;
  }

  if (GuiButton({110, 350, 100, 40}, "Create")) {
    reset();
    showCreateButtons = true;
  }
  if (GuiButton({110, 410, 100, 40}, "Add")) {
    reset();
    showAddButtons = true;
  }
  if (GuiButton({110, 470, 100, 40}, "Delete")) {
    reset();
    showDeleteButtons = true;
  }
  if (GuiButton({110, 530, 100, 40}, "Search")) {
    reset();
    showSearchButtons = true;
  }
  if (GuiButton({110, 590, 100, 40}, "Update")) {
    reset();
    showUpdateButtons = true;
  }

  if (showAddButtons) {
    if (GuiButton({280, 410, 100, 40}, "Add to head")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      memset(lineHighlight, 0, sizeof(lineHighlight));
      showInputBox[0] = true;
    }
    if (showInputBox[0]) {
      if (DrawInputBox({280, 470, 60, 30}, "", input[0], value[0],
                       enableInput[0], ICON_PLUS)) {
        resetBeforeAnimate();
        index = 1;
        isAddToHead = true;
        shouldMoveUp = false;
        add(value[0], 1);
        showInputBox[0] = false;
        strcpy(input[0], "");
      }
    }
    if (GuiButton({400, 410, 100, 40}, "Add to tail")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      memset(lineHighlight, 0, sizeof(lineHighlight));
      showInputBox[1] = true;
    }
    if (showInputBox[1]) {
      if (DrawInputBox({400, 470, 60, 30}, "", input[0], value[0],
                       enableInput[0], ICON_PLUS)) {
        resetBeforeAnimate();
        index = getSize() + 1;
        isAddToTail = true;
        isNodeNext = false;
        animDone = true;
        shouldMoveUp = false;
        add(value[0], getSize() + 1, 0);
        showInputBox[1] = false;
        strcpy(input[0], "");
      }
    }
    if (GuiButton({520, 410, 100, 40}, "Add to index")) {
      memset(showInputBox, 0, sizeof(showInputBox));
      showInputBox[2] = true;
    }
    if (showInputBox[2]) {
      if (DrawInputBox({520, 470, 60, 30}, "", input[0], value[0],
                       enableInput[0], ICON_PLUS)) {
        if (currentIndex == -1) {
          errStartTime = GetTime();
        } else {
          resetBeforeAnimate();
          index = currentIndex;
          isAddToIndex = true;
          shouldHighlight = false;
          shouldMoveUp = false;
          needUpdate = true;
          animDone = false;
          currentIndex = -1;
          memset(lineHighlight, 0, sizeof(lineHighlight));
          memset(selected, 0, sizeof(selected));
          add(value[0], index, 0);
          showInputBox[2] = false;
          strcpy(input[0], "");
        }
      }
    }
  }
  if (showDeleteButtons) {
    if (GuiButton({280, 470, 100, 40}, "Delete head")) {
      resetBeforeAnimate();
      index = 1;
      isRemoveHead = true;
      animDone = false;
      shouldHighlight = false;
      needUpdate = true;
      memset(lineHighlight, 0, sizeof(lineHighlight));
    }
    if (GuiButton({400, 470, 100, 40}, "Delete tail")) {
      resetBeforeAnimate();
      index = getSize();
      isDeleting = true;
      shouldHighlight = false;
      isRemoveTail = true;
      needUpdate = true;
      animDone = false;
      memset(lineHighlight, 0, sizeof(lineHighlight));
    }
    if (GuiButton({520, 470, 100, 40}, "Delete at index")) {
      if (currentIndex == -1) {
        errStartTime = GetTime();
      } else {
        resetBeforeAnimate();
        index = currentIndex;
        isRemoveIndex = true;
        shouldHighlight = false;
        needUpdate = true;
        animDone = false;
        currentIndex = -1;
        memset(lineHighlight, 0, sizeof(lineHighlight));
        memset(selected, 0, sizeof(selected));
        showInputBox[1] = false;
        strcpy(input[0], "");
      }
    }
  }
  if (showSearchButtons) {
    if (DrawInputBox({250, 530, 50, 30}, "", input[0], value[0], enableInput[0],
                     ICON_LENS)) {
      resetBeforeAnimate();
      index = value[0];
      isSearching = true;
      shouldHighlight = false;
      needUpdate = true;
      found = false;
      memset(lineHighlight, 0, sizeof(lineHighlight));
      search(index);
      strcpy(input[0], "");
    }
  }
  if (showUpdateButtons) {
    if (DrawInputBox({250, 590, 50, 30}, "", input[0], value[0], enableInput[0],
                     ICON_REPEAT_FILL)) {
      if (currentIndex == -1) {
        errStartTime = GetTime();
      } else {
        resetBeforeAnimate();
        index = currentIndex;
        newVal = value[0];
        isUpdating = true;
        shouldHighlight = false;
        needUpdate = true;
        animDone = false;
        currentIndex = -1;
        memset(showInputBox, 0, sizeof(showInputBox));
        memset(selected, 0, sizeof(selected));
        memset(lineHighlight, 0, sizeof(lineHighlight));
        strcpy(input[0], "");
        strcpy(input[1], "");
      }
    }
  }

  if (isSearching) {
    Image img = LoadImage("images/SLL/search.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isAddToHead) {
    Image img = LoadImage("images/SLL/add_head.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isAddToTail) {
    Image img = LoadImage("images/SLL/add_tail.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isAddToIndex) {
    Image img = LoadImage("images/SLL/add_index.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isRemoveHead) {
    Image img = LoadImage("images/SLL/remove_head.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isRemoveTail) {
    Image img = LoadImage("images/SLL/remove_tail.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isRemoveIndex) {
    Image img = LoadImage("images/SLL/remove_index.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (isUpdating) {
    Image img = LoadImage("images/SLL/update.png");
    // read image from file and draw it
    Texture2D texture = LoadTextureFromImage(img);
    DrawTexture(texture, 895, 490, WHITE);
  }
  if (!shouldHighlight && isSearching) {
    if (!lineHighlight[0]) {
      if (needUpdate) {
        rect.update(0, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[0] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[1]) {
      if (needUpdate) {
        rect.update(1, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[1] = true;
        needUpdate = true;
      }
    } else {
      shouldHighlight = true;
      head->guiNode.setNewHighlight();
      needUpdate = true;
      isCodeNext = true;
      isNodeNext = false;
    }
  }

  if (!shouldHighlight && (isAddToIndex || isUpdating)) {
    if (!lineHighlight[0]) {
      if (needUpdate) {
        rect.update(0, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[0] = true;
        needUpdate = true;
      }
    } else {
      CustomLog(LOG_INFO, "head is highlighting", 0);
      head->guiNode.setNewHighlight();
      shouldHighlight = true;
      isCodeNext = true;
      isNodeNext = false;
    }
  }
  if (!shouldHighlight && isRemoveHead) {
    if (!lineHighlight[0]) {
      if (needUpdate) {
        rect.update(0, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[0] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[1]) {
      if (needUpdate) {
        rect.update(1, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[1] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[2]) {
      if (needUpdate) {
        rect.update(2, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[2] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[3]) {
      if (needUpdate) {
        rect.update(3, 0.5);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[3] = true;
        needUpdate = true;
      }
    }
  }
  if (!shouldHighlight && (isRemoveTail || isRemoveIndex)) {
    if (!lineHighlight[0]) {
      if (needUpdate) {
        rect.update(0, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[0] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[1]) {
      if (needUpdate) {
        rect.update(1, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[1] = true;
        needUpdate = true;
      }
    } else {
      head->guiNode.setNewHighlight();
      shouldHighlight = true;
      isCodeNext = true;
      isNodeNext = false;
    }
  }
  idx = 1;
  rect.render();
  // CustomLog(LOG_INFO, TextFormat("shouldHighlight = %d", shouldHighlight), 0);
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (isAddToHead) {
      if (head->next) {
        head->next->guiNode.setIsHead(true);
        if (rect.getPos() == 1) {
          head->guiNode.setShouldRenderArrowNext(true);
        }
      }
    } else if (isRemoveHead) {
      if (rect.getPos() > 0)
        DrawTextEx(font_regular, "temp",
                   {head->guiNode.getCurPos().x + 10,
                    head->guiNode.getCurPos().y + 60},
                   20, 1, textColor);
      if (rect.getPos() > 1) {
        head->next->guiNode.setIsHead(true);
        head->guiNode.setIsHead(false);
      }
      if (rect.getPos() > 2) {
        isRemoveHead = false;
        remove(index);
        index = -1;
      }
    } else {
      if (cur != head)
        cur->guiNode.setIsHead(false);
      else
        cur->guiNode.setIsHead(true);
    }
    if (isAddToTail) {
      if (rect.getPos() == 1) {
        if (cur->next) {
          cur->guiNode.setIsLast(false);
        }
      }
      if (rect.getPos() == 2) {
        if (!cur->next)
          cur->guiNode.setIsLast(true);
      }
    }
    if (cur->guiNode.getIsClicked()) {
      bool tmp = selected[idx];
      memset(selected, false, sizeof(selected));
      selected[idx] = !tmp;
      if (!selected[idx])
        currentIndex = -1;
    }
    if (selected[idx]) {
      cur->guiNode.setIsSelected(true);
      currentIndex = idx;
    } else
      cur->guiNode.setIsSelected(false);
    cur->guiNode.render();
    if (cur->guiNode.getIsRemove())
      continue;
    if (cur->next && !cur->guiNode.getIsLast()) {
      cur->guiNode.setArrowNext(
          {cur->guiNode.getCurPos().x + 60, cur->guiNode.getCurPos().y + 25},
          {cur->next->guiNode.getCurPos().x,
           cur->next->guiNode.getCurPos().y + 25});
    }
    // CustomLog(LOG_DEBUG, TextFormat("%.2f", cur->guiNode.getProgress()), 0);
    if ((isSearching || isAddToIndex || isUpdating ||
         (isRemoveTail && cur->next != tail) ||
         (isRemoveIndex && idx + 1 != index)) &&
        cur->guiNode.getProgress() >= 0.5) {
      isCodeNext = true;
      isNodeNext = false;
    }
    if (!animDone) {
      if (isSearching && isCodeNext) {
        if (!lineHighlight[2]) {
          if (needUpdate) {
            // CustomLog(LOG_DEBUG, "updated line 2", 0);
            rect.update(2, 0.4);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[2] = true;
            lineHighlight[3] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        } else if (!lineHighlight[3]) {
          if (needUpdate) {
            rect.update(3, 0.6);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[3] = true;
            lineHighlight[2] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        }
      }
      if ((isAddToIndex || isUpdating) && isCodeNext) {
        if (!lineHighlight[1]) {
          if (needUpdate) {
            // CustomLog(LOG_DEBUG, "updated line 2", 0);
            rect.update(1, 0.4);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[1] = true;
            lineHighlight[2] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        } else if (!lineHighlight[2]) {
          if (needUpdate) {
            rect.update(2, 0.6);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[2] = true;
            lineHighlight[1] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        }
      }
      if ((isRemoveTail || isRemoveIndex) && isCodeNext) {
        if (!lineHighlight[2]) {
          if (needUpdate) {
            rect.update(2, 0.4);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[2] = true;
            lineHighlight[3] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        } else if (!lineHighlight[3]) {
          if (needUpdate) {
            rect.update(3, 0.6);
            needUpdate = false;
          }
          if (rect.getIsDone()) {
            lineHighlight[3] = true;
            lineHighlight[2] = false;
            needUpdate = true;
            isNodeNext = true;
            isCodeNext = false;
          }
        }
      }
      if (cur->guiNode.getIsDone() && shouldHighlight) {
        if (isNodeNext) {
          if (cur->next && !cur->next->guiNode.getHighlight() &&
              !cur->next->guiNode.getIsDone()) {
            if ((isSearching && cur->next->val == value[0]) ||
                idx + 1 == index) {
              if (isSearching) {
                cur->next->guiNode.setHighLightColor(accentColor);
              }
              if (!isRemoveTail && !isRemoveIndex)
                cur->next->guiNode.setNewHighlight(2);
              found = true;
              animDone = true;
            } else if (idx + 1 < index) {
              cur->next->guiNode.setNewHighlight(1);
            }
          } else if (!cur->next && cur->guiNode.getIsDone())
            animDone = true;
        }
        // CustomLog(LOG_DEBUG, TextFormat("idx: %d, index: %d, isDone: %d", idx, index, head->guiNode.getIsDone()), 0);
        if (index == 1 && head->next && head->next->guiNode.getIsDone())
          animDone = true;
        if (getSize() == 1) {
          if (isUpdating) {
            head->guiNode.setVal(newVal);
            head->val = newVal;
            isUpdating = false;
          }
          animDone = true;
        }
      }
    }
    // if (cur->next != nullptr && cur->guiNode.getIsLast() && fabs(cur->next->guiNode.getCurPos().y - cur->guiNode.getCurPos().y) < 5) {
    //   cur->guiNode.setIsLast(false);
    // }
    if (cur->guiNode.getIsRemove() || (!shouldMoveUp && idx == index) ||
        (!shouldMoveUp &&
         ((cur == tail && isAddToTail) || (cur == head && isAddToHead)))) {
      cur->guiNode.setNewPos({(float)(BASE_X * idx), BASE_Y + 50});
    } else
      cur->guiNode.setNewPos({(float)(BASE_X * idx), BASE_Y});
  }
  if (isAddToHead || isAddToTail) {
    if (!lineHighlight[0]) {
      if (needUpdate) {
        rect.update(0, 0.3);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[0] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[1]) {
      if (needUpdate) {
        rect.update(1, 0.5);
        needUpdate = false;
        shouldMoveUp = true;
      }
      if (rect.getIsDone()) {
        lineHighlight[1] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[2]) {
      if (needUpdate) {
        rect.update(2, 0.3);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[2] = true;
        needUpdate = true;
        isAddToHead = false;
        isAddToTail = false;
      }
    }
  }
  if (isSearching && animDone) {
    if (found) {
      if (needUpdate) {
        rect.update(6, 2);
        needUpdate = false;
      }
      if (rect.getIsDone())
        isSearching = false;
    } else {
      if (!lineHighlight[4]) {
        if (needUpdate) {
          rect.update(4, 1);
          needUpdate = false;
        }
        if (rect.getIsDone()) {
          lineHighlight[4] = true;
          needUpdate = true;
        }
      } else if (!lineHighlight[5]) {
        if (needUpdate) {
          rect.update(5, 1);
          needUpdate = false;
        }
        if (rect.getIsDone()) {
          lineHighlight[5] = true;
          needUpdate = true;
        }
      } else if (rect.getIsDone())
        isSearching = false;
    }
  }

  if (isAddToIndex && animDone) {
    if (!lineHighlight[3]) {
      if (needUpdate) {
        rect.update(3, 0.5);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[3] = true;
        Node* tmp = head;
        int idx = 1;
        for (; tmp != nullptr && idx != index; tmp = tmp->next, idx++)
          ;
        needUpdate = true;
        tmp->guiNode.setShouldRenderArrowNext(true);
      }
    } else if (!lineHighlight[4]) {
      if (needUpdate) {
        rect.update(4, 0.5);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        Node* tmp = head;
        int idx = 1;
        for (; tmp != nullptr && idx + 1 != index; tmp = tmp->next, idx++)
          ;
        needUpdate = true;
        tmp->guiNode.setShouldRenderArrowNext(true);
        isAddToIndex = false;
      }
    }
  }

  if (isRemoveTail && animDone) {
    if (!lineHighlight[4]) {
      if (needUpdate) {
        rect.update(4, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[4] = true;
        Node* tmp = head;
        for (; tmp && tmp->next != tail; tmp = tmp->next)
          ;
        // CustomLog(LOG_INFO,
        //           TextFormat("tail = %d, tmp = %d, tmp->next = %d", tail, tmp,
        //                      tmp->next),
        //           0);
        tmp->guiNode.setShouldRenderArrowNext(false);
        tail->guiNode.setIsLast(false);
        lineHighlight[4] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[5]) {
      if (needUpdate) {
        rect.update(5, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[5] = true;
        Node* tmp = head;
        for (; tmp->next != tail; tmp = tmp->next)
          ;
        tmp->guiNode.setIsLast(true);
        lineHighlight[5] = true;
        needUpdate = true;
      }
    } else if (rect.getIsDone()) {
      remove(index);
    }
  }

  if (isRemoveIndex && animDone) {
    if (!lineHighlight[4]) {
      if (needUpdate) {
        rect.update(4, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[4] = true;
        Node* tmp = head;
        int idx = 1;
        for (; tmp && idx + 1 != index; tmp = tmp->next, idx++)
          ;
        tmp->guiNode.setText("pre");
        tmp->next->next->guiNode.setText("aft");
        lineHighlight[4] = true;
        needUpdate = true;
      }
    } else if (!lineHighlight[5]) {
      if (needUpdate) {
        rect.update(5, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        lineHighlight[5] = true;
        lineHighlight[5] = true;
        needUpdate = true;
      }
    } else if (rect.getIsDone()) {
      Node* tmp = head;
      int idx = 1;
      for (; tmp && idx + 1 != index; tmp = tmp->next, idx++)
        ;
      tmp->guiNode.setText("");
      tmp->next->next->guiNode.setText("");
      remove(index);
    }
  }

  if (isUpdating && animDone) {
    if (!lineHighlight[3]) {
      if (needUpdate) {
        rect.update(3, 1);
        needUpdate = false;
      }
      if (rect.getIsDone()) {
        Node* tmp = head;
        int idx = 1;
        for (; tmp && idx != index; tmp = tmp->next, idx++)
          ;
        tmp->guiNode.setVal(newVal);
        tmp->val = newVal;
        isUpdating = false;
      }
    }
  }

  if (animDone) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
      if (cur->next) {
        if (cur->next == tail && isAddToTail) {
        } else if (!isAddToIndex) {
          if (isRemoveTail && cur->next == tail) {
            DrawText("cur", cur->guiNode.getCurPos().x + 10,
                     cur->guiNode.getCurPos().y + 60, 20, textColor);
          } else {
            cur->guiNode.setIsLast(false);
            cur->guiNode.setShouldRenderArrowNext(true);
          }
        }
      }
      if (cur->guiNode.getIsDone())
        cur->guiNode.setHighLightColor();
      cur->guiNode.setIsDone(false);
    }
    if (!isAddToIndex && !isRemoveTail && !isRemoveIndex && !isUpdating)
      index = -1;
  }
  if (showCreateButtons) {
    if (GuiButton({280, 350, 100, 40}, "Random")) {
      createRandomList();
    }
    if (GuiButton({400, 350, 100, 40}, "From file")) {
      const char* fileName =
          tinyfd_openFileDialog("Choose a file", "", 0, nullptr, nullptr, 0);
      if (fileName != nullptr) {
        addFromFile(fileName);
      }
    }
  }

  if (GetTime() - errStartTime < 2 && errStartTime > 0) {
    DrawTextEx(font_bold, "Please select a node", {50, 250}, 22, 1, textColor);
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

bool SingleLL::add(int val, int pos, bool hasAnimation) {
  if (getSize() >= 10)
    return false;
  // if (pos)
  //   // search();
  if (head && hasAnimation) {
    animate();
  }
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  newNode->guiNode = GuiNode({(float)(BASE_X * pos), BASE_Y + 50});
  newNode->guiNode.setVal(val);
  newNode->guiNode.setNewOpacity(1);
  newNode->guiNode.setShouldRenderArrowNext(false);

  if (pos == 1) {
    newNode->next = head;
    head = newNode;
    if (getSize() == 1) {
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
        // tail->guiNode.setIsRotateArrow(true);
        tail = newNode;
        tail->guiNode.setIsLast(true);
      }
    }
  } else {
    int idx = 1;
    for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
      if (idx + 1 == pos) {
        cur->guiNode.setShouldRenderArrowNext(false);
        newNode->next = cur->next;
        cur->next = newNode;
        break;
      }
    }
    // newNode->guiNode.setArrowNext({newNode->guiNode.getCurPos().x + 80, newNode->guiNode.getCurPos().y + 25}, {newNode->next->guiNode.getCurPos().x, newNode->next->guiNode.getCurPos().y + 25});
  }
  if (tail != nullptr)
    tail->guiNode.setIsLast(true);
  return true;
}

void SingleLL::getRandom() {
  randomSize = max(1, rand() % 11);
  while (randomSize--) {
    add(rand() % 100, getSize() + 1, false);
  }
}

void SingleLL::remove(int id) {
  int idx = 1;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (idx == id) {
      CustomLog(LOG_DEBUG, "founded", 0);
      cur->guiNode.setNewPos({(float)(BASE_X * idx), BASE_Y + 50});
      cur->guiNode.setNewOpacity(0);
      cur->guiNode.setIsRemove(true);
    }
  }
}

void SingleLL::removeAll() {
  while (head != nullptr) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
  }
}

void SingleLL::removeFromLL() {
  Node* found = nullptr;
  int idx = 0;
  for (Node* cur = head; cur != nullptr; cur = cur->next, idx++) {
    if (cur->guiNode.getIsRemove() && cur->guiNode.getOpacity() < 0.03) {
      found = cur;
      break;
    }
  }

  if (found != nullptr) {
    CustomLog(LOG_INFO, "founded", 0);
    if (found == head) {
      head = head->next;
      isRemoveHead = false;
    } else {
      Node* prev = head;
      while (prev->next != found) {
        prev = prev->next;
      }
      if (found == tail) {
        CustomLog(LOG_DEBUG, "found == tail", 0);
        CustomLog(LOG_DEBUG, TextFormat("%d", prev->val), 0);
        isRemoveTail = false;
        tail = prev;
        tail->guiNode.setIsLast(true);
        tail->guiNode.setArrowNext({0, 0}, {0, 0});
      }
      isRemoveIndex = false;
      prev->next = found->next;
    }
    delete found;
  }
}

void SingleLL::animate() {
  if (head == nullptr)
    return;
  head->guiNode.setNewHighlight(1);
  animDone = false;
}

void SingleLL::search(int val) {
  CustomLog(LOG_DEBUG, "inside search", 0);
  if (head == nullptr)
    return;
  // head->guiNode.setNewHighlight();
  animDone = false;
}

void SingleLL::reset() {
  showCreateButtons = false;
  showAddButtons = false;
  showDeleteButtons = false;
  showSearchButtons = false;
  showUpdateButtons = false;
  memset(showInputBox, 0, sizeof(showInputBox));
}

void SingleLL::createRandomList() {
  removeAll();
  getRandom();
  setIsLast();
}

void SingleLL::addFromFile(const char* filePath) {
  removeAll();
  fileData = LoadFileText(filePath);
  strtok(fileData, ",");
  while (fileData != NULL) {
    add(atoi(fileData), getSize() + 1, false);
    fileData = strtok(NULL, ",");
  }
  setIsLast();
}

void SingleLL::setIsLast() {
  for (Node* cur = head; cur != nullptr; cur = cur->next) {
    if (cur->next) {
      cur->guiNode.setIsLast(false);
      cur->guiNode.setShouldRenderArrowNext(true);
    }
  }
}

void SingleLL::update() {
  isUpdating = true;
  animate();
}

void SingleLL::resetBeforeAnimate() {
  searchDone = true, animDone = true, isAdding = false, isDeleting = false,
  isUpdating = false, isSearching = false, shouldHighlight = true,
  shouldMoveUp = true, needUpdate = true, found = false, isAddToHead = false,
  isAddToTail = false, isAddToIndex = false, isRemoveHead = false,
  isRemoveTail = false, isRemoveIndex = false, isNodeNext = false,
  isCodeNext = false;
}