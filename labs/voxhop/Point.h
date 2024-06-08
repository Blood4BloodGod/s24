#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x, y, z;

    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    // Declare the stream operators
    friend std::istream& operator>>(std::istream& stream, Point& point);
    friend std::ostream& operator<<(std::ostream& stream, const Point& point);
};

#endif // POINT_H
