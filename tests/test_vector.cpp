#include <gtest/gtest.h>
#include <Vector.h>
#include <string>

namespace {
    struct CopyOnReAlloc {
        inline static int copyCounter = 0;
        inline static int moveCounter = 0;

        CopyOnReAlloc() = default;

        CopyOnReAlloc(CopyOnReAlloc&&) {
            moveCounter++;
        }

        CopyOnReAlloc(const CopyOnReAlloc&) {
            copyCounter++;
        }
    };

    struct MoveOnReAlloc {
        inline static int copyCounter = 0;
        inline static int moveCounter = 0;

        MoveOnReAlloc() = default;

        MoveOnReAlloc(MoveOnReAlloc&&) noexcept {
            moveCounter++;
        }

        MoveOnReAlloc(const MoveOnReAlloc&) {
            copyCounter++;
        }
    };
}

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

TEST(Vector, PushBack_Fills_Initial_Capacity) {
    Vector<int> vector;

    vector.PushBack(5);
    ASSERT_EQ(1, vector.Size());
    EXPECT_EQ(5, vector[0]);
    EXPECT_FALSE(vector.empty());

    vector.PushBack(6);
    ASSERT_EQ(2, vector.Size());
    EXPECT_EQ(5, vector[0]);
    EXPECT_EQ(6, vector[1]);
}

TEST(Vector, PushBack_Fills_Int_ReAlloc_Capacity) {
    Vector<int> vector;

    vector.PushBack(5);
    vector.PushBack(6);
    vector.PushBack(7);

    ASSERT_EQ(3, vector.Size());
    EXPECT_EQ(5, vector[0]);
    EXPECT_EQ(6, vector[1]);
    EXPECT_EQ(7, vector[2]);
}

TEST(Vector, PushBack_Fills_String_ReAlloc_Capacity) {
    Vector<std::string> vector;

    vector.PushBack("s1");
    vector.PushBack("s2");
    vector.PushBack("s3");

    ASSERT_EQ(3, vector.Size());
    EXPECT_EQ("s1", vector[0]);
    EXPECT_EQ("s2", vector[1]);
    EXPECT_EQ("s3", vector[2]);
}

TEST(Vector, ReAlloc_Copies_When_Move_Is_Not_Noexcept) {
    CopyOnReAlloc::copyCounter = 0;
    CopyOnReAlloc::moveCounter = 0;

    Vector<CopyOnReAlloc> vector;
    CopyOnReAlloc obj1;
    CopyOnReAlloc obj2;
    CopyOnReAlloc obj3;

    vector.PushBack(obj1);
    vector.PushBack(obj2);
    vector.PushBack(obj3);

    ASSERT_EQ(3, vector.Size());
    EXPECT_EQ(5, CopyOnReAlloc::copyCounter);
    EXPECT_EQ(0, CopyOnReAlloc::moveCounter);
}

TEST(Vector, ReAlloc_Moves_When_Move_Is_Noexcept) {
    MoveOnReAlloc::copyCounter = 0;
    MoveOnReAlloc::moveCounter = 0;

    Vector<MoveOnReAlloc> vector;
    MoveOnReAlloc obj1;
    MoveOnReAlloc obj2;
    MoveOnReAlloc obj3;

    vector.PushBack(obj1);
    vector.PushBack(obj2);
    vector.PushBack(obj3);

    ASSERT_EQ(3, vector.Size());
    EXPECT_EQ(3, MoveOnReAlloc::copyCounter);
    EXPECT_EQ(2, MoveOnReAlloc::moveCounter);
}



