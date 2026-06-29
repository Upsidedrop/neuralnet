#pragma once

#include "DualNumber.hpp"

template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
class NeuralNet{
    public:
    int getWeightIndex(int x, int y1, int y2);
    void testRun(double* inputs, double* outputs);
    double train(double* inputs, double* outputs, double* desiredOutputs, double learningRate = 0.5);
    template<int DIMENSIONS, int DEGREES>
    Dual<DIMENSIONS, DEGREES> createTracker(double value, int index);
    double weights[HEIGHT * (HEIGHT * (WIDTH - 1) + NUM_INPUTS + NUM_OUTPUTS)];
};

#include "neuralnet.cpp"