#pragma once
#include <string>
#include "List.h"
#include "Index.h"

class Counter {
public:
    Counter();
    ~Counter();

    int get(const std::string& key) const;
    void set(const std::string& key, int value);
    void inc(const std::string& key, int delta = 1);
    void dec(const std::string& key, int delta = 1);
    void del(const std::string& key);
    int count() const;
    int total() const;

    class Iterator {
    public:
        Iterator(ListNode* node);

        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        std::string key() const;
        int value() const;

    private:
        ListNode* current;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    List list;
    Index index;
};

