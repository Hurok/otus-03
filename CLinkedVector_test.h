#include <gtest/gtest.h>
#include "CLinkedVector.h"

template <typename Allocator = std::allocator<int> >
inline void fill(CLinkedVector<int, Allocator> &inOut, std::size_t count) {
    for (std::size_t i = 0; i < count; i++) {
        inOut.push_back(i);
    }
}

TEST(LinkedVector, clear) {
    CLinkedVector<int> vec;
    fill(vec, 5);
    EXPECT_EQ(vec.size(), 5);

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);
}

TEST(LinkedVector, empty) {
    CLinkedVector<int> vec;
    EXPECT_EQ(vec.empty(), true);

    vec.reserve(10);
    EXPECT_EQ(vec.empty(), true);

    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);

    fill(vec, 5);
    EXPECT_EQ(vec.empty(), false);
    vec.reserve(10);
    EXPECT_EQ(vec.empty(), false);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.empty(), false);

    vec.clear();
    EXPECT_EQ(vec.empty(), true);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.empty(), true);
}

TEST(LinkedVector, size) {
    CLinkedVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    vec.reserve(10);
    EXPECT_EQ(vec.size(), 0);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 0);

    fill(vec, 5);
    EXPECT_EQ(vec.size(), 5);
    vec.reserve(10);
    EXPECT_EQ(vec.size(), 5);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 5);

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 0);
}

TEST(LinkedVector, at) {
    // int
    {
        CLinkedVector<int> vec;
        for (auto i = 0; i < 5; i++) {
            vec.push_back(i);
            EXPECT_EQ(vec.at(i), i);
        }
    }

    // string
    {
        CLinkedVector<std::string> vec;
        for (auto i = 0; i < 5; i++) {
            const auto val = std::to_string(i + i);
            vec.push_back(val);
            EXPECT_EQ(vec.at(i), val);
        }
    }
}

TEST(LinkedVector, capacity) {
    CLinkedVector<int> vec;
    vec.reserve(10);
    EXPECT_EQ(vec.capacity(), 10);

    fill(vec, 5);
    EXPECT_EQ(vec.capacity(), 10);

    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), 5);

    vec.clear();
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(LinkedVector, shrink_to_fit) {
    CLinkedVector<int> vec;
    EXPECT_EQ(vec.capacity(), 0);
    vec.reserve(10);
    EXPECT_EQ(vec.capacity(), 10);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), 0);

    fill(vec, 5);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(LinkedVector, push_back) {
    CLinkedVector<int> vec;
    for (auto i = 0; i < 10; i++) {
        vec.push_back(i);
        EXPECT_EQ(vec.size(), i + 1);
    }
}

TEST(LinkedVector, reserve) {
    CLinkedVector<int> vec;
    vec.reserve(10);

    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);

    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);

    vec.reserve(5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);

    vec.clear();
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);
}
