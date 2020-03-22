#add_executable(allocator_test)
#add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest-master)

add_executable(allocator_test)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#message(${gtest_SOURCE_DIR})

target_sources(
        allocator_test
        PRIVATE
        allocator_test.cpp
)

target_link_libraries(
        allocator_test
        gtest gtest_main common
)