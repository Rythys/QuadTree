#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H


#include <iostream>
#include <cfloat>
#include "Point.h"
#include "Vector.h"


struct QuadTreeNode {

    AABB boundary;
    Point point;

    QuadTreeNode *northWest = nullptr;
    QuadTreeNode *northEast = nullptr;
    QuadTreeNode *southWest = nullptr;
    QuadTreeNode *southEast = nullptr;

    Point outOfRange;

    QuadTreeNode(AABB _boundary) : boundary(_boundary) {
        point.x = boundary.min.x - 10;
        point.y = boundary.min.y - 10;
        outOfRange = point;
    }


    bool isPtInBoundary(Point pt) const;

};

class QuadTree {
private:
    QuadTreeNode* root;
public:
    QuadTree(Vector& pts);
    void Delete(QuadTreeNode* QT);
    ~QuadTree();
    void insert(QuadTreeNode* qNode, Point pt);
    bool isEqual(double p1, double p2);
    void printQuadTree(std::ostream &os, const QuadTreeNode* qt) const;
    friend std::ostream& operator<<(std::ostream& os, const QuadTree& qt);
    void retQuadTree(Vector& res, const QuadTreeNode* qt);
    Vector allPointsInBoundsReturn();
};

#endif //QUADTREE_QUADTREE_H
