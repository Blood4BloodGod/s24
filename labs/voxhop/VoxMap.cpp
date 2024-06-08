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

#include "VoxMap.h"
#include <istream>
#include <vector>
#include <unordered_map>
#include <queue>

VoxMap::VoxMap(std::istream& is) {
    int x, d, h;
    while (is >> x >> d >> h) {
        Point p = Point(static_cast<double>(x), static_cast<double>(d), static_cast<double>(h));
        // Assuming addEdge is a function that accepts Points and adds edges to your graph
        if (x > 0) {
            addEdge(p, Point(static_cast<double>(x - 1), static_cast<double>(d), static_cast<double>(h)));
            addEdge(Point(static_cast<double>(x - 1), static_cast<double>(d), static_cast<double>(h)), p);
        }
        if (d > 0) {
            addEdge(p, Point(static_cast<double>(x), static_cast<double>(d - 1), static_cast<double>(h)));
            addEdge(Point(static_cast<double>(x), static_cast<double>(d - 1), static_cast<double>(h)), p);
        }
        if (h > 0) {
            addEdge(p, Point(static_cast<double>(x), static_cast<double>(d), static_cast<double>(h - 1)));
            addEdge(Point(static_cast<double>(x), static_cast<double>(d), static_cast<double>(h - 1)), p);
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