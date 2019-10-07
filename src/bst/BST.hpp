#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /**
     * Frees all memory allocated by the BST
     */
    virtual ~BST() { deleteAll(root); }

    /**
     * insert a Data item to BST
     * Return:
     * true if the item successful added to this BST
     * false if an item equal to this one already in BST
     * no duplicate insertion
     * In addition: the function only use "<" operator when
     * comparing
     *
     * Parameter:
     * the new item to form a Node to insert the BST
     */
    virtual bool insert(const Data& item) {
        // check root is empty or not
        if (!root) {
            root = new BSTNode<Data>(item);
            isize++;
            iheight = 0;
            return 1;
        }

        // initialize pointer to root to start
        BSTNode<Data>* current = root;
        BSTNode<Data>* prev = nullptr;

        int numOfHeight = 0;

        // start the travse
        while (current != 0) {
            // if the data is smaller than the current, go left
            if (item < current->data) {
                prev = current;
                current = current->left;
                numOfHeight++;
            }

            // if the data is larger than the current, go right
            else if (current->data < item) {
                prev = current;
                current = current->right;
                numOfHeight++;
            } else {
                return 0;
            }
        }
        // smaller than previous, then go left
        if (item < prev->data) {
            current = prev->left = new BSTNode<Data>(item);
            current->parent = prev;
            if (!prev->right) {
                numOfHeight++;
            }
        }
        // if larger than previous, then go right
        else {
            current = prev->right = new BSTNode<Data>(item);
            current->parent = prev;
            if (!prev->left) {
                numOfHeight++;
            }
        }
        // if the number of Height is larger than the previous height
        // then set the numOfHeight as new height
        if (iheight < numOfHeight) {
            iheight = numOfHeight;
        }
        isize++;
        return 1;
    }
    /**
     * Search the BST for the given item existed or not
     * This function only use "<" as an operator when comparing
     * Parameter:
     * the item to search for the existence in the BST
     * Return:
     * return an iterator pointing to the given item if found
     * pointing past the last node in the BST if not found
     */
    virtual iterator find(const Data& item) const {
        if (empty()) {
            return 0;
        }

        BSTNode<Data>* current = root;
        // start the while loop of search
        while (current) {
            // if less than the current data, then search left part
            if (item < current->data) {
                current = current->left;
            }
            // if larger than the current data, then search right part
            if (current->data < item) {
                current = current->right;
            }
            // we found the equal data
            else {
                return typename BST<Data>::iterator(current);
            }
        }
        return end();
    }

    /**
     * return the number of element in the BST
     */
    unsigned int size() const { return isize; }

    /**
     * return the height of the BST
     * note: empty BST has height -1;
     *       BST with only one node has height 0;
     */
    int height() const { return iheight; }

    /**
     * check if the BST is empty or not
     * Return:
     * return true if BST is empty
     * return false if BST is not empty
     */
    bool empty() const { return isize == 0; }

    /**
     * Return an iterator pointing to the first item in BST
     * (the smallest element in current BST)
     */
    iterator begin() const { return typename BST<Data>::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /**
     * print the element in BST in ascending order
     */
    vector<Data> inorder() const { return inorder(root); }

  private:
    /**
     * find the first node in the BST which is the smallest
     * element in the BST ( in the leftmost part of tree)
     */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* current = root;
        if (!current) {
            return 0;
        }
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    /**
     * First we check if the current node is null,return void;
     * then we recursively delete left sub-tree;
     * then we recursively delete right sub-tree;
     * finally, we delete current node.
     */
    static void deleteAll(BSTNode<Data>* n) {
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
    vector<Data> inorder(BSTNode<Data>* n) const {
        BSTNode<Data>* current = n;
        if (current->left) {
            inorder(current->left);
        }
        vector<Data> result;
        result.push_back(current->data);
        if (current->right) {
            inorder(current->right);
        }
        return result;
    }
};

#endif  // BST_HPP
