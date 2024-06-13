#include "Point.h"
#include <istream>
#include <ostream>

// Operator to read a Point from an input stream
std::istream& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y >> point.z;
    return stream;
}

// Operator to write a Point to an output stream
std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << point.x << " " << point.y << " " << point.z;
    return stream;
}
