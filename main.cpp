#include <iostream>

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
    const int HEIGHT = 5;
    const int WIDTH = 10;
    const int NUM_INPUTS = 2;
    const int NUM_OUTPUTS = 2;
    NeuralNet<WIDTH, HEIGHT, NUM_INPUTS, NUM_OUTPUTS> bar;
    double input[NUM_INPUTS] =
    {
        1, 2
    };
    double desired[NUM_OUTPUTS] =
    {
        3,6
    };
    double output[NUM_OUTPUTS];
    for(int i = 0; i < HEIGHT * (HEIGHT * (WIDTH - 1) + NUM_INPUTS + NUM_OUTPUTS); ++i){
        bar.weights[i] = 2;
    }
    bar.testRun(input, output);
    std::cout << output[0] << "\n";
    std::cout << output[1] << "\n";

    std::cout << "\n";

    std::cout << bar.train(input, output, desired) << "\n";
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

    // (a.hadamard(b)).print();
    std::cout << b.squaredMagnitude() << "\n";
    b -= (a * 0.5);
    std::cout << b.squaredMagnitude() << "\n";
    b.print();

    while(true){
        // int stop = 0;
        // std::cin >> stop;
        // if(stop){
        //     break;
        // }

        std::cout << bar.train(input, output, desired, 1) << "\n";
        std::cout << output[0] << "\n";
        std::cout << output[1] << "\n";
    }
}