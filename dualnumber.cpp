#include "DualNumber.hpp"

#include "math.h"

template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator*(const Dual<DIMENSIONS, DEGREES>& other){
    Dual<DIMENSIONS, DEGREES> res;
    res.real = other.real * real;
    for(int i = 0; i < DIMENSIONS; ++i){
        for(int j = 0; j < DEGREES; ++j){
            res.derivatives[i][j] += other.real * derivatives[i][j];
            for(int k = j; k < DEGREES; ++k){
                if(k == j){
                    res.derivatives[i][k] += real * other.derivatives[i][j];
                    continue;
                }
                res.derivatives[i][k] += derivatives[i][k-1] * other.derivatives[i][j];
            }
        }
    }
    return res;
}
template <int DIMENSIONS, int DEGREES>
void Dual<DIMENSIONS, DEGREES>::print(){
    std::cout << real << "\n";
    for(int i = 0; i < DIMENSIONS; ++i){
        for(int j = 0; j < DEGREES; ++j){
            std::cout << derivatives[i][j] << "ε^" << j + 1 << "_" << i + 1 << ", ";
        }
        std::cout << "\n";
    }
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES>::Dual(double p_values[DIMENSIONS][DEGREES], double p_real){
    for(int i = 0; i < DIMENSIONS; ++i){
        for(int j = 0; j < DEGREES; ++j){
            derivatives[i][j] = p_values[i][j];
        }
    }
    real = p_real;
}
uint factorial(int n) {
    if (n < 0) return 0;
    
    uint result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::exp(){
    Dual<DIMENSIONS, DEGREES> res;
    double oldReal = real;
    res = *this;
    real = 0;
    for(int i = 1; i < DEGREES; ++i){
        res = res + this -> pow(i + 1) * (1/(double)factorial(i+1));
    }
    res.real = 1;
    real = oldReal;
    res = res * std::exp(real);
    return res;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator*(double other){
    Dual<DIMENSIONS, DEGREES> res = *this;
    res.real *= other;
    for(int i = 0; i < DIMENSIONS; ++i){
        for(int j = 0; j < DEGREES; ++j){
            res.derivatives[i][j] *= other;
        }
    }
    return res;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator+(const Dual& other){
    Dual<DIMENSIONS, DEGREES> res;
    res.real = real + other.real;
    for(int i = 0; i < DIMENSIONS; ++i){
        for(int j = 0; j < DEGREES; ++j){
            res.derivatives[i][j] = derivatives[i][j] + other.derivatives[i][j];
        }
    }
    return res;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::pow(int num){
    Dual<DIMENSIONS, DEGREES> res = *this;
    for(int i = 1; i < num; ++i){
        res = *this * res;
    }
    return res;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator=(const Dual& other){
    real = other.real;
    for(int i = 0; i < DIMENSIONS;++i){
        for(int j = 0; j < DEGREES; ++j){
            derivatives[i][j] = other.derivatives[i][j];
        }
    }
    return *this;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES>::Dual(const Dual& other){
    real = other.real;
    for(int i = 0; i < DIMENSIONS;++i){
        for(int j = 0; j < DEGREES; ++j){
            derivatives[i][j] = other.derivatives[i][j];
        }
    }
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES>::Dual(Dual&& other){
    real = other.real;
    for(int i = 0; i < DIMENSIONS;++i){
        for(int j = 0; j < DEGREES; ++j){
            derivatives[i][j] = other.derivatives[i][j];
        }
    }
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator=(Dual&& other){
    real = other.real;
    for(int i = 0; i < DIMENSIONS;++i){
        for(int j = 0; j < DEGREES; ++j){
            derivatives[i][j] = other.derivatives[i][j];
        }
    }
    return *this;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::operator+(double other){
    Dual res = *this;
    res.real += other;
    return res;
}
template <int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> Dual<DIMENSIONS, DEGREES>::ln(){
    Dual input = *this;
    input = input * (1/real);
    input.real = 0;

    Dual res = input;
    for(int i = 2; i <= DEGREES; ++i){
        res = res + input.pow(i) * -(std::pow(-1, i) / i);
    }
    res.real = std::log(real);

    return res;
}
