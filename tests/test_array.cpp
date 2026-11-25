#include "Array.h"
#include "gtest/gtest.h"

TEST(Array, Create_Object_With_Variadic) {
    Array<int, 5> array{5,5,5,5,5};

    ASSERT_EQ(5, array.size());
}

TEST(Array, Index_Operator) {
    Array<int, 5> array{1,2,3,4,5};
    const Array<std::string, 3> array2{"he", "ee", "ll"};

    ASSERT_EQ(3, array[2]);
    ASSERT_EQ("he", array2[0]);

    array[2] = 7;
    ASSERT_EQ(7, array[2]);
}

