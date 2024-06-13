#include "Move.h"
#include <iostream>

int main() {
    Move move;
    if (!(std::cin >> move)) {
        std::cout << "Parse error." << std::endl;
        return 1;
    }

    if (!move.isValid()) {
        std::cout << "Parse error." << std::endl;
        return 1;
    }

    std::cout << move << std::endl;
    return 0;
}
