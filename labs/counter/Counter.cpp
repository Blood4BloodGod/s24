#include "Counter.h"

Counter::Counter() : list(), index() {
    // Constructor
}

Counter::~Counter() {
    // Destructor
}

int Counter::get(const std::string& key) const {
    ListNode* node = index.getNode(key);
    if (node) {
        return node->value;
    }
    return 0; // Key not found
}

void Counter::set(const std::string& key, int value) {
    ListNode* node = index.getNode(key);
    if (node) {
        list.update(key, value);
    } else {
        list.add(key, value);
        index.add(key, list.getNode(key));
    }
}

void Counter::inc(const std::string& key, int delta) {
    ListNode* node = index.getNode(key);
    if (node) {
        list.update(key, node->value + delta);
    } else {
        list.add(key, delta);
        index.add(key, list.getNode(key));
    }
}

void Counter::dec(const std::string& key, int delta) {
    ListNode* node = index.getNode(key);
    if (node) {
        list.update(key, node->value - delta);
        if (node->value <= 0) {
            del(key);
        }
    }
}

void Counter::del(const std::string& key) {
    list.remove(key);
    index.remove(key);
}

int Counter::count() const {
    return list.size();
}

int Counter::total() const {
    return list.total();
}

Counter::Iterator Counter::begin() const {
    return Iterator(list.begin());
}

Counter::Iterator Counter::end() const {
    return Iterator(nullptr);
}
