enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(
  my_test
  tests.cpp
)
target_link_libraries(
  my_test
  PRIVATE rs_task Gtest::gtest_main
)

add_test(
  NAME my_test
  COMMAND my_test
)

include(GoogleTest)
gtest_discover_tests(my_test)