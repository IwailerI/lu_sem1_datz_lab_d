/*
Andrejs Piroženoks, ap24069
Program created: 2024/09/12

D15. Create class "tetragon" containing 5 digits - 4 lengths of sides and 1
angle (value 1..179 degrees). The following class methods should be created: (1)
a constructor to initialize an object with given initial values, (2) destructor
which should notify about deleting the object, (3) method "change" with 5 given
parameters to add given parameter values to lengths of sides and angle, (4)
method "print" to print all length of sides and angle, (5) method "calculate" to
calculate type of tetragon: square, rectangle, rhombus, parallelogram or other.

*/

#include <iostream>

#include "tetragon.h"

void assert(bool condition) {
    if (!condition) {
        throw std::logic_error("assertion failed");
    }
}

int main() {
    try {
        Tetragon invalid(-12, 1, 1, 1, 90);
        assert(false);
    } catch (const std::exception& _) {
    }
    try {
        Tetragon invalid(1, 1, 0, 1, 90);
        assert(false);
    } catch (const std::exception& _) {
    }
    try {
        Tetragon invalid(1, 1, 1, 1, -90);
        assert(false);
    } catch (const std::exception& _) {
    }
    try {
        Tetragon invalid(1, 1, 1, 1, 180);
        assert(false);
    } catch (const std::exception& _) {
    }
    try {
        Tetragon invalid(100, 1, 1, 1, 90);
        assert(false);
    } catch (const std::exception& _) {
    }

    // Note: this quadrilateral is invalid, but invariant does not account for
    // it.
    Tetragon square(2, 1, 1, 1, 45);

    // make it a square
    square.change(-1, 0, 0, 0, 45);

    Tetragon rhombus(1, 1, 1, 1, 80);
    Tetragon rectangle(1, 2, 1, 2, 90);
    Tetragon parallelogram(1, 2, 1, 2, 10);
    Tetragon other(7.168, 9.110, 10.359, 3.381, 35.742);

    assert(square.calculate() == TetragonType::Square);
    assert(rhombus.calculate() == TetragonType::Rhombus);
    assert(rectangle.calculate() == TetragonType::Rectangle);
    assert(parallelogram.calculate() == TetragonType::Parallelogram);
    assert(other.calculate() == TetragonType::Other);

    square.print();
}
/*
Expected output:
[INFO] Tetragon at 0x<address> destroyed.
<Tetragon 1 1 1 1 angle: 90>
[INFO] Tetragon at 0x<address> destroyed.
[INFO] Tetragon at 0x<address> destroyed.
[INFO] Tetragon at 0x<address> destroyed.
[INFO] Tetragon at 0x<address> destroyed.
[INFO] Tetragon at 0x<address> destroyed.
*/