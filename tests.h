#ifndef TESTS_CPP
#define TESTS_CPP

#include <functional>
#include <iostream>
#include <vector>

namespace tests {

/// @brief Ad-hoc testing framework.
class UnitTests {
    std::vector<std::function<void()>> _tests;

   public:
    /// @brief Adds a new test, which must not throw to succeed.
    /// @param test Function that will be called as the test.
    void add_test(std::function<void()> test);

    /// @brief Adds a new test, which must throw to succeed.
    /// @param test Function that will be called as the test.
    void add_test_must_throw(std::function<void()> test);

    /// @brief Runs the testing protocol, printing a summary to standard error.
    /// @return Reports whether some test failed.
    bool run();
};

bool run_tests();

}  // namespace tests

#endif