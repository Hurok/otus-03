#include "Utils.h"
#include "CLinkedVector.h"
#include "CCustomAllocator.h"
#include <boost/math/special_functions/factorials.hpp>

static constexpr auto kCountElements = 10;  // max 10 elements

int main(int, char**) {   
    try {
        // 1 - default allocator
        std::map<int, int> mapDefaultAllocator;
        for (int i = 0; i < kCountElements; ++i) {
            assert(i < boost::math::max_factorial<int>::value);
            mapDefaultAllocator.emplace(std::make_pair(i, static_cast<int>(boost::math::factorial<double>(i))));
        }

//        print(mapDefaultAllocator);

        // 2 - custom allocator
        std::map<int, int, std::less<int>, CCustomAllocator<std::pair<int, int> > > mapCustomAllocator;
        for (int i = 0; i < kCountElements; ++i) {
            assert(i < boost::math::max_factorial<int>::value);
            mapCustomAllocator.emplace(std::make_pair(i, static_cast<int>(boost::math::factorial<double>(i))));
        }

        print(mapCustomAllocator);
        return 0;

        // 3 - custom container
        CLinkedVector<int> customContainer;
        for (int i = 0; i < kCountElements; ++i) {
            customContainer.push_back(i);
        }

        print(customContainer);

        // 4 - custom container with custom allocator
        CLinkedVector<int, CCustomAllocator<int>, 1> customContainerAlloc;
        for (int i = 0; i < kCountElements; ++i) {
            customContainerAlloc.push_back(i);
        }

        print(customContainerAlloc);
        std::cout.flush();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
