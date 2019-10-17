#ifndef KDT_HPP
#define KDT_HPP

#include <bits/stdc++.h>
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
     * Parameter: a list of points to build the tree
     *            (assume each point has same dimension)
     */
    void build(vector<Point>& points) {
        // check if the given vector is empty or not
        if (points.size() == 0) {
            return;
        }
        // initialize the variable
        isize = 0;
        numDim = points[0].numDim;
        root = nullptr;
        iheight = -1;
        root = buildSubtree(points, 0, points.size(), 0, 0);
        nearestNeighbor = root->point;
        isize = points.size();
    }

    /**
     *this method traverse through the tree to find the nearest point in the
     *tree regard to the give parameter(querPoint) Parameter: the point to
     *search the neighbor. we could using the variable inside this parameter
     *(distToQuery) to compare with the threshold to update the threshold
     * Return: return a pointer to the nearest neighbor in the tree regard to
     *the point give by the parameter
     */
    Point* findNearestNeighbor(Point& queryPoint) {
        // check if the tree is empty or not
        if (root == nullptr) {
            return nullptr;
        }
        KDNode* curr = root;
        // initialize the threshold each time for method call to compare
        threshold = INT_MAX;
        queryPoint.setDistToQuery(curr->point);
        findNNHelper(curr, queryPoint, 0);
        Point* result = &nearestNeighbor;
        if (result != nullptr) {
            return result;
        } else {
            return nullptr;
        }
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /**
     * get the number of items currently in the current KDT
     * Return: unsigned integer of currently number of elements
     */
    unsigned int size() const { return isize; }

    /**
     * get the currently height of the current KDT
     * Return: integer of currently height of tree
     */
    int height() const { return iheight; }

  private:
    /**
     *the method using the give parameter build the tree recursively
     * First, check if there remain points in the parameter to continue building
     *the tree Second, sort the points in the order of current dimension Third,
     *get the mid point in these points in order to build the curr node in tree
     * Finally, if there are any other points, then divide the remaining points
     *into two parts and using indexes of these points as parameter to continue
     *build the subtree by call the method again (recursively) Return: the first
     *node of subtree with entire subtree for this node Parameter:
     * vector<Point>& points : the points to build the subtree
     * unsigned int start: to indicate where to start in these points
     *(inclusive) unsigned int start: to indicate where to end in the these
     *points (exclusive) curDim: the curDim of the first node of the subtree to
     *build height: to check the height of the current subtree.
     */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start >= end) {
            return nullptr;
        }
        curDim = curDim % numDim;
        // start to sort the given points by the indexes by the  start and end
        CompareValueAt comp(curDim);
        vector<Point>::iterator it = points.begin();
        sort(it + start, it + end, comp);
        // set the mid point in the sorting points as current node and continue
        // to build subtree if there are any other points
        int mid = floor((start + end) / 2);
        KDNode* curr = new KDNode(points[mid]);
        // initialize the new build KDNode
        curr->left = nullptr;
        curr->right = nullptr;
        // get the number of dimension in these points (since all are equal)
        numDim = points[0].numDim;
        // check if there are other points remaining to build
        if (end - start > 1) {
            // curDim = curDim % numDim;
            height = height + 1;
            // continue to build the remain points
            curr->left =
                buildSubtree(points, start, mid, (curDim + 1) % numDim, height);
            curr->right = buildSubtree(points, mid + 1, end,
                                       (curDim + 1) % numDim, height);
        }
        // check the current height of kdt and update
        if (iheight < height) {
            iheight = height;
        }
        // return the build node with subtree
        return curr;
    }

    /**
     * the method find the nearest neighbor point existed in the parameter
     * node's subtree Firstly, we set the node as the first potential nearest
     * neighbor and then check if the square distance between the current
     * dimension value compared with the threshold if the square distance is
     * smaller than the threshold, then continue to check its child if exists
     * (different method to the discussion)
     * by searching down to the leaf, check the square distance for all
     * dimension and compare with the threshold and update the threshold
     * Parameter:
     * KDNode* node: the node with subtree to start search the nearest neighbor
     * Point& queryPoint: the point for searching nearest point
     * unsigned int curDim: the current dimension of node in the current kdt
     * Return: return nothing but update the threshold until to the
     * smallestdistance to the object point Besides, the method nearestNeighbor
     * check the distance compared to the threshold and update new canditate to
     * the nearestNeighbor. After the method call, the nearestNeighbor is
     * already set to the nearest neighbor.
     */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        KDNode* curr = node;
        curDim = curDim % numDim;
        // first check the square distance in the current dimension and compare
        // with threshold to see continue or not
        double squareDistance =
            pow(curr->point.valueAt(curDim) - queryPoint.valueAt(curDim), 2.0);
        if (squareDistance <= threshold) {
                        curr->point.setDistToQuery(queryPoint);
            double check = curr->point.distToQuery;
            if (check <= threshold) {
                nearestNeighbor = curr->point;
                threshold = check;
            }
            // if smaller, then check its child recursively
            if (curr->left != nullptr) {
                //  curDim = curDim % numDim;
                findNNHelper(curr->left, queryPoint, (curDim + 1) % numDim);
            }
            if (curr->right != nullptr) {
                // curDim = curDim % numDim;
                findNNHelper(curr->right, queryPoint, (curDim + 1) % numDim);
            }
            // check the current square distance in all dimension
            // then compare with the threshold to check update or not
           // curr->point.setDistToQuery(queryPoint);
           // double check = curr->point.distToQuery;
           // if (check <= threshold) {
           //     nearestNeighbor = curr->point;
           //     threshold = check;
          //  }
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /**
     * the method delete all the node in the subtree staring from the parameter
     * node Parameter: KDNode* n : the starting point of the subtree to delete
     */
    static void deleteAll(KDNode* n) {
        // check if the current node is existed or not
        if (n == nullptr) {
            return;
        }
        // first recursively delete all its children
        if (n->left) {
            deleteAll(n->left);
        }
        if (n->right) {
            deleteAll(n->right);
        }
        // finally delete itself
        delete n;
    }
};
#endif  // KDT_HPP
