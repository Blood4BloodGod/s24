#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    int x, y, z;
    Point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << '(' << point.x << ", " << point.y << ", " << point.z << ')';
        return os;
    }
};

struct PointHasher {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) ^ std::hash<int>()(p.z);
    }
};

#endif // POINT_H