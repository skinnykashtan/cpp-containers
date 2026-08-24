#include <gtest/gtest.h>
#include <Vector.h>

TEST(Vector, Create_Object_With_Default) {
    Vector<int> vector;

    ASSERT_TRUE(vector.empty());
}

TEST(Vector, Create_Object_With_Initializer_List) {
    Vector<int> vector{1,2,5,6};

    EXPECT_FALSE(vector.empty());
    ASSERT_EQ(4, vector.Size());

    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
    EXPECT_EQ(5, vector[2]);
    EXPECT_EQ(6, vector[3]);
}

