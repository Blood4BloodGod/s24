#ifndef VOXMAP_H
#define VOXMAP_H

#include "Point.h"
#include <vector>
#include <unordered_map>
#include <istream>

using Route = std::vector<Point>; // Define Route as a vector of Point

class VoxMap {
public:
    VoxMap(std::istream& input);
    Route route(Point src, Point dst);

private:
    int width, depth, height;
    std::vector<std::vector<std::vector<bool>>> voxels;
    std::vector<Point> points;
    std::unordered_map<Point, std::vector<Point>, PointHasher> adjacencyList;

    bool isValidPoint(const Point& p) const;
    double heuristic(const Point& a, const Point& b) const;
    void addEdge(const Point& a, const Point& b);
};

#endif // VOXMAP_H
