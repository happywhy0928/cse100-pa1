#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;
    vector<Point> vec1;
    KDT kdt1;
    vector<Point> vec2;
    KDT kdt2;
    vector<Point> vec3;
    KDT kdt3;

  public:
    SmallKDTFixture() {
        vec.emplace_back(Point({1.0, 3.2}));
        vec.emplace_back(Point({3.2, 1.0}));
        vec.emplace_back(Point({5.7, 3.2}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
        kdt.build(vec);
        vec1.emplace_back(Point({1.0, 3.2, 1}));
        vec1.emplace_back(Point({3.2, 1.0, 2}));
        vec1.emplace_back(Point({5.7, 3.2, 3}));
        vec1.emplace_back(Point({1.8, 1.9, 4}));
        vec1.emplace_back(Point({4.4, 2.2, 5}));
        kdt1.build(vec1);
        vec2.emplace_back(Point({2.0, 6.0, 6.0}));
        vec2.emplace_back(Point({2.0, 7.0, 2.0}));
        vec2.emplace_back(Point({3.0, 3.0, 3.0}));
        vec2.emplace_back(Point({4.0, 4.0, 4.0}));
        vec2.emplace_back(Point({5.0, 5.0, 5.0}));
        vec2.emplace_back(Point({6.0, 6.0, 6.0}));
        vec2.emplace_back(Point({0.0, 0.0, 0.0}));
        kdt2.build(vec2);
        vec3.emplace_back(Point({2.0, 3.0}));
        vec3.emplace_back(Point({4.0, 9.0}));
        vec3.emplace_back(Point({6.0, 4.0}));
        vec3.emplace_back(Point({7.0, 2.0}));
        vec3.emplace_back(Point({8.0, 1.0}));
        vec3.emplace_back(Point({9.0, 6.0}));
        kdt3.build(vec3);
    }
};
TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 5);
}
TEST_F(SmallKDTFixture, TEST_height) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.height(), 2);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}

TEST_F(SmallKDTFixture, TEST_SIZE1) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt1.size(), 5);
}
TEST_F(SmallKDTFixture, TEST_height1) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt1.height(), 2);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT1) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec1);
    Point queryPoint({5.81, 3.21, 2});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt1.findNearestNeighbor(queryPoint), *closestPoint);
}
TEST_F(SmallKDTFixture, TEST_SIZE2) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt2.size(), 7);
}
TEST_F(SmallKDTFixture, TEST_height2) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt2.height(), 2);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT2) {
    // check the three dimension tree to find nearest neighbor
    NaiveSearch naiveSearch;
    naiveSearch.build(vec2);
    Point queryPoint({6.2, 6.2, 6.2});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt2.findNearestNeighbor(queryPoint), *closestPoint);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT3) {
    // check the two dimension tree to find nearest neighbor
    NaiveSearch naiveSearch;
    naiveSearch.build(vec3);
    Point queryPoint({1.0, 4.0});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    std::cout << *kdt3.findNearestNeighbor(queryPoint) << "/n";
    ASSERT_EQ(*kdt3.findNearestNeighbor(queryPoint), *closestPoint);
}
