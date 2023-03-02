#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "../../lib/raylib.h"
#include <string>

class SingleLL {
    struct Node {
        int val;
        Node* next;
    };

    Node* head, *tail;

    public:
    int size = 0;
    SingleLL(): head(nullptr), tail(nullptr) {}
    
    int getSize();
    int getHead();

    void add(int val);
    void render();
    void getRandom();
    void print();
    void remove(int id);
};

#endif