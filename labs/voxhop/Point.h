#ifndef POINT_H
#define POINT_H

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
};

#endif // POINT_H
