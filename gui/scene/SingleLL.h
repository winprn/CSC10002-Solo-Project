#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "../../lib/raylib.h"
#include "../components/GuiNode.h"
#include "../components/HighlightRectangle.h"
#include <string>

class SingleLL {
  struct Node {
    int val;
    Node* next = nullptr;
    GuiNode guiNode;
  };

  Node *head, *tail;

 public:
  bool searchDone = true, animDone = true, isAdding = false, isDeleting = false,
       isUpdating = false, isSearching = false, showCreateButtons = false,
       showAddButtons = false, showDeleteButtons = false,
       showSearchButtons = false, showUpdateButtons = false,
       shouldHighlight = true, needUpdate = true, found = false,
       isAddToHead = false, isAddToTail = false, isNodeNext = false,
       isCodeNext = false;
  bool enableInput[10] = {false}, showInputBox[10] = {false},
       lineHighlight[10] = {false};
  int value[10] = {0}, index = -1, randomSize = 0, newVal = -1;
  float time = 0;
  char input[10][10] = {""}, *fileData = nullptr, filePath[512] = {0};
  const char* options = "ADD;DELETE;SEARCH";
  HighlightRectangle rect;

  int active = 0;
  SingleLL() : head(nullptr), tail(nullptr) {}
  ~SingleLL() {
    // delete active;
  }

  int getSize();
  int getHead();

  bool add(int val, int pos, bool hasAnimation = true);
  void reset();
  void render();
  void getRandom();
  void remove(int id);
  void removeAll();
  void removeFromLL();
  void search(int val = -1);
  void animate();
  void createRandomList();
  void addFromFile();
  void setIsLast();
  void update();
};

#endif
