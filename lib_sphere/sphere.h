#pragma once
#include "../lib_point3d/point3d.h"
class Sphere : public Point3D {
private:
    int _radius;
public:
    Sphere(int x, int y, int z, int radius) : Point3D(x, y, z), _radius(radius) {}
    Sphere(Point3D _coord_center, int radius) : Point3D(_coord_center), _radius(radius) {}
    Sphere(const Sphere& other) = default;
    int getR() const {
        return _radius;
    }
    void setR(int radius) {
        _radius = radius;
    }
    bool operator ==(const Sphere& other) const {
        return _x == other._x && _y == other._y && _z == other._z && _radius == other._radius;
    }
    bool operator != (const Sphere& other) const {
        return !(*this == other);
    }
};
