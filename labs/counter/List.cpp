#include "List.h"

List::List() : head(nullptr), tail(nullptr), count(0), totalCount(0) {
    // Constructor
}

List::~List() {
    // Destructor
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

void List::add(const std::string& key, int value) {
    ListNode* newNode = new ListNode(key, value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
    totalCount += value;
}

void List::update(const std::string& key, int value) {
    ListNode* node = getNode(key);
    if (node) {
        totalCount += value - node->value;
        node->value = value;
    }
}

void List::remove(const std::string& key) {
    ListNode* node = getNode(key);
    if (node) {
        totalCount -= node->value;
        if (node == head) {
            head = node->next;
        }
        if (node == tail) {
            tail = node->prev;
        }
        if (node->prev) {
            node->prev->next = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        delete node;
        count--;
    }
}

ListNode* List::getNode(const std::string& key) const {
    ListNode* current = head;
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int List::size() const {
    return count;
}

int List::total() const {
    return totalCount;
}

ListNode* List::begin() const {
    return head;
}

ListNode* List::end() const {
    return nullptr;
}
