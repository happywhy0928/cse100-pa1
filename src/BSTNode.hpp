#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /**
     * Constructor that initialize a BSTNode with given data
     * with no parent and no children
     */
    BSTNode(const Data& d) : data(d) { parent = left = right = nullptr; }

    /**
     * Find the successor of this BSTNode ,
     * the successor of the node is the next larger data (in ascending
     * order) of the node
     *
     * Return:
     * the BSTNode that is the successor of this BSTNode, or nullptr
     * if there is no successor.
     */
    BSTNode<Data>* successor() {
        BSTNode<Data>* current = this;

        // Case1: curr has a right child
        if (current->right) {
            current = current->right;

            // find the smallest node in curr's right subtree
            while (current->left) {
                current = current->left;
            }
            return current;
        }
        // Case2: curr does not have a right child
        else {
            current = current->parent;
            while (current) {
                // traverse up until current node is its current's left child
                if (current->left == this) {
                    return current;
                }
                current = current->parent;
                if (current) {
                    if (this->data < current->data) {
                        return current;
                    }
                }
            }
        }
        return nullptr;
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
