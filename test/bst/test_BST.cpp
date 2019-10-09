#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}
TEST_F(SmallBSTFixture, SMALL_height_TEST) {
    // assert that the small BST has the correct height
    ASSERT_EQ(bst.height(), 2);
}
TEST_F(SmallBSTFixture, SMALL_empty_TEST) {
    // assert that the small BST is not empty
    ASSERT_EQ(bst.empty(), false);
}
TEST_F(SmallBSTFixture, SMALL_inorder_TEST) {
    // assert that the small BST is printed in correct order
    vector<int> result{-33, 1, 3, 4, 100};
    ASSERT_EQ(bst.inorder(), result);
}
TEST_F(SmallBSTFixture, SMALL_begin_TEST) {
    // assert that the small BST first element
    BSTIterator<int> iter(bst.find(1));
    iter = bst.begin();
    ASSERT_EQ(iter.operator*(), -33);
}
TEST_F(SmallBSTFixture, SMALL_find_TEST) {
    // assert that the small BST find element
    BSTIterator<int> iter(bst.find(100));
    ASSERT_EQ(iter.operator*(), 100);
    BSTIterator<int> last(bst.find(1));
    last = bst.find(200);
    ASSERT_EQ(last, nullptr);
}
TEST_F(SmallBSTFixture, SMALL_operator_TEST) {
    // check the two different operator
    BSTIterator<int> last(bst.find(1));
    BSTIterator<int> iter(bst.find(100));
    ASSERT_EQ(last.operator==(iter), false);
    ASSERT_EQ(last.operator!=(iter), true);
}