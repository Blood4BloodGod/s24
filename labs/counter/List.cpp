#include "List.h"

List::List() : head(nullptr), tail(nullptr), count(0), totalCount(0) {}

List::~List() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

void List::add(const std::string& key, int value) {
    ListNode* newNode = new ListNode(key, value);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    count++;
    totalCount += value;
}

void List::update(const std::string& key, int value) {
    ListNode* node = getNode(key);
    if (node) {
        totalCount -= node->value;
        node->value = value;
        totalCount += value;
    }
}

void List::remove(const std::string& key) {
    ListNode* node = getNode(key);
    if (node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        totalCount -= node->value;
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
