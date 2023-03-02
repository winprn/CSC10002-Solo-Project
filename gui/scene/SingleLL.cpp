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

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void SingleLL::remove(int val) {
    Node* cur = head;
    Node* prev = nullptr;

    while (cur != nullptr) {
        if (cur->val == val) {
            if (prev == nullptr) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }

            delete cur;
            break;
        }

        prev = cur;
        cur = cur->next;
    }
}

void SingleLL::render() {
    int idx = 0;
    DrawText("Hi", 100, 100, 20, BLACK);
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        Vector2 pos{(float)(50 + 100 * idx), 50};
        GuiNode node(pos);
        node.render();
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