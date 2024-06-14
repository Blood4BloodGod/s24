#include "Counter.h"

Counter::Counter() : list(), index() {}

Counter::~Counter() {}

bool Counter::get(const std::string& key) const {
    return index.contains(key);
}

void Counter::set(const std::string& key, bool value) {
    if (value) {
        if (!index.contains(key)) {
            list.add(key, value);
            index.add(key, list.getNode(key));
        }
    } else {
        del(key);
    }
}

void Counter::inc(const std::string& key) {
    set(key, true);
}

void Counter::dec(const std::string& key) {
    set(key, false);
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

Counter::Iterator Counter::begin() const {
    return Iterator(list.begin());
}

Counter::Iterator Counter::end() const {
    return Iterator(nullptr);
}
