#ifndef VOXMAP_H
#define VOXMAP_H

#include <vector>
#include <iostream>
#include <unordered_map>

#include "Point.h"

using Route = std::vector<Point>;

class VoxMap {
public:
    VoxMap(std::istream& input);
    ~VoxMap() = default; // Destructor

    Route route(Point src, Point dst);
    bool isValidPoint(const Point& p) const;

private:
    int width, depth, height;
    std::vector<std::vector<std::vector<bool>>> voxels;
    std::unordered_map<Point, std::vector<Point>, PointHasher> adjacencyList;

    void addEdge(const Point& a, const Point& b);
    double heuristic(const Point& a, const Point& b) const;
};

#endif // VOXMAP_H
