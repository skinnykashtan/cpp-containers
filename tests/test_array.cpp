#include "Array.h"
#include "gtest/gtest.h"

TEST(Array, Create_Object_With_Variadic) {
    Array<int, 5> array{5,5,5,5,5};

    ASSERT_EQ(5, array.size());
}
