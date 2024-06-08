#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

class Point {
public:
    double x, y, z;

    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y >> point.z;
        return is;
    }
};

struct PointHasher {
    std::size_t operator()(const Point& point) const {
        return std::hash<double>()(point.x) ^ std::hash<double>()(point.y) ^ std::hash<double>()(point.z);
    }
};

// Overload operator<< for Route (std::vector<Point>)
inline std::ostream& operator<<(std::ostream& os, const std::vector<Point>& route) {
    for (const auto& point : route) {
        os << point << " ";
    }
    return os;
}

#endif // POINT_H
