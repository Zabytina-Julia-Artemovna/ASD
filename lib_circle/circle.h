#pragma once
#include "../lib_point/point.h"
#include <cmath>
class Circle : public Point {
private:
    int _radius;
public:
    Circle(int x, int y, int radius) : Point(x,y), _radius(radius) {}
    Circle(Point coord_center, int radius)
        : Point(coord_center.getX(), coord_center.getY()), _radius(radius) {}
    Circle(const Circle& other) = default;
    int getR() const {
        return _radius;
    }
    void setR(int r) {
        _radius = r;
    }
    bool operator == (const Circle& other) const {
        return _x == other._x && _y == other._y && _radius == other._radius;
    }
    bool operator != (const Circle& other) const{
        return !(*this == other);
    }
};
