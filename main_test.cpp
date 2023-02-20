#include "CLinkedVector_test.h"
#include "CCustomAllocator_test.h"
#include <boost/math/special_functions/factorials.hpp>
#include <map>

TEST(Main, MapInit) {
    std::map<int, int> container;
    const auto size = 10;
    for (auto i = 0; i < size; i++) {
        auto k = i;
        auto v = static_cast<int>(boost::math::factorial<double>(i));
        container.emplace(std::make_pair(k, v));

        EXPECT_EQ(container.size(), i + 1);
        auto it = container.find(k);
        EXPECT_EQ(it == container.cend(), false);
        EXPECT_EQ(it->first, k);
        EXPECT_EQ(it->second, v);
    }

    EXPECT_EQ(container.size(), size);
}

TEST(Main, MapInitCustomAllocator) {
    std::map<int, int, std::less<int>, CCustomAllocator<std::pair<int, int> > > container;
    const auto size = 10;
    for (auto i = 0; i < size; i++) {
        auto k = i;
        auto v = static_cast<int>(boost::math::factorial<double>(i));
        container.emplace(std::make_pair(k, v));

        EXPECT_EQ(container.size(), i + 1);
        auto it = container.find(k);
        EXPECT_EQ(it == container.cend(), false);
        EXPECT_EQ(it->first, k);
        EXPECT_EQ(it->second, v);
    }

    EXPECT_EQ(container.size(), size);
}

TEST(Main, LinkedVectorInit) {
    CLinkedVector<int> container;
    const auto size = 10;
    for (auto i = 0; i < size; i++) {
        container.push_back(i);
        EXPECT_EQ(container.size(), i/* + 1*/);
        EXPECT_EQ(container.at(i), i);
    }

    EXPECT_EQ(container.size(), size);
}


TEST(Main, LinkedVectorInitCustomAllocator) {
    CLinkedVector<int, CCustomAllocator<int> > container;
    const auto size = 10;
    for (auto i = 0; i < size; i++) {
        container.push_back(i);
        EXPECT_EQ(container.size(), i + 1);
        EXPECT_EQ(container.at(i), i);
    }

    EXPECT_EQ(container.size(), size);
}
