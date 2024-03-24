#include "Vector.h"

Vector::Vector():sz(0), realSize(2) {}

Vector::Vector(const size_t size) {
    sz = size;
    realSize = size * 2;
    vec = new Point[realSize];
    for (int i = 0; i < sz; ++i) {
        vec[i].x = 0;
        vec[i].y = 0;
    }
}

Vector::Vector(const Vector& vec2) {
    sz = vec2.sz;
    realSize = vec2.realSize;
    vec = new Point[realSize];
    for (int i = 0; i < sz; ++i) {
        vec[i] = vec2.vec[i];
    }
}

Vector& Vector::operator=(const Vector &vec2) {
    if (this == &vec2) {
        return *this;
    }
    if (realSize != 0 ) {
        delete[] vec;
    }
    sz = vec2.sz;
    realSize = vec2.realSize;
    vec = new Point[realSize];
    for (int i = 0; i < sz; ++i) {
        vec[i] = vec2.vec[i];
    }
//    Vector new_vec(vec2);
//    swap(new_vec);
    return *this;
}

void Vector::swap(Vector& vec2) {
    std::swap(vec, vec2.vec);
    std::swap(sz, vec2.sz);
    std::swap(realSize, vec2.realSize);
}

std::ostream& operator<<(std::ostream &os, const Vector &vec2) {
    for (int i = 0; i < static_cast<int>(vec2.sz); ++i) {
        os << "(" << vec2.vec[i].x << ", " << ")" << " ";
    }
    return os;
}


Vector::~Vector() {
    delete[] vec;
}

void Vector::push_back(Point x) {
    if (realSize <= sz + 2) {
        realSize *= 2;
        auto* tmp = new Point[realSize];
        for (int i = 0; i < static_cast<int>(sz); ++i) {
            tmp[i] = vec[i];
        }
        //delete[] vec;
        vec = tmp;
    }
    vec[sz] = x;
    ++sz;
}

Point &Vector::operator[](int i) {
    return vec[i];
}

Point Vector::operator[](int i) const {
    return vec[i];
}

size_t Vector::size() const {
    return sz;
}

size_t Vector::real_size() const {
    return realSize;
}

void Vector::pop_back() {
    if (sz > 0) {
        --sz;
    }
    if (realSize / 2 > sz) {
        Vector v2(*this);
        realSize /= 2;
        delete[] vec;
        vec = new Point[realSize];
        for (int i = 0; i < sz; ++i) {
            vec[i] = v2.vec[i];
        }
    }
}

Point Vector::back() const {
    return vec[sz - 1];
}