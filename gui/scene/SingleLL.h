#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "../../lib/raylib.h"
#include "../components/GuiNode.h"
#include <string>

class SingleLL {
    struct Node {
        int val;
        Node* next;
        GuiNode guiNode;
    };

    Node* head, *tail;

    public:
    bool enableInput = false;
    int input;
    const char* options = "ADD;DELETE;SEARCH";

    int active = 0;
    SingleLL(): head(nullptr), tail(nullptr) {}
    ~SingleLL() {
        // delete active;
    }
    
    int getSize();
    int getHead();

    bool add(int val);
    void render();
    void getRandom();
    void print();
    void remove(int id);
    void removeAll();
    void removeFromLL();
};

#endif