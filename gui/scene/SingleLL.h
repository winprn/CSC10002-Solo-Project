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
    bool enableInput = false, enableInput2 = false, searchDone = true, animDone = true, isAdding = false;
    int input;
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