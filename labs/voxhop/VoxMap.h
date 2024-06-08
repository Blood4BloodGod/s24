#ifndef VOXMAP_H
#define VOXMAP_H

#include "Point.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using Route = std::vector<Point>;

class VoxMap {
public:
    VoxMap(std::istream& input);
    Route route(Point src, Point dst);
    bool isValidPoint(const Point& p) const;

private:
    int width, depth, height;
    std::vector<std::vector<std::vector<bool>>> voxels;
    std::vector<Point> points;
    std::unordered_map<Point, std::vector<Point>, PointHasher> adjacencyList;

    double heuristic(const Point& a, const Point& b) const;
    void addEdge(const Point& a, const Point& b);
};

// Declare operator<< for Route
std::ostream& operator<<(std::ostream& os, const Route& route);

#endif // VOXMAP_H
