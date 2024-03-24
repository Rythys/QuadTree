//
// Created by r_yu_ on 15.11.2022.
//

#include "QuadTree.h"


QuadTree::QuadTree(Vector& pts) {
    // initialize boundary
    Point b1(pts[0].x, pts[0].y), b2(pts[0].x, pts[0].y);
    for (int i = 1; i < pts.size(); ++i) {
        b1.x = std::min(pts[i].x, b1.x);
        b1.y = std::min(pts[i].y, b1.y);
        b2.x = std::max(pts[i].x, b2.x);
        b2.y = std::max(pts[i].y, b2.y);
    }
    AABB boundary;
    boundary.min = b1;
    boundary.max = b2;
    boundary.center.x = (boundary.max.x + boundary.min.x) / 2;
    boundary.center.y = (boundary.max.y + boundary.min.y) / 2;

    root = new QuadTreeNode(boundary);
    if (pts.size() == 1) {
        root->point = pts[0];
    } else {
        for (int i = 0; i < static_cast<int>(pts.size()); ++i) {
            insert(root, pts[i]);
        }
    }

}

void QuadTree::Delete(QuadTreeNode* qt) {
    if (qt == nullptr) {
        return;
    }
    if (qt->southWest) {
        Delete(qt->southWest);
    }
    if (qt->southEast) {
        Delete(qt->southEast);
    }
    if (qt->northEast) {
        Delete(qt->northEast);
    }
    if (qt->northWest) {
        Delete(qt->northWest);
    }
    delete qt;
}

QuadTree::~QuadTree() {
    Delete(root);
    //delete root;
}

void QuadTree::insert(QuadTreeNode* qNode, Point pt) {

    if (!qNode->isPtInBoundary(pt)) {
        return;
    }
    double boundCentX = qNode->boundary.center.x, boundCentY = qNode->boundary.center.y;
    if ((boundCentX >= pt.x || isEqual(boundCentX, pt.x)) && (boundCentY >= pt.y || isEqual(boundCentY, pt.y))) { // SW

            if (qNode->southWest == nullptr && !qNode->isPtInBoundary(qNode->point)) { // в данной области нет точки и в southWest тоже нет
                Point p1(qNode->boundary.min.x, qNode->boundary.min.y), p2(boundCentX, boundCentY);
                AABB newBoundary(p1, p2);
                qNode->southWest = new QuadTreeNode(newBoundary);
                qNode->southWest->point = pt;
            } else if (qNode->southWest == nullptr && qNode->isPtInBoundary(qNode->point)) { // в данной области есть точка, и надо взять эту область, поделить ее, засунуть лежащую там точку в новую область и добавить новую точку
                if (qNode->point == pt) {
                    return;
                }
                Point tmp = qNode->point;
                qNode->point = qNode->outOfRange;
                insert(qNode, tmp);
                insert(qNode, pt);
            } else if (qNode->southWest != nullptr && qNode->isPtInBoundary(qNode->point)) { // такой случай не реализуется

            } else if (qNode->southWest != nullptr) { // в southWest есть точки. Далее рекурсивно заполняем эту область
                insert(qNode->southWest, pt);
            }
    } else if ((boundCentX >= pt.x || isEqual(boundCentX, pt.x)) && pt.y > boundCentY) { // NW

        if (qNode->northWest == nullptr && !qNode->isPtInBoundary(qNode->point)) { // в данной области нет точки и в southWest тоже нет
            Point p1(qNode->boundary.min.x, boundCentY), p2(boundCentX, qNode->boundary.max.y);
            AABB newBoundary(p1, p2);
            qNode->northWest = new QuadTreeNode(newBoundary);
            qNode->northWest->point = pt;
        } else if (qNode->northWest == nullptr && qNode->isPtInBoundary(qNode->point)) { // в данной области есть точка, и надо взять эту область, поделить ее, засунуть лежащую там точку в новую область и добавить новую точку
            if (qNode->point == pt) {
                return;
            }
            Point tmp = qNode->point;
            qNode->point = qNode->outOfRange;
            insert(qNode, tmp);
            insert(qNode, pt);
        } else if (qNode->northWest != nullptr && qNode->isPtInBoundary(qNode->point)) { // такой случай не реализуется

        } else if (qNode->northWest != nullptr) { // в southWest есть точки. Далее рекурсивно заполняем эту область
            insert(qNode->northWest, pt);
        }
    } else if (pt.x > boundCentX && (boundCentY >= pt.y || isEqual(boundCentY, pt.y))) { // SE

        if (qNode->southEast == nullptr && !qNode->isPtInBoundary(qNode->point)) { // в данной области нет точки и в southWest тоже нет
            Point p1(boundCentX, qNode->boundary.min.y), p2(qNode->boundary.max.x, boundCentY);
            AABB newBoundary(p1, p2);
            qNode->southEast = new QuadTreeNode(newBoundary);
            qNode->southEast->point = pt;
        } else if (qNode->southEast == nullptr && qNode->isPtInBoundary(qNode->point)) { // в данной области есть точка, и надо взять эту область, поделить ее, засунуть лежащую там точку в новую область и добавить новую точку
            if (qNode->point == pt) {
                return;
            }
            Point tmp = qNode->point;
            qNode->point = qNode->outOfRange;
            insert(qNode, tmp);
            insert(qNode, pt);
        } else if (qNode->southEast != nullptr && qNode->isPtInBoundary(qNode->point)) { // такой случай не реализуется

        } else if (qNode->southEast != nullptr) { // в southWest есть точки. Далее рекурсивно заполняем эту область
            insert(qNode->southEast, pt);
        }
    } else if (pt.x > boundCentX && pt.y > boundCentY) { // NE

        if (qNode->northEast == nullptr && !qNode->isPtInBoundary(qNode->point)) { // в данной области нет точки и в southWest тоже нет
            Point p1(boundCentX, boundCentY), p2(qNode->boundary.max.x, qNode->boundary.max.y);
            AABB newBoundary(p1, p2);
            qNode->northEast = new QuadTreeNode(newBoundary);
            qNode->northEast->point = pt;
        } else if (qNode->northEast == nullptr && qNode->isPtInBoundary(qNode->point)) { // в данной области есть точка, и надо взять эту область, поделить ее, засунуть лежащую там точку в новую область и добавить новую точку
            if (qNode->point == pt) {
                return;
            }
            Point tmp = qNode->point;
            qNode->point = qNode->outOfRange;
            insert(qNode, tmp);
            insert(qNode, pt);
        } else if (qNode->northEast != nullptr && qNode->isPtInBoundary(qNode->point)) { // такой случай не реализуется

        } else if (qNode->northEast != nullptr) { // в southWest есть точки. Далее рекурсивно заполняем эту область
            insert(qNode->northEast, pt);
        }
    }
}

bool QuadTreeNode::isPtInBoundary(Point pt) const {
    if (pt.x >= boundary.min.x && pt.x <= boundary.max.x && pt.y >= boundary.min.y && pt.y <= boundary.max.y) {
        return true;
    }
    return false;
}

bool QuadTree::isEqual(double p1, double p2) {
    if (std::abs(p1 - p2) < DBL_EPSILON) {
        return true;
    }
    return false;
}

void QuadTree::printQuadTree(std::ostream &os, const QuadTreeNode* qt) const {
    if (qt == nullptr) {
        return;
    }
    printQuadTree(os, qt->southWest);
    printQuadTree(os, qt->southEast);
    printQuadTree(os, qt->northWest);
    printQuadTree(os, qt->northEast);

    if (qt->isPtInBoundary(qt->point)) {
        os << "In boundary: (" << qt->boundary.min.x << ", " << qt->boundary.min.y << ") " << "(" << qt->boundary.max.x << ", " << qt->boundary.max.y << ") ";

        os << "Point: (" << qt->point.x << ", " << qt->point.y << ") \n";
    }


}

std::ostream &operator<<(std::ostream &os, const QuadTree& qt) {
    qt.printQuadTree(os, qt.root);
    return os;
}

void QuadTree::retQuadTree(Vector& res, const QuadTreeNode* qt) {
    if (qt == nullptr) {
        return;
    }
    retQuadTree(res, qt->southWest);
    retQuadTree(res, qt->southEast);
    retQuadTree(res, qt->northWest);
    retQuadTree(res, qt->northEast);

    if (qt->isPtInBoundary(qt->point)) {
        res.push_back({qt->boundary.min.x, qt->boundary.min.y});
        res.push_back({qt->boundary.max.x, qt->boundary.max.y});

        res.push_back({qt->point.x, qt->point.y});
    }


}

Vector QuadTree::allPointsInBoundsReturn() {
    Vector res;
    retQuadTree(res, this->root);
    return res;
}







