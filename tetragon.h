#ifndef TETRAGON_H
#define TETRAGON_H

#include <ostream>

/// @brief Class enum representing possible variants of a tetragon.
enum class TetragonType {
    Square,
    Rectangle,
    Rhombus,
    Parallelogram,
    Other,
};

/// @brief Class representing a quadrilateral.
class Tetragon {
    friend std::ostream& operator<<(std::ostream& s, const Tetragon& t);

    double _sides[4];
    double _angle;

    /// @brief Checks whether the tetragon is valid and throws an exception
    /// if it is not.
    void check_invariant() const;

   public:
    /// @brief Constructs a new tetragon.
    /// @param a side length 1
    /// @param b side length 2
    /// @param c side length 3
    /// @param d side length 4
    /// @param angle angle between some 2 sides (in degrees)
    /// @throws if provided lengths are impossible or angle is out of range
    Tetragon(double a, double b, double c, double d, double angle);
    ~Tetragon();

    /// @brief Adds specified values to each side and angle.
    void change(double a, double b, double c, double d, double angle);

    /// @brief Outputs all sides lengths and angle to the standart output and
    /// flushed the stream.
    void print() const;

    /// @brief Determines the type of this tetragon.
    TetragonType calculate() const;
};

std::ostream& operator<<(std::ostream& s, const Tetragon& t);

#endif