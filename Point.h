//
// Created by r_yu_ on 23.11.2022.
//

#ifndef QUADTREE_POINT_H
#define QUADTREE_POINT_H

#include <iostream>
#include <climits>

struct Point {
    double x;
    double y;
    Point():x(0), y(0) {}
    Point(double x, double y):x(x), y(y) {}
    ~Point() = default;
    Point& operator=(const Point& other) = default;
    bool operator==(const Point& other) {
        if (x == other.x && y == other.y) {
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream &os) {
        os << x << " " << y;
        return os;
    }
};

struct AABB {
    Point min;
    Point max;
    Point center;
    AABB(): min(0,0), max(0,0), center(0, 0) {}
    AABB(Point min, Point max):min(min), max(max) {
        center.x = (max.x + min.x) / 2;
        center.y = (max.y + min.y) / 2;
    }
    ~AABB() = default;
    AABB& operator=(const AABB& other) = default;
};


#endif //QUADTREE_POINT_H
