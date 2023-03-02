#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "../components/GuiNode.h"
#include <string>

class SingleLL {
    struct Node {
        int val;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    public:
    char const * getSize() {}
    void add(int val) {}

    void remove(int val) {}

    void render() {}

    void getRandom() {}

    // void remove(int id) {
    //     int idx = 0;
    //     for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
    //         if (idx == id) {
                
    //             break;
    //         }
    //     }
    // }
};

#endif