#include "VoxMap.h"
#include <sstream>
#include <stdexcept>
#include <queue>
#include <algorithm> // Include this for std::reverse
#include "Errors.h" // Include Errors.h for custom exceptions

VoxMap::VoxMap(std::istream& stream) {
    std::string line;
    std::getline(stream, line);
    if (stream.fail()) {
        throw std::runtime_error("Error reading the header line");
    }

    std::istringstream header(line);
    header >> width >> depth >> height;

    if (header.fail() || width <= 0 || depth <= 0 || height <= 0) {
        throw std::runtime_error("Invalid dimensions in header");
    }

    voxels.resize(height, std::vector<std::vector<bool>>(depth, std::vector<bool>(width, false)));

    for (int h = 0; h < height; ++h) {
        // Skip empty line between tiers
        std::getline(stream, line);
        if (stream.fail()) {
            throw std::runtime_error("Error reading empty line between tiers");
        }

        for (int d = 0; d < depth; ++d) {
            std::getline(stream, line);
            if (stream.fail()) {
                throw std::runtime_error("Error reading voxel data line");
            }

            if (line.length() != static_cast<size_t>(width / 4)) {
                throw std::runtime_error("Invalid line length for voxel data");
            }

            for (int w = 0; w < width / 4; ++w) {
                char hexChar = line[w];
                int binary;
                try {
                    binary = std::stoi(std::string(1, hexChar), nullptr, 16);
                } catch (const std::invalid_argument&) {
                    throw std::runtime_error("Invalid hex character in voxel data");
                }

                for (int b = 0; b < 4; ++b) {
                    bool isFilled = (binary & (1 << (3 - b))) != 0;
                    int x = w * 4 + b;
                    voxels[h][d][x] = isFilled;

                    if (!isFilled) {
                        Point p = {x, d, h};
                        // Add edges to adjacent empty voxels
                        if (x > 0 && !voxels[h][d][x - 1]) {
                            addEdge(p, {x - 1, d, h});
                            addEdge({x - 1, d, h}, p);
                        }
                        if (d > 0 && !voxels[h][d - 1][x]) {
                            addEdge(p, {x, d - 1, h});
                            addEdge({x, d - 1, h}, p);
                        }
                        if (h > 0 && !voxels[h - 1][d][x]) {
                            addEdge(p, {x, d, h - 1});
                            addEdge({x, d, h - 1}, p);
                        }
                    }
                }
            }
        }
    }
}

bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 && p.z < height && !voxels[p.z][p.y][p.x];
}

Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src) || !isValidPoint(dst)) {
        throw InvalidPoint(src);
    }

    std::map<Point, Point> cameFrom;
    std::map<Point, double> costSoFar;
    auto compare = [](const std::pair<double, Point>& a, const std::pair<double, Point>& b) { return a.first > b.first; };
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, decltype(compare)> frontier(compare);
    frontier.emplace(0, src);
    cameFrom[src] = src;
    costSoFar[src] = 0;
    
    while (!frontier.empty()) {
        Point current = frontier.top().second;
        frontier.pop();

        if (current == dst) break;

        for (const Point& next : adjacencyList[current]) {
            double newCost = costSoFar[current] + 1; // Assuming uniform cost
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                double priority = newCost + heuristic(next, dst);
                frontier.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
    }

    if (cameFrom.find(dst) == cameFrom.end()) {
        throw NoRoute(src, dst);
    }

    Route path;
    Point current = dst;
    while (current != src) {
        Point prev = cameFrom[current];
        if (prev.x < current.x) path.push_back(Move::EAST);
        else if (prev.x > current.x) path.push_back(Move::WEST);
        else if (prev.y < current.y) path.push_back(Move::SOUTH);
        else if (prev.y > current.y) path.push_back(Move::NORTH);
        current = prev;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}

void VoxMap::addEdge(const Point& a, const Point& b) {
    adjacencyList[a].push_back(b);
}

bool VoxMap::isFilledVoxel(char c, int index) const {
    int hexVal = c >= '0' && c <= '9' ? c - '0' : c - 'A' + 10;
    return (hexVal & (1 << (3 - index))) != 0;
}
