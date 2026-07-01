#pragma once

template <int DIMENSIONS>
class Vector{
    public:
    // Vector hadamard(const Vector& other);
    double squaredMagnitude();
    Vector operator*(double other);
    Vector operator-=(const Vector& other);
    double data[DIMENSIONS];
    void print();
};

#include "vector.cpp"