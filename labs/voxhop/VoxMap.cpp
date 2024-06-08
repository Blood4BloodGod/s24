#include "VoxMap.h"
#include "Errors.h"
#include <sstream>   // Include this header for istringstream
#include <algorithm> // Include this header for std::reverse
#include <cmath>     // Include for std::abs

void VoxMap::addEdge(const Point& src, const Point& dst) {
    graph[src].push_back(dst);
}

bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 && p.z < height;
}

double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}

VoxMap::VoxMap(std::istream& stream) {
    std::string line;
    std::getline(stream, line);
    std::istringstream header(line);  // Correct usage of istringstream
    header >> width >> depth >> height;

    voxels.resize(height, std::vector<std::vector<bool>>(depth, std::vector<bool>(width, false)));

    for (int h = 0; h < height; ++h) {
        // Skip empty line between tiers
        std::getline(stream, line);
        for (int d = 0; d < depth; ++d) {
            std::getline(stream, line);
            for (int w = 0; w < width / 4; ++w) {
                char hexChar = line[w];
                int binary = std::stoi(std::string(1, hexChar), nullptr, 16);
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

Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src) || !isValidPoint(dst)) {
        throw InvalidPoint(src);
    }

    if (graph.find(src) == graph.end() || graph.find(dst) == graph.end()) {
        throw InvalidPoint(src);
    }

    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<std::pair<double, Point>>> frontier;
    frontier.emplace(0, src);

    std::unordered_map<Point, Point, PointHasher> came_from;
    std::unordered_map<Point, double, PointHasher> cost_so_far;
    came_from[src] = src;
    cost_so_far[src] = 0;

    while (!frontier.empty()) {
        Point current = frontier.top().second;
        frontier.pop();

        if (current == dst) {
            Route route;
            Point next = dst;
            while (next != src) {
                Point previous = came_from[next];
                if (next.x > previous.x) route.push_back(Move::EAST);
                else if (next.x < previous.x) route.push_back(Move::WEST);
                else if (next.y > previous.y) route.push_back(Move::NORTH);
                else if (next.y < previous.y) route.push_back(Move::SOUTH);
                else if (next.z > previous.z) route.push_back(Move::UP);
                else if (next.z < previous.z) route.push_back(Move::DOWN);
                next = previous;
            }
            std::reverse(route.begin(), route.end());
            return route;
        }

        for (const Point& next : graph[current]) {
            double new_cost = cost_so_far[current] + 1; // Assuming each move has a cost of 1
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, dst);
                frontier.emplace(priority, next);
                came_from[next] = current;
            }
        }
    }

    throw NoRoute(src, dst);
}
