#pragma once
#include <string>
#include "List.h"

class Index {
public:
    Index();
    ~Index();

    void add(const std::string& key, ListNode* node);
    void remove(const std::string& key);
    bool contains(const std::string& key) const;
    int get(const std::string& key) const;
    ListNode* getNode(const std::string& key) const;

private:
    static const int TABLE_SIZE = 400000;  // Increased table size to reduce collisions
    struct HashNode {
        std::string key;
        ListNode* node;
        HashNode* next;

        HashNode(const std::string& key, ListNode* node) : key(key), node(node), next(nullptr) {}
    };
    HashNode* table[TABLE_SIZE];

    int hash(const std::string& key) const;
};
