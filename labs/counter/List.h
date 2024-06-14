#pragma once
#include <string>

struct ListNode {
    std::string key;
    bool value;
    ListNode* prev;
    ListNode* next;

    ListNode(const std::string& key, bool value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class List {
public:
    List();
    ~List();

    void add(const std::string& key, bool value);
    void update(const std::string& key, bool value);
    void remove(const std::string& key);
    ListNode* getNode(const std::string& key) const;
    int size() const;

    ListNode* begin() const;
    ListNode* end() const;

private:
    ListNode* head;
    ListNode* tail;
    int count;
};
