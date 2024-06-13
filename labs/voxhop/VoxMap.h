#ifndef VOXMAP_H
#define VOXMAP_H

#include <vector>
#include <map>
#include "Point.h"
#include "Route.h"

class VoxMap {
public:
    VoxMap(std::istream& input);
    Route route(Point src, Point dst);
    bool isValidPoint(const Point& p) const;

private:
    int width, depth, height;
    std::vector<std::vector<std::vector<bool>>> voxels;
    std::map<Point, std::vector<Point>> adjacencyList;
    std::vector<Point> points;

    double heuristic(const Point& a, const Point& b) const;
    void addEdge(const Point& a, const Point& b);
    bool isFilledVoxel(char c, int index) const;
};

#endif // VOXMAP_H
