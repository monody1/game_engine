//
// Created by Chen.Zr on 2020/3/22.
//

#include "gtest/gtest.h"
#include "allocator.hpp"

TEST(allorcator_test, basic_test){
    engine::Allocator allocator = engine::Allocator(3, 40, 1);
    for (int i = 0; i < 10; ++i) {
        auto p = allocator.Allocate();
        allocator.Free(p);
    }
}