#include "SingleLL.h"

#include <string>
using namespace std;

char const * SingleLL::getSize() {
    char const *str = to_string(size).c_str();
    return str;
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
    printf("%d", size);
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
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        Vector2 pos{(float)(50 + 100 * idx), 50};
        GuiNode node(pos);
        node.render();
    }
}

void SingleLL::getRandom() {
    int n = 4;
    for (int i = 0; i < n; i++) {
        printf("%d", rand() % 20);
        add(rand() % 20);
    }
}