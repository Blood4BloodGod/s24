#include "VoxMap.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <voxmap file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    VoxMap map(input);

    Point src(1, 1, 1);
    Point dst(11, 1, 1);
    Route route = map.route(src, dst);
    if (!route.empty()) {
        std::cout << "Valid route: " << route << std::endl;
    } else {
        std::cout << "Invalid path: Does not end at destination." << std::endl;
    }

    return 0;
}
