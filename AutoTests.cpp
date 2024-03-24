#include "AutoTests.h"

bool AutoTest1() {
    Vector v;
    v.push_back({1,1});
    v.push_back({2.5,3.5});
    v.push_back({4.0,4.0});
    QuadTree QTT(v);
    Vector test = QTT.allPointsInBoundsReturn();
    if (test[0].x == 1 && test[0].y == 1 && test[1].x == 2.5 && test[1].y == 2.5 && test[2].x == 1 && test[2].x == 1 &&
        test[3].x == 1 && test[3].y == 2.5 && test[4].x == 2.5 && test[4].y == 4 && test[5].x == 2.5 && test[5].y == 3.5 &&
        test[6].x == 2.5 && test[6].y == 2.5 && test[7].x == 4 && test[7].y == 4 && test[8].x == 4 && test[8].y == 4) {
        return true;
    }
    return false;
}

bool AutoTest2() {
    Vector v;
    v.push_back({0.0,0.0});
    v.push_back({1.0,1.0});
    v.push_back({4.0,4.0});
    QuadTree QTT(v);
    Vector test = QTT.allPointsInBoundsReturn();
    if (test[0].x == 0 && test[0].y == 0 && test[1].x == 0.5 && test[1].y == 0.5 && test[2].x == 0 && test[2].x == 0 &&
        test[3].x == 0.5 && test[3].y == 0.5 && test[4].x == 1 && test[4].y == 1 && test[5].x == 1 && test[5].y == 1 &&
        test[6].x == 2 && test[6].y == 2 && test[7].x == 4 && test[7].y == 4 && test[8].x == 4 && test[8].y == 4) {
        return true;
    }
    return false;
}

bool AutoTests() {
    if (AutoTest1() && AutoTest2()) {
        std::cout << "All Auto Tests passed!\n";
        return true;
    } else {
        std::cout << "Some Auto Tests failed!\n";
        return false;
    }
}