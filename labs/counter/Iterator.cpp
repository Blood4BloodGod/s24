#include "Counter.h"

Counter::Iterator::Iterator(ListNode* node) : current(node) {}

bool Counter::Iterator::operator!=(const Counter::Iterator& other) const {
    return current != other.current;
}

Counter::Iterator& Counter::Iterator::operator++() {
    if (current) {
        current = current->next;
    }
    return *this;
}

std::string Counter::Iterator::key() const {
    return current ? current->key : "";
}

bool Counter::Iterator::value() const {
    return current ? current->value : false;
}
