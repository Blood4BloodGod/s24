#include "VoxMap.h"
#include "Errors.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <stdexcept>

VoxMap::VoxMap(std::istream& input) {
    Point p;
    while (input >> p) {
        adjacencyList[p] = std::vector<Point>();
    }
    for (auto& [point, _] : adjacencyList) {
        // Add edges for the neighboring points if valid
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dz = -1; dz <= 1; ++dz) {
                    if (dx == 0 && dy == 0 && dz == 0) continue;
                    Point neighbor(point.x + dx, point.y + dy, point.z + dz);
                    if (adjacencyList.find(neighbor) != adjacencyList.end()) {
                        addEdge(point, neighbor);
                    }
                }
            }
        }
    }
}

bool VoxMap::isValidPoint(const Point& point) const {
    return adjacencyList.find(point) != adjacencyList.end();
}

void VoxMap::addEdge(const Point& a, const Point& b) {
    adjacencyList[a].push_back(b);
}

double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src)) throw InvalidPoint(src);
    if (!isValidPoint(dst)) throw InvalidPoint(dst);

    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;
    std::unordered_map<Point, double, PointHasher> gScore;
    std::unordered_map<Point, double, PointHasher> fScore;

    openSet.emplace(0.0, src);
    gScore[src] = 0.0;
    fScore[src] = heuristic(src, dst);

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if (current == dst) {
            Route path;
            while (current != src) {
                path.push_back(current);
                current = parentMap[current];
            }
            path.push_back(src);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Point& neighbor : adjacencyList[current]) {
            double tentative_gScore = gScore[current] + heuristic(current, neighbor);
            if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                parentMap[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, dst);
                openSet.emplace(fScore[neighbor], neighbor);
            }
        }
    }

    throw NoRoute(src, dst);
}
