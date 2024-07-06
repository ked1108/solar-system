include(AddGoogleTest)

add_executable(
        unit_tests
        test_planet.cpp
)
target_link_libraries(
        unit_tests PRIVATE system raylib GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)