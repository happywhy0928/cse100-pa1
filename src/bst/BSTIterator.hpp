#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /** Constructor that initialize the current BSTNode
     *  in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->data; }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /**
     * equality test operator.
     * Return: true(1) if equal / false(0) if inequal
     */
    bool operator==(BSTIterator<Data> const& other) const {
        return curr == other.curr;
    }

    /**
     * inequality test operatior.
     * Return: true(1) if inequal/ false(0) if equal
     */
    bool operator!=(BSTIterator<Data> const& other) const {
        return curr != other.curr;
    }
};

#endif  // BSTITERATOR_HPP
