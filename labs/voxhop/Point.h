#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x, y, z;

    // Default constructor
    Point() : x(0), y(0), z(0) {}

    // Parameterized constructor
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    // Declare the stream operators
    friend std::istream& operator>>(std::istream& stream, Point& point);
    friend std::ostream& operator<<(std::ostream& stream, const Point& point);
};

// Hash function for Point
struct PointHasher {
    std::size_t operator()(const Point& p) const {
        return std::hash<double>()(p.x) ^ std::hash<double>()(p.y) ^ std::hash<double>()(p.z);
    }
};

#endif // POINT_H
