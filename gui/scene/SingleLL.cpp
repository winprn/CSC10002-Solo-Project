#include "SingleLL.h"
#include "../../lib/raylib.h"
#include "../../lib/raygui.h"
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

bool SingleLL::add(int val) {
    if (getSize() >= 10) return false;
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
    return true;
}

void SingleLL::render() {
    int idx = 0;
    removeFromLL();
    // if (GuiButton({100, 200, 100, 50}, "Delete")) {
    //     remove(0);
    // }
    // if (GuiButton({250, 200, 100, 50}, "New List")) {
    //     getRandom();
    // }
    // if (GuiTextBox({100, 300, 100, 50}, input, 10, true) && strlen(input)) {
    //     bool result = add(atoi(input));
    //     if (!result) {
    //         // CustomLog(LOG_DEBUG, "Cannot add more", 0);
    //     } else {
    //         // CustomLog(LOG_DEBUG, TextFormat("Added %d", atoi(s)), 0);
    //     }
    //     strcpy(input, "");
    // }

    switch (active)
    {
    case 0:
        if (GuiButton({150, 220, 100, 50}, "Random")) {
            getRandom();
        }
        break;
    case 1:
        if (GuiButton({100, 220, 150, 50}, "Delete head")) {
            remove(0);
        }
        if (GuiButton({300, 220, 150, 50}, "Delete tail")) {
            remove(getSize() - 1);
        }
        DrawText("Input index to delete", 500, 180, 20, BLACK);
        if (GuiTextBox({500, 220, 150, 50}, input, 10, enableInput) && strlen(input)) {
            int id = atoi(input);
            remove(id);
            strcpy(input, "");
        }
        if (IsMouseButtonDown(0)) {
            if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, {500, 220, 150, 50})) {
                enableInput = true;
            } else enableInput = false;
        }
        break;
    
    default:
        break;
    }

    active = GuiComboBox((Rectangle){150, 150, 120, 50}, options, active);
    for (Node *cur = head; cur != nullptr; cur = cur->next, idx++) {
        cur->guiNode.setNewPos({(float)(50 + 130 * idx), 50});
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
            if (found == tail) {
                tail = prev;
                tail->guiNode.setIsLast(true);
            }
            prev->next = found->next;
        }
        delete found;
        render();
    }
}