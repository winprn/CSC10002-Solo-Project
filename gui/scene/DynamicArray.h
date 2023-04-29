#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "../../DS/Vector.h"
#include "../components/ArrayGuiNode.h"
#include "../components/InputBox.h"
#include <vector>

using namespace std;

class DynamicArray {
  const int maxSize = 25;
  bool showCreateButtons = false, showAddButtons = false,
       showDeleteButtons = false, showSearchButtons = false,
       showUpdateButtons = false, showAllocateButtons = false,
       isAddToIndex = false, isPushBack = false, isDeleteIndex = false,
       isPopBack = false, isSearching = false, found = false, extend = false;
  int n, val, pos, currentIndex = -1, step = 0, prv = -1;
  float notiTime = 0, startTime = 0;
  bool selected[30] = {false}, showInputBox[10] = {false},
       enableInput[10] = {false};
  int value[10] = {0};
  char *notiMessage = new char[50], input[10][10] = {""}, filePath[512] = "";

 public:
  Vector<ArrayGuiNode> nodes;
  DynamicArray() { n = 0; }

  void render() {
    Vector2 textPos = MeasureTextEx(font_bold, "Static Array", 40, 1);
    DrawTextEx(font_bold, "Static Array", {(1280 - textPos.x) / 2, 20}, 40, 1,
               WHITE);
    if (GuiButton({25, 35, 100, 40}, GuiIconText(118, "Back"))) {
      curScreen = 0;
    }
    DrawRectangleRounded({80, 275, 160, 370}, 0.12, 20, backgroundColor2);
    DrawRectangleRoundedLines({80, 275, 160, 370}, 0.12, 20, 2,
                              ColorAlpha(textColor, 0.6));

    if (GuiButton({110, 290, 100, 40}, "Allocate")) {
      reset();
      showAllocateButtons = true;
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

    if (showAllocateButtons) {
      if (DrawInputBox({280, 290, 60, 30}, "", input[0], value[0],
                       enableInput[0], ICON_PLUS)) {
        // n = value[0];
        nodes = Vector<ArrayGuiNode>();
        nodes.reserve(value[0]);
        for (int i = 0; i < nodes.capacity(); i++)
          nodes.push_back(ArrayGuiNode());
        // for (int i = 0; i < n; i++) {
        //   nodes.push_back(ArrayGuiNode());
        //   nodes[i].setVal(0);
        //   nodes[i].setIndex(i);
        //   nodes[i].setHasValue(true);
        //   nodes[i].setCurPos({BASE_X + 42 * i, BASE_Y});
        // }
        // maxSize = nodes.capacity();
        // for (int i = 0; i < maxSize; i++) {
        //   nodes[i].setCurPos({BASE_X + 42 * i, BASE_Y});
        // }
        showAllocateButtons = false;
        strcpy(input[0], "");
      }
    }

    if (showAddButtons) {
      if (GuiButton({280, 410, 100, 40}, "Add to head")) {
        memset(showInputBox, 0, sizeof(showInputBox));
        showInputBox[0] = true;
      }
      if (showInputBox[0]) {
        if (DrawInputBox({280, 470, 60, 30}, "", input[0], value[0],
                         enableInput[0], ICON_PLUS)) {
          currentIndex = 0;
          val = value[0];
          isAddToIndex = true;
          extend = false;
          startTime = GetTime();
          step = 0;
          showInputBox[0] = false;
          strcpy(input[0], "");
        }
      }
      if (GuiButton({400, 410, 100, 40}, "Add to tail")) {
        memset(showInputBox, 0, sizeof(showInputBox));
        showInputBox[1] = true;
      }
      if (showInputBox[1]) {
        if (DrawInputBox({400, 470, 60, 30}, "", input[0], value[0],
                         enableInput[0], ICON_PLUS)) {
          currentIndex = n;
          val = value[0];
          startTime = GetTime();
          isPushBack = true;
          extend = false;
          step = 0;
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
            setNotiMessage("Invalid index");
          } else {
            val = value[0];
            startTime = GetTime();
            extend = false;
            isAddToIndex = true;
            step = 0;
          }
          showInputBox[2] = false;
          strcpy(input[0], "");
        }
      }
    }

    if (showDeleteButtons) {
      if (GuiButton({280, 470, 100, 40}, "Delete first")) {
        currentIndex = 0;
        isDeleteIndex = true;
        startTime = GetTime();
        step = 0;
        memset(showInputBox, 0, sizeof(showInputBox));
        showInputBox[0] = true;
      }
      if (GuiButton({400, 470, 100, 40}, "Delete last")) {
        isPopBack = true;
        startTime = GetTime();
        memset(showInputBox, 0, sizeof(showInputBox));
        showInputBox[0] = true;
      }
      if (GuiButton({520, 470, 100, 40}, "Delete index")) {
        if (currentIndex == -1) {
          setNotiMessage("Invalid index");
        } else {
          isDeleteIndex = true;
          startTime = GetTime();
          step = 0;
          memset(selected, 0, sizeof(selected));
          showInputBox[1] = false;
          strcpy(input[0], "");
        }
      }
    }

    if (showSearchButtons) {
      if (DrawInputBox({250, 530, 50, 30}, "", input[0], value[0],
                       enableInput[0], ICON_LENS)) {
        val = value[0];
        startTime = GetTime();
        isSearching = true;
        found = false;
        strcpy(input[0], "");
      }
    }

    if (showUpdateButtons) {
      if (DrawInputBox({250, 590, 50, 30}, "", input[0], value[0],
                       enableInput[0], ICON_REPEAT_FILL)) {
        if (currentIndex == -1) {
          setNotiMessage("Invalid index");
        } else {
          nodes[currentIndex].setVal(value[0]);
          memset(showInputBox, 0, sizeof(showInputBox));
          memset(selected, 0, sizeof(selected));
          strcpy(input[0], "");
        }
      }
    }

    DrawTextEx(font_bold, "index", {50, 177}, 22, 1, textColor);
    DrawTextEx(font_bold, TextFormat("N = %d", n), {50, 200}, 20, 1, textColor);
    for (int i = 0; i < n; i++) {
      nodes[i].setHasValue(true);
      nodes[i].setIndex(i);
      if (nodes[i].getIsClicked()) {
        bool tmp = selected[i];
        memset(selected, false, sizeof(selected));
        selected[i] = !tmp;
        if (!selected[i])
          currentIndex = -1;
      }
      if (isSearching) {
        if (nodes[i].getVal() == val && prv == i) {
          nodes[i].setHighlightColor(accentColor);
          found = true;
          setNotiMessage(TextFormat("Founded at index %d", i));
          if (GetTime() - startTime > 1) {
            nodes[i].setIsHighlighted(false);
            nodes[i].setHighlightColor();
            isSearching = false;
            prv = -1;
          }
        } else if (!found) {
          if (GetTime() - startTime > 0.5) {
            if (i == prv + 1) {
              startTime = GetTime();
              nodes[prv].setIsHighlighted(false);
              nodes[i].setIsHighlighted(true);
              prv = i;
            } else if (i == n - 1) {
              nodes[i].setIsHighlighted(false);
              isSearching = false;
              found = false;
              prv = -1;
              setNotiMessage(
                  TextFormat("No element with value = %d found", val));
            }
          }
        }
      }
      if (selected[i]) {
        nodes[i].setIsSelected(true);
        currentIndex = i;
      } else
        nodes[i].setIsSelected(false);
    }
    for (int i = 0; i < nodes.capacity(); i++) {
      nodes[i].setCurPos({BASE_X + 42 * i, BASE_Y});
      nodes[i].render();
    }

    if (isAddToIndex) {
      if (n == maxSize) {
        setNotiMessage("The array is full");
        isAddToIndex = false;
      } else if (step == 0) {
        Rectangle rect{
            nodes[currentIndex].getCurPos().x - 10,
            nodes[currentIndex].getCurPos().y - 5,
            (float)(42 * (n - currentIndex) + 18),
            50,
        };
        if (n == nodes.capacity() && !extend) {
          extend = true;
          nodes.reserve(nodes.capacity() * 2 + 1);
          for (int i = n; i < nodes.capacity(); i++) {
            CustomLog(LOG_INFO, TextFormat("%d", i), 0);
            nodes[i] = ArrayGuiNode();
          }
        }
        DrawRectangleLinesEx(rect, 2, textColor);
        if (GetTime() - startTime > 1) {
          startTime = GetTime();
          step = 1;
        }
      } else if (step == 1) {
        Rectangle rect{
            nodes[currentIndex + 1].getCurPos().x - 10,
            nodes[currentIndex + 1].getCurPos().y - 5,
            (float)(42 * (n - currentIndex) + 18),
            50,
        };
        DrawRectangleLinesEx(rect, 2, textColor);
        if (GetTime() - startTime > 1) {
          nodes[n].setHasValue(true);
          nodes[n].setIndex(n);
          for (int i = n; i > currentIndex; i--) {
            nodes[i].setVal(nodes[i - 1].val);
          }
          n++;
          startTime = GetTime();
          step = 2;
        }
      } else {
        if (GetTime() - startTime > 1) {
          nodes[currentIndex].setVal(val);
          currentIndex = -1;
          isAddToIndex = false;
          step = 0;
        }
      }
    }

    if (isPushBack) {
      if (n == maxSize) {
        setNotiMessage("The array is full");
        isPushBack = false;
      } else if (step == 0) {
        if (GetTime() - startTime > 0.5) {
          if (n == nodes.capacity() && !extend) {
            extend = true;
            nodes.reserve(nodes.capacity() * 2 + 1);
            for (int i = n; i < nodes.capacity(); i++)
              nodes[i] = ArrayGuiNode();
          }
          n++;
          startTime = GetTime();
          step++;
        }
      } else if (step == 1) {
        if (GetTime() - startTime > 0.5) {
          nodes[n - 1].setVal(val);
          nodes[n - 1].setHasValue(true);
          isPushBack = false;
        }
      }
    }

    if (isDeleteIndex) {
      if (step == 0) {
        Rectangle rect{nodes[currentIndex + 1].getCurPos().x - 10,
                       nodes[currentIndex + 1].getCurPos().y - 5,
                       (float)(42 * (n - currentIndex - 1) + 18), 50};
        DrawRectangleLinesEx(rect, 2, textColor);
        if (GetTime() - startTime > 1) {
          startTime = GetTime();
          step++;
        }
      } else if (step == 1) {
        Rectangle rect{nodes[currentIndex].getCurPos().x - 10,
                       nodes[currentIndex].getCurPos().y - 5,
                       (float)(42 * (n - currentIndex - 1) + 18), 50};
        DrawRectangleLinesEx(rect, 2, textColor);
        if (GetTime() - startTime > 0.5) {
          for (int i = currentIndex; i < n - 1; i++) {
            nodes[i].setVal(nodes[i + 1].getVal());
          }
          nodes[n - 1].setVal(0);
          nodes[n - 1].setHasValue(false);
          n--;
          startTime = GetTime();
          isDeleteIndex = false;
          step++;
        }
      }
    }

    if (isPopBack) {
      if (GetTime() - startTime > 0.5) {
        nodes[n - 1].setVal(0);
        nodes[n - 1].setHasValue(false);
      }
      if (GetTime() - startTime > 1) {
        n--;
        isPopBack = false;
      }
    }

    if (showCreateButtons) {
      if (GuiButton({280, 350, 100, 40}, "Random")) {
        createRandomArray();
      }
      if (GuiButton({400, 350, 100, 40}, "From file")) {
        fileDialogState.windowActive = true;
      }
      if (fileDialogState.windowActive)
        GuiLock();
      GuiUnlock();
      if (fileDialogState.SelectFilePressed) {
        if (IsFileExtension(fileDialogState.fileNameText, ".txt")) {
          strcpy(filePath, fileDialogState.fileNameText);
          CustomLog(LOG_INFO, TextFormat("Selected file: %s", filePath), 0);
          addFromFile();
        }
        fileDialogState.SelectFilePressed = false;
      }
      GuiFileDialog(&fileDialogState);
    }

    if (GetTime() - notiTime < 2 && notiTime > 0) {
      Vector2 textPos = MeasureTextEx(font_bold, notiMessage, 22, 1);
      Rectangle rect{0, 250, 80 + textPos.x, 20 + textPos.y};
      DrawRectangleRounded(rect, 0.1, 20, accentColor2);
      DrawTextEx(font_bold, notiMessage, {rect.x + 40, rect.y + 10}, 22, 1,
                 textColor);
    }
  }

  void add(int pos) {
    if (n == maxSize) {
      setNotiMessage("The array is full");
      return;
    }
    if (pos < 0 || pos > n) {
      setNotiMessage("Invalid index");
      return;
    }
    if (pos == n) {
      nodes[pos].setVal(val);
    } else {
      for (int i = n; i > pos; i--) {
        nodes[i].setVal(nodes[i - 1].val);
      }
      nodes[pos].setVal(val);
    }
    n++;
  }

  void setNotiMessage(const char* message) {
    strcpy(notiMessage, message);
    notiTime = GetTime();
  }

  void reset() {
    showCreateButtons = false;
    showAddButtons = false;
    showDeleteButtons = false;
    showSearchButtons = false;
    showUpdateButtons = false;
    memset(showInputBox, 0, sizeof(showInputBox));
  }

  void createRandomArray() {
    removeAllFromArray();
    n = 5 + rand() % (maxSize - 10);
    for (int i = 0; i < n; i++) {
      int val = 10 + rand() % 90;
      nodes[i].setVal(val);
    }
  }

  void addFromFile() {
    for (int i = 0; i < maxSize; i++) {
      nodes[i].setVal(0);
      nodes[i].setHasValue(false);
    }
    char* fileData = LoadFileText(filePath);
    strtok(fileData, ",");
    n = 0;
    while (fileData != NULL) {
      nodes[n].setVal(atoi(fileData));
      nodes[n].setIndex(n);
      nodes[n].setHasValue(true);
      n++;
      fileData = strtok(NULL, ",");
    }
  }

  void removeAllFromArray() {
    for (int i = 0; i < maxSize; i++) {
      nodes[i].setVal(0);
      nodes[i].setHasValue(false);
    }
  }
};

#endif
