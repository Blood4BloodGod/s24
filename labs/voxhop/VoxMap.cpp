#include "VoxMap.h"
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_map>

bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 && p.z < height && voxels[p.x][p.y][p.z];
}

VoxMap::VoxMap(std::istream& input) {
    input >> width >> depth >> height;
    voxels = std::vector<std::vector<std::vector<bool>>>(width, std::vector<std::vector<bool>>(depth, std::vector<bool>(height, false)));
    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < depth; ++y) {
            for (int x = 0; x < width; ++x) {
                char voxel;
                input >> voxel;
                voxels[x][y][z] = (voxel == '1');
                if (voxels[x][y][z]) {
                    Point p(x, y, z);
                    points.push_back(p);
                    if (x > 0 && voxels[x - 1][y][z]) {
                        addEdge(p, Point(x - 1, y, z));
                        addEdge(Point(x - 1, y, z), p);
                    }
                    if (y > 0 && voxels[x][y - 1][z]) {
                        addEdge(p, Point(x, y - 1, z));
                        addEdge(Point(x, y - 1, z), p);
                    }
                    if (z > 0 && voxels[x][y][z - 1]) {
                        addEdge(p, Point(x, y, z - 1));
                        addEdge(Point(x, y, z - 1), p);
                    }
                }
            }
        }
    }
}

Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src) || !isValidPoint(dst)) {
        return Route(); // Return an empty route if the source or destination is invalid
    }

    std::unordered_map<Point, Point, PointHasher> cameFrom;
    std::unordered_map<Point, double, PointHasher> costSoFar;
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

    Route path;
    if (cameFrom.find(dst) == cameFrom.end()) return path; // No route found

    Point current = dst;
    while (current != src) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());
    return path;
}

double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}

void VoxMap::addEdge(const Point& a, const Point& b) {
    adjacencyList[a].push_back(b);
}

// Helper function to print Route
std::ostream& operator<<(std::ostream& os, const Route& route) {
    for (const auto& point : route) {
        os << point << ' ';
    }
    return os;
}
