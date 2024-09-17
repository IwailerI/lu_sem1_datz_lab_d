#include "tests.h"

#include "tetragon.h"

void tests::UnitTests::add_test(std::function<void()> test) {
    _tests.push_back(test);
}

void tests::UnitTests::add_test_must_throw(std::function<void()> test) {
    _tests.push_back([=]() {
        try {
            test();
        } catch (const std::exception& e) {
            return;
        }
        throw std::logic_error("function did not throw");
    });
}

bool tests::UnitTests::run() {
    bool error = false;

    std::cerr << "Running " << _tests.size() << " tests.\n";

    for (unsigned i = 0; i < _tests.size(); i++) {
        try {
            _tests[i]();
        } catch (const std::exception& e) {
            std::cerr << "Test " << i << ": ERROR\n" << e.what() << std::endl;
            error = true;
            continue;
        }
        std::cerr << "Test " << i << ": ok" << std::endl;
    }

    return error;
}

void assert(bool condition) {
    if (condition) return;
    throw std::logic_error("assertion failed");
}

bool tests::run_tests() {
    UnitTests ut;

    ut.add_test_must_throw([]() {
        // negative length side
        Tetragon invalid(-12, 1, 1, 1, 90);
    });

    ut.add_test_must_throw([]() {
        // zero length side
        Tetragon invalid(1, 1, 0, 1, 90);
    });

    ut.add_test_must_throw([]() {
        // invalid angle
        Tetragon invalid(1, 1, 1, 1, -90);
    });

    ut.add_test_must_throw([]() {
        // invalid angle
        Tetragon invalid(1, 1, 1, 1, 180);
    });

    ut.add_test_must_throw([]() {
        // sides not compatible with each other
        Tetragon invalid(100, 1, 1, 1, 90);
    });

    ut.add_test_must_throw([]() {
        // constructed object is valid, but becomes invalid after operation
        Tetragon invalid(1, 1, 1, 1, 90);
        invalid.change(-1, 0, 0, 0, 0);
    });

    ut.add_test([]() {
        // each type works
        assert(Tetragon(1, 1, 1, 1, 90).calculate() == TetragonType::Square);
        assert(Tetragon(1, 1, 1, 1, 80).calculate() == TetragonType::Rhombus);
        assert(Tetragon(1, 2, 1, 2, 90).calculate() == TetragonType::Rectangle);
        assert(Tetragon(1, 2, 1, 2, 10).calculate() ==
               TetragonType::Parallelogram);
        assert(Tetragon(7.168, 9.110, 10.359, 3.381, 35.742).calculate() ==
               TetragonType::Other);
    });

    ut.add_test([]() {
        // change works
        Tetragon square(2, 1, 1, 1, 45);
        square.change(-1, 0, 0, 0, 45);
        assert(square.calculate() == TetragonType::Square);
    });

    return ut.run();
}
