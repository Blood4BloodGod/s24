#ifndef VOXMAP_H
#define VOXMAP_H

#include "Point.h"
#include <unordered_map>
#include <vector>
#include <istream>

using Route = std::vector<Point>;

class VoxMap {
public:
    VoxMap(std::istream& input);

    Route route(Point src, Point dst);

private:
    bool isValidPoint(const Point& point) const;
    void addEdge(const Point& a, const Point& b);
    double heuristic(const Point& a, const Point& b) const;

    std::unordered_map<Point, std::vector<Point>, PointHasher> adjacencyList;
    std::unordered_map<Point, Point, PointHasher> parentMap;
};

#endif // VOXMAP_H
