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
    newNode->guiNode = GuiNode({(float)(0), 50});
    newNode->guiNode.setVal(val);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        head->guiNode.setIsLast(true);
    } else {
        tail->next = newNode;
        tail->guiNode.setIsLast(false);
        tail = newNode;
        tail->guiNode.setIsLast(true);
    }
    size++;
}

void SingleLL::render() {
    int idx = 0;
    removeFromLL();
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        cur->guiNode.setNewPos({(float)(50 + 200 * idx), 50});
    }
}

void SingleLL::getRandom() {
    // removeAll();
    int n = max(1, rand() % 10);
    for (int i = 0; i < n; i++) {
        add(rand() % 20);
    }
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
    }
}

void SingleLL::removeAll() {
    while (head != nullptr) {
        remove(0);
    }
    size = 0;
}

void SingleLL::removeFromLL() {
    Node* found = nullptr;
    int idx = 0;
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        if (cur->guiNode.getOpacity() <= 0.0005) {
            found = cur;
            break;
        }
    }

    if (found != nullptr) {
        if (found == head) {
            head = head->next;
        } else {
            Node *prev = head;
            while (prev->next != found) {
                prev = prev->next;
            }
            prev->next = found->next;
        }
        delete found;
        render();
    }
}