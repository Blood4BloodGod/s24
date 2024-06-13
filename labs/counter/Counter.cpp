#include "Counter.h"

Counter::Counter() : list(), index() {}

Counter::~Counter() {}

int Counter::get(const std::string& key) const {
    return index.get(key);
}

void Counter::set(const std::string& key, int value) {
    if (index.contains(key)) {
        list.update(key, value);
    } else {
        list.add(key, value);
        index.add(key, list.getNode(key));
    }
}

void Counter::inc(const std::string& key, int delta) {
    set(key, get(key) + delta);
}

void Counter::dec(const std::string& key, int delta) {
    set(key, get(key) - delta);
}

void Counter::del(const std::string& key) {
    if (index.contains(key)) {
        list.remove(key);
        index.remove(key);
    }
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
    return Iterator(list.end());
}
