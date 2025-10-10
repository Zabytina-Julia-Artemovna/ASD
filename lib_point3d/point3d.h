#pragma once
#include "../lib_point/point.h"
class Point3D : public Point {
protected:
    int _z;
public:
    Point3D() : Point(0,0), _z(0) {}
    Point3D(int x, int y, int z): Point(x,y), _z(z){}
    Point3D(const Point3D& other) = default;
    int getZ() const {
        return _z;
    }
    void setZ(int z) {
        _z = z;
    }
    bool operator == (const Point3D& other) const {
        return _x == other._x && _y == other._y && _z == other._z;
    }
    bool operator != (const Point3D& other) const {
        return !(*this == other);
    }
    int getDistanceTo(const Point3D& other) const;
};
