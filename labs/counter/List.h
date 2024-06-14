#pragma once
#include <string>

struct ListNode {
    std::string key;
    int value;
    ListNode* prev;
    ListNode* next;

    ListNode(const std::string& key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class List {
public:
    List();
    ~List();

    void add(const std::string& key, int value);
    void update(const std::string& key, int value);
    void remove(const std::string& key);
    ListNode* getNode(const std::string& key) const;
    int size() const;
    int total() const;

    ListNode* begin() const;
    ListNode* end() const;

private:
    ListNode* head;
    ListNode* tail;
    int count;
    int totalCount;
};
