#include <iostream>
#include <random>

#include "DualNumber.hpp"
#include "NeuralNet.hpp"
#include "Vector.hpp"

// Test Cases
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
    std::cout << "\n";

    NeuralNet<2, 3, 2, 2> bar;
    double input[2] =
    {
        1, 2
    };
    double output[2];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10, 10);
    for(int i = 0; i < 21; ++i){
        bar.weights[i] = dis(gen);
    }
    bar.testRun(input, output);
    std::cout << output[0] << "\n";
    std::cout << output[1] << "\n";

    std::cout << "\n";

    bar.train(input, output, nullptr);
    std::cout << output[0] << "\n";
    std::cout << output[1] << "\n";

    Vector<5> a;
    a.data[0] = 1;
    a.data[1] = 2;
    a.data[2] = 3;
    a.data[3] = 4;
    a.data[4] = 5;

    Vector<5> b;
    b.data[0] = 1;
    b.data[1] = 2;
    b.data[2] = 3;
    b.data[3] = 4;
    b.data[4] = 5;

    std::cout << "\n";

    (a.hadamard(b)).print();
    std::cout << b.squaredMagnitude() << "\n";
    b -= (a * 0.5);
    std::cout << b.squaredMagnitude() << "\n";
    b.print();
}