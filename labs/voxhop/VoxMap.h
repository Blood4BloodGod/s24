#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>
#include "Point.h"
#include "Route.h"
#include "Errors.h"

struct PointHasher {
  std::size_t operator()(const Point& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) ^ std::hash<int>()(p.z);
  }
};

class VoxMap {
  int width, depth, height;
  std::vector<std::vector<std::vector<bool>>> voxels;
  std::unordered_map<Point, std::vector<Point>, PointHasher> graph;

  void addEdge(const Point& src, const Point& dst);

public:
  VoxMap(std::istream& stream);
  Route route(Point src, Point dst);
};

#endif