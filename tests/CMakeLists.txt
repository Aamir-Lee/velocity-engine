add_executable(velocity_tests
        unit/test_types.cpp
        unit/test_orders.cpp
)

target_link_libraries(velocity_tests PRIVATE
        velocity_types
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(velocity_tests)