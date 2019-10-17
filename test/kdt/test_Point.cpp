#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

TEST(PointTests, TEST_EQUALS) {
    vector<double> p1Values{3, 4, 5, 6};
    Point p1(p1Values);

    vector<double> p2Values{3, 4, 5};
    Point p2(p2Values);

    ASSERT_NE(p1, p2);
}

TEST(PointTests, TEST_DISTANCE) {
    vector<double> p1Values{3, 4, 5, 6};
    vector<double> p2Values{3, 4, 5, 7};

    Point p1(p1Values);
    Point p2(p2Values);

    p1.setDistToQuery(p2);
    ASSERT_DOUBLE_EQ(p1.distToQuery, 1.0);
    double check1 = p1.valueAt(0);
    ASSERT_DOUBLE_EQ(check1, 3.0);
    bool check2 = p1.operator==(p2);
    ASSERT_EQ(check2, false);
    bool check3 = p1.operator!=(p2);
    ASSERT_EQ(check3, true);
}