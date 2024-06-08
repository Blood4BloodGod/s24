#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x, y, z;
    Point() : x(0), y(0), z(0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    // Comparison operator for sorting
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    // Declare input and output stream operators
    friend std::istream& operator>>(std::istream& stream, Point& point);
    friend std::ostream& operator<<(std::ostream& stream, const Point& point);
};

#endif // POINT_H