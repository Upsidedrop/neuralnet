#include "Vector.hpp"

template <int DIMENSIONS>
Vector<DIMENSIONS> Vector<DIMENSIONS>::hadamard(const Vector& other){
    Vector<DIMENSIONS> res;
    for(int i = 0; i < DIMENSIONS; ++i){
        res.data[i] = data[i] * other.data[i];
    }
    return res;
}
template <int DIMENSIONS>
double Vector<DIMENSIONS>::squaredMagnitude(){
    double res = 0;
    for(int i = 0; i < DIMENSIONS; ++i){
        res += data[i] * data[i];
    }
    return res;
}
template <int DIMENSIONS>
Vector<DIMENSIONS> Vector<DIMENSIONS>::operator*(double other){
    Vector<DIMENSIONS> res;
    for(int i = 0; i < DIMENSIONS; ++i){
        res.data[i] = data[i] * other;
    }
    return res;
}
template <int DIMENSIONS>
Vector<DIMENSIONS> Vector<DIMENSIONS>::operator-=(const Vector& other){
    for(int i = 0; i < DIMENSIONS; ++i){
        data[i] -= other.data[i];
    }
    return *this;
}
template <int DIMENSIONS>
void Vector<DIMENSIONS>::print(){
    std::cout << "[";
    for(int i = 0; i < DIMENSIONS - 1; ++i){
        std::cout << data[i] << ", ";
    }
    std::cout << data[DIMENSIONS - 1] << "]\n";
}