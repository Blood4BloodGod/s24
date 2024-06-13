#include "Index.h"
#include <cstring>

Index::Index() {
    std::memset(table, 0, sizeof(table));
}

Index::~Index() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* node = table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
    }
}

int Index::hash(const std::string& key) const {
    unsigned long hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;  // Improved hash function
    }
    return hash % TABLE_SIZE;
}

void Index::add(const std::string& key, ListNode* node) {
    int index = hash(key);
    HashNode* newNode = new HashNode(key, node);
    newNode->next = table[index];
    table[index] = newNode;
}

void Index::remove(const std::string& key) {
    int index = hash(key);
    HashNode* node = table[index];
    HashNode* prev = nullptr;

    while (node && node->key != key) {
        prev = node;
        node = node->next;
    }

    if (node) {
        if (prev) {
            prev->next = node->next;
        } else {
            table[index] = node->next;
        }
        delete node;
    }
}

bool Index::contains(const std::string& key) const {
    int index = hash(key);
    HashNode* node = table[index];
    while (node) {
        if (node->key == key) {
            return true;
        }
        node = node->next;
    }
    return false;
}

int Index::get(const std::string& key) const {
    int index = hash(key);
    HashNode* node = table[index];
    while (node) {
        if (node->key == key) {
            return node->node->value;
        }
        node = node->next;
    }
    return 0;
}

ListNode* Index::getNode(const std::string& key) const {
    int index = hash(key);
    HashNode* node = table[index];
    while (node) {
        if (node->key == key) {
            return node->node;
        }
        node = node->next;
    }
    return nullptr;
}
