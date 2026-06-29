#pragma once

template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
class NeuralNet{
    public:
    int getWeightIndex(int x, int y1, int y2);
    void testRun(double* inputs, double* outputs);
    double weights[HEIGHT * (HEIGHT * (WIDTH - 1) + NUM_INPUTS + NUM_OUTPUTS)];
};

#include "neuralnet.cpp"