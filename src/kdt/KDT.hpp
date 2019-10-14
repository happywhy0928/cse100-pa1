#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    /**
     * build a balanced KD tree. First we search if the given vector is
     * empty or not, if empty then return directly.
     */
    void build(vector<Point>& points) {
        // check if the given vector is empty or not
        if (points.size() == 0) {
            return;
        }

        root = nullptr;
        iheight = -1;
        isize = points.size();
        root = buildSubtree(points, 0, points.size(), 0, 0);
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) {
        KDNode* curr = root;
        if (curr == nullptr) {
            return nullptr;
        }
        queryPoint.setDistToQuery(curr->point);
        findNNHelper(curr, queryPoint, 0);
        return &(curr->point);
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /**
     * get the number of items currently in the KDT
     * Return: unsigned integer of currently number of elements
     */
    unsigned int size() const { return isize; }

    /**
     * get the currently height of the KDT
     * Return: integer of currently height of tree
     */
    int height() const { return iheight; }

  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start >= end) {
            return nullptr;
        }
        sort(start, end, CompareValueAt(curDim));
        int mid = (start + end - 1) / 2;
        KDNode* curr = new KDNode(points[mid]);
        curDim = curDim + 1;
        if (end - start > 1) {
            curDim = curDim % numDim;
            height = height + 1;
            curr->left = buildSubtree(points, start, mid, curDim, height);
            curr->right = buildSubtree(points, mid + 1, end, curDim, height);
        }
        if (iheight < height) {
            iheight = height;
        }
        return curr;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        // KDNode * temp = findFirstGuess(root,queryPoint,0);
        KDNode* curr = node;
        // queryPoint.setDistToQuery(node->point);
        double smallestSquare = queryPoint.distToQuery;
        double squareDistance =
            pow(curr->point.valueAt(curDim) - queryPoint.valueAt(curDim), 2.0);
        if (curr->left != nullptr && squareDistance <= smallestSquare) {
            // if(squareDistance <= smallestSquare){
            //  return;
            //
            curr = curr->left;
            curDim = curDim + 1;
            curDim = curDim % numDim;
            findNNHelper(curr, queryPoint, curDim);
        }
        if (curr->right != nullptr && squareDistance <= smallestSquare) {
            curr = curr->right;
            curDim = curDim + 1;
            curDim = curDim % numDim;
            findNNHelper(curr, queryPoint, curDim);
        }
        if (squareDistance <= smallestSquare) {
            queryPoint.setDistToQuery(curr->point);
            double check = queryPoint.distToQuery;
            if (check <= smallestSquare) {
                node = curr;
                smallestSquare = check;
            }
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    static void deleteAll(KDNode* n) {
        if (n == nullptr) {
            return;
        }
        if (n->left) {
            deleteAll(n->left);
        }
        if (n->right) {
            deleteAll(n->right);
        }
        delete n;
    }

    // Add your own helper methods here
    KDNode* findFirstGuess(KDNode* node, Point& queryPoint,
                           unsigned int curDim) {
        KDNode* result = node;
        while (result != nullptr) {
            if (result->point.valueAt(curDim) <= queryPoint.valueAt(curDim)) {
                curDim = curDim + 1;
                result = result->left;
            } else {
                curDim = curDim + 1;
                result = result->right;
            }
            curDim = curDim % numDim;
        }
        return result;
    }
};
#endif  // KDT_HPP
