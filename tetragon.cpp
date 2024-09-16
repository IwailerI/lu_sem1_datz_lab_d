#include "tetragon.h"

#include <iostream>

void Tetragon::check_invariant() const {
    int a = _sides[0];
    int b = _sides[1];
    int c = _sides[2];
    int d = _sides[3];

    // note: floating point errors not handled
    bool valid =
        ((_angle >= 0.0 && _angle < 180.0)              // angle in range
         && (a > 0.0 && b > 0.0 && c > 0.0 && d > 0.0)  // sides in range
         && (a <= b + c + d && b <= a + c + d && c <= a + b + +d &&
             d <= a + b + c)  // sides are compatible
        );

    if (!valid) {
        throw std::logic_error(
            "Tetragon invariant violated: quadrilateral is invalid");
    }
}

Tetragon::Tetragon(double a, double b, double c, double d, double angle)
    : _angle(angle) {
    // _sides cannot be initialized in the initializer list, because program
    // needs to be portable

    _sides[0] = a;
    _sides[1] = b;
    _sides[2] = c;
    _sides[3] = d;

    check_invariant();
}

Tetragon::~Tetragon() {
    std::cout << "[INFO] Tetragon at " << this << " destroyed." << std::endl;
}

void Tetragon::change(double a, double b, double c, double d, double angle) {
    // we construct another instance, because in the event that invariant is
    // violated and an exception is thrown, we want to remain in the last valid
    // state
    auto next_state = Tetragon(_sides[0] + a, _sides[1] + b, _sides[2] + c,
                               _sides[3] + d, _angle + angle);

    next_state.check_invariant();

    *this = next_state;
}

std::ostream& operator<<(std::ostream& s, const Tetragon& t) {
    return s << "<Tetragon " << t._sides[0] << " " << t._sides[1] << " "
             << t._sides[2] << " " << t._sides[3] << " angle: " << t._angle
             << ">";
}

void Tetragon::print() const { std::cout << *this << std::endl; }

bool float_eq(double a, double b) {
    const double EPS = 1e-8;
    return std::abs(a - b) < EPS;
}

TetragonType Tetragon::calculate() const {
    if (!(float_eq(_sides[0], _sides[2]) && float_eq(_sides[1], _sides[3]))) {
        return TetragonType::Other;
    }

    bool sides_equal =
        float_eq(_sides[0], _sides[1]) && float_eq(_sides[2], _sides[3]);

    if (float_eq(_angle, 90)) {
        if (sides_equal) {
            return TetragonType::Square;
        } else {
            return TetragonType::Rectangle;
        }
    } else {
        if (sides_equal) {
            return TetragonType::Rhombus;
        } else {
            return TetragonType::Parallelogram;
        }
    }
}
