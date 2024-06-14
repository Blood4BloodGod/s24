#include "Index.h"
#include <cstring>
#include <iostream>

// FNV-1a Hash function
uint32_t fnv1a_hash(const std::string& key) {
    uint32_t hash = 2166136261u;
    for (char c : key) {
        hash ^= c;
        hash *= 16777619u;
    }
    return hash;
}

Index::Index() {
    std::memset(table, 0, sizeof(table));
}

Index::~Index() {
    clearTable();
}

int Index::hash(const std::string& key) const {
    return fnv1a_hash(key) % TABLE_SIZE;
}

void Index::clearTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* node = table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
    }
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
