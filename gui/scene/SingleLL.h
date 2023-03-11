#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "../../lib/raylib.h"
#include "../components/GuiNode.h"
#include <string>

class SingleLL {
    struct Node {
        int val;
        Node* next = nullptr;
        GuiNode guiNode;
    };

    Node *head, *tail;

    public:
    bool searchDone = true, animDone = true, isAdding = false;
    bool enableInput[10] = {false};
    int value[10] = {0};
    char input[10][10] = {""};
    const char* options = "ADD;DELETE;SEARCH";

    int active = 0;
    SingleLL(): head(nullptr), tail(nullptr) {}
    ~SingleLL() {
        // delete active;
    }
    
    int getSize();
    int getHead();

    bool add(int val, int pos);
    void addToLL(int val);
    void render();
    void getRandom();
    void remove(int id);
    void removeAll();
    void removeFromLL();
    void search(int val = -1);
};

#endif