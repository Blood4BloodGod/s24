#include "Index.h"

Index::Index() {
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

Index::~Index() {
    // Clean up hash table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = table[i];
        while (current) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
}

void Index::add(const std::string& key, ListNode* node) {
    int index = hash(key);
    HashNode* newNode = new HashNode(key, node);

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        HashNode* current = table[index];
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Index::remove(const std::string& key) {
    int index = hash(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool Index::contains(const std::string& key) const {
    int index = hash(key);
    HashNode* current = table[index];

    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

int Index::get(const std::string& key) const {
    int index = hash(key);
    HashNode* current = table[index];

    while (current) {
        if (current->key == key) {
            return current->node->value;
        }
        current = current->next;
    }

    return 0; // Key not found
}

ListNode* Index::getNode(const std::string& key) const {
    int index = hash(key);
    HashNode* current = table[index];

    while (current) {
        if (current->key == key) {
            return current->node;
        }
        current = current->next;
    }

    return nullptr; // Key not found
}

int Index::hash(const std::string& key) const {
    unsigned long hashValue = 5381;
    for (char c : key) {
        hashValue = ((hashValue << 5) + hashValue) + c; /* hash * 33 + c */
    }
    return hashValue % TABLE_SIZE;
}
