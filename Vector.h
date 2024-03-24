#ifndef QUADTREE_VECTOR_H
#define QUADTREE_VECTOR_H


#include <iostream>
#include "Point.h"

class Vector {
private:
    Point* vec;
    size_t sz;
    size_t realSize;
public:
    Vector();

    Vector(size_t size);

    Vector(const Vector& vec2);

    ~Vector();

    Vector& operator=(const Vector& vec2);

    void swap(Vector& s);

    void push_back(Point x);

    void pop_back();

    Point& operator[](int i);

    Point operator[] (int i) const;

    size_t size() const;

    size_t real_size() const;

    Point back() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec2);
};


#endif //QUADTREE_VECTOR_H
