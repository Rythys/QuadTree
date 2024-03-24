#include <iostream>
#include "Vector.h"
#include "QuadTree.h"
#include "AutoTests.h"
using namespace std;



int main() {
    AutoTests();

    Vector v;
    std::cout << "Number of points:\n";
    int n;
    std::cin >> n;
    std::cout << "Type x and y:\n";
    double x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        v.push_back({x,y});
    }
    QuadTree QTT(v);
    std::cout << QTT << "\n";
    return 0;
}
