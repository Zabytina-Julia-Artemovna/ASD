#pragma once
class Point {
protected:
    int _x;
    int _y;
public:
    Point() : _x(0), _y(0) {}
    Point(int x, int y) : _x(x), _y(y) {}
    Point(const Point& other) = default;
    int getX() const {
        return _x;
    }
    int getY() const {
        return _y;
    }
    void setX(int x) {
        _x = x;
    }
    void setY(int y) {
        _y = y;
    }
    void set(int x, int y) {
        _x = x;
        _y = y;
    }
    bool operator == (const Point& other) const {
        return _x == other._x && _y == other._y;
    }
    bool operator !=(const Point& other) const {
        return !(*this == other);
    }
    Point& operator=(const Point& other) = default;
    int getDistanceTo(const Point& other) const;
};
