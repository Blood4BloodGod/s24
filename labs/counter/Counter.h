#pragma once
#include <string>
#include "List.h"
#include "Index.h"

class Counter {
public:
    Counter();
    ~Counter();

    bool get(const std::string& key) const;
    void set(const std::string& key, bool value);
    void inc(const std::string& key);
    void dec(const std::string& key);
    void del(const std::string& key);
    int count() const;

    class Iterator {
    public:
        Iterator(ListNode* node);

        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        std::string key() const;
        bool value() const;

    private:
        ListNode* current;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    List list;
    Index index;
};
