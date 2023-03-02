#include "SingleLL.h"
#include "../../lib/raylib.h"
#include "../components/GuiNode.h"

#include <string>
using namespace std;

int SingleLL::getSize() {
    int sz = 0;
    for (Node *cur = head; cur != nullptr; cur = cur->next) {
        sz++;
    }
    return sz;
}

int SingleLL::getHead() {
    if (head == nullptr) return 123;
    return head->val;
}

void SingleLL::add(int val) {
    Node* newNode = new Node;
    newNode->val = val;
    newNode->next = nullptr;
    newNode->guiNode = GuiNode({(float)(50 + 100 * size), 50});

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void SingleLL::render() {
    int idx = 0;
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        cur->guiNode.render();
    }
}

void SingleLL::getRandom() {
    int n = 4;
    for (int i = 0; i < n; i++) {
        add(6);
    }

    printf("%d", getSize());
}

void SingleLL::print() {
    for (Node *cur = head; cur != nullptr; cur = cur->next) {
        printf("%d ", cur->val);
    }
}

void SingleLL::remove(int id) {
    int idx = 0;
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        if (idx == id) {
            cur->guiNode.setNewOpacity(0);
        }
        if (idx > id) {
            cur->guiNode.setNewPos({(float)(50 + 100 * (idx - 1)), 50});
        }
    }
}