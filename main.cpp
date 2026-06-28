#include <iostream>

#include "DualNumber.hpp"

int main(){
    std::cout << "Hello, World!\n";
    double init[2][2] = 
    {
        {1, 0},
        {2, 1}
    };
    double init2[2][2] = 
    {
        {3, 5},
        {1, 3}
    };
    Dual<2, 2> foo(init, 4);
    (foo.pow(2)).print();
    std::cout << "\n";
    (foo.exp()).print();
    std::cout << "\n";
    (foo.exp().ln()).print();
    std::cout << "\n";
    (foo + 1).print();
    std::cout << "\n";
    foo.print();
    std::cout << "\n";
    (Dual<2, 2>(init2, 7) * 3).print();
}