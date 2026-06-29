#pragma once

template <int DIMENSIONS, int DEGREES>
class Dual{
    public:
    Dual(){};
    Dual(double initValue);
    Dual(double p_values[DIMENSIONS][DEGREES], double p_real);
    Dual operator=(const Dual& other);
    Dual(const Dual& other);
    Dual operator=(Dual&& other);
    Dual(Dual&& other);
    Dual operator*(double other);
    Dual operator*(const Dual& other);
    Dual operator+(const Dual& other);
    Dual operator+=(const Dual& other);
    Dual operator+(double other);
    Dual exp();
    Dual pow(int num);
    Dual ln();
    void print();
    double derivatives[DIMENSIONS][DEGREES];
    double real;
};

#include "dualnumber.cpp"