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
        isize = 0;
        numDim = points[0].numDim;
        root = nullptr;
        iheight = -1;
        root = buildSubtree(points, 0, points.size(), 0, 0);
        //   std::cout << root->point.features << "/n";
        //   std::cout << root->left->point.features << "/n";
        //   std::cout << root->right->point.features << "/n";
        //   std::cout << root->left->right->point.features << "/n";
        //   std::cout << root->right->right->point.features << "/n";
        //   if (!root->right->right->right->point.features.empty()) {
        //       std::cout << "abc";
        //   }
        // KDNode* curr = root;
        // while (curr) {
        //     std::cout << curr->point.features << "/n";
        //    if (curr->left) {
        //       std::cout << curr->left->point.features << "/l";
        //   }
        //     if (curr->right) {
        //         std::cout << curr->right->point.features << "/r        ";
        //     }
        //     curr = curr->left;
        // }
        // curr = root;
        //   while (curr) {
        ///      std::cout << curr->point.features << "/n";
        //       if (curr->left) {
        //          std::cout << curr->left->point.features << "/l";
        //      }
        //      if (curr->right) {
        //           std::cout << curr->right->point.features << "/r";
        //       }
        //     curr = curr->right;
        //  }
        threshold = 99999;
        nearestNeighbor = root->point;
        isize = points.size();
    }

    /**
     *
     */
    Point* findNearestNeighbor(Point& queryPoint) {
        if (root == nullptr) {
            return nullptr;
        }
        KDNode* curr = root;
        //  KDNode* abC = root;
        //  while (abC) {
        //      std::cout << abC->point.features << "/n";
        //     if (abC->left) {
        //         std::cout << abC->left->point.features << "/l";
        //     }
        //     if (abC->right) {
        //         std::cout << abC->right->point.features << "/r        ";
        //     }
        //     abC = abC->left;
        //  }
        threshold = 99999;
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
    /**
     *
     */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start >= end) {
            return nullptr;
        }
        CompareValueAt comp(curDim);
        vector<Point>::iterator it = points.begin();
        sort(it + start, it + end, comp);
        int mid = (start + end - 1) / 2;
        KDNode* curr = new KDNode(points[mid]);
        vector<double> x = curr->point.features;
        numDim = points[0].numDim;
        if (end - start > 1) {
            curDim = curDim + 1;
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

    /**
     *
     */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        // KDNode * temp = findFirstGuess(root,queryPoint,0);
        if (!node) {
            return;
        }
        KDNode* curr = node;
        //       queryPoint.setDistToQuery(node->point);
        threshold = queryPoint.distToQuery;
        //        std::cout << curr->point.features << "/num";
        double squareDistance =
            pow(curr->point.valueAt(curDim) - queryPoint.valueAt(curDim), 2.0);
        if (squareDistance <= threshold) {
            if (curr->left != nullptr) {
                curDim = curDim + 1;
                curDim = curDim % numDim;
                findNNHelper(curr->left, queryPoint, curDim);
            }
            if (curr->right != nullptr) {
                curDim = curDim + 1;
                curDim = curDim % numDim;
                findNNHelper(curr->right, queryPoint, curDim);
            }
            curr->point.setDistToQuery(queryPoint);
            double check = curr->point.distToQuery;
            // std::cout << check << "/num";
            if (check <= threshold) {
                nearestNeighbor = curr->point;
                threshold = check;
                queryPoint.setDistToQuery(curr->point);
            }
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /**
     *
     */
    static void deleteAll(KDNode* n) {
        if (n == nullptr) {
            return;
        }
        //  if (n->left) {
        //   deleteAll(n->left);
        //   }
        //  if (n->right) {
        //      deleteAll(n->right);
        //   }
        delete n;
    }
};
#endif  // KDT_HPP
