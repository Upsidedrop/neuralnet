#include "NeuralNet.hpp"

#include <math.h>

template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
int NeuralNet<WIDTH, HEIGHT, NUM_INPUTS, NUM_OUTPUTS>::getWeightIndex(int x, int y1, int y2){
    int res = 0;
    if(x != 0){
        res += ((x-1) * HEIGHT + NUM_INPUTS) * HEIGHT;
    }
    res += y1 * ((x == WIDTH)? NUM_OUTPUTS : HEIGHT);
    res += y2;
    return res;
}
template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
void NeuralNet<WIDTH, HEIGHT, NUM_INPUTS, NUM_OUTPUTS>::testRun(double* inputs, double* outputs){
    double nextLayerValues[HEIGHT]{};
    for(int i = 0; i < NUM_INPUTS; ++i){
        for(int j = 0; j < HEIGHT; ++j){
            nextLayerValues[j] += inputs[i] * weights[getWeightIndex(0, i, j)];
        }
    }
    {
        double currentLayerValues[HEIGHT];
        for(int i = 1; i < WIDTH; ++i){
            for(int j = 0; j < HEIGHT; ++j){
                currentLayerValues[j] = (std::log(std::exp(nextLayerValues[j]) + 1)) - 0.1 * (std::log(std::exp(-nextLayerValues[j]) + 1));
                nextLayerValues[j] = 0;
            }
            for(int j = 0; j < HEIGHT; ++j){
                for(int k = 0; k < HEIGHT; ++k){
                    nextLayerValues[k] += currentLayerValues[j] * weights[getWeightIndex(i, j, k)];
                }
            }
        }
    }
    for(int i = 0; i < NUM_OUTPUTS; ++i){
        outputs[i] = 0; 
    }
    for(int j = 0; j < HEIGHT; ++j){
        nextLayerValues[j] = (std::log(std::exp(nextLayerValues[j]) + 1)) - 0.1 * (std::log(std::exp(-nextLayerValues[j]) + 1));
        for(int i = 0; i < NUM_OUTPUTS; ++i){
            outputs[i] += nextLayerValues[j] * weights[getWeightIndex(WIDTH, j, i)]; 
        }
    }
}
template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
double NeuralNet<WIDTH, HEIGHT, NUM_INPUTS, NUM_OUTPUTS>::train(double* inputs, double* outputs, double* desiredOutputs, double learningRate){
    const int NUM_WEIGHTS = HEIGHT * (HEIGHT * (WIDTH - 1) + NUM_INPUTS + NUM_OUTPUTS);
    Dual<NUM_WEIGHTS,2> nextLayerValues[HEIGHT];
    for(int i = 0; i < HEIGHT; ++i){
        nextLayerValues[i] = Dual<NUM_WEIGHTS, 2>(0);
    }
    for(int i = 0; i < NUM_INPUTS; ++i){
        for(int j = 0; j < HEIGHT; ++j){
            nextLayerValues[j] += createTracker<NUM_WEIGHTS, 2>(weights[getWeightIndex(0, i, j)], getWeightIndex(0, i, j)) * inputs[i];
        }
    }
    {
        Dual<NUM_WEIGHTS,2> currentLayerValues[HEIGHT];
        for(int i = 1; i < WIDTH; ++i){
            for(int j = 0; j < HEIGHT; ++j){
                currentLayerValues[j] = (nextLayerValues[j].exp() + 1).ln() + (((nextLayerValues[j] * -1).exp() + 1).ln()) * (-0.1);
                nextLayerValues[j] = 0;
            }
            for(int j = 0; j < HEIGHT; ++j){
                for(int k = 0; k < HEIGHT; ++k){
                    nextLayerValues[k] += currentLayerValues[j] * createTracker<NUM_WEIGHTS, 2>(weights[getWeightIndex(i, j, k)], getWeightIndex(i, j, k));
                }
            }
        }
    }
    Dual<NUM_WEIGHTS,2> outputDuals[NUM_OUTPUTS];
    for(int i = 0; i < NUM_OUTPUTS; ++i){
        outputDuals[i] = Dual<NUM_WEIGHTS,2>(0); 
    }
    for(int j = 0; j < HEIGHT; ++j){
        nextLayerValues[j] = (nextLayerValues[j].exp() + 1).ln() + (((nextLayerValues[j] * -1).exp() + 1).ln()) * (-0.1);
        for(int i = 0; i < NUM_OUTPUTS; ++i){
            outputDuals[i] += nextLayerValues[j] * createTracker<NUM_WEIGHTS, 2>(weights[getWeightIndex(WIDTH, j, i)], getWeightIndex(WIDTH, j, i)); 
        }
    }
    for(int i = 0; i < NUM_OUTPUTS; ++i){
        outputs[i] = outputDuals[i].real;
    }
    return 0;
}
template<int WIDTH, int HEIGHT, int NUM_INPUTS, int NUM_OUTPUTS>
template<int DIMENSIONS, int DEGREES>
Dual<DIMENSIONS, DEGREES> NeuralNet<WIDTH, HEIGHT, NUM_INPUTS, NUM_OUTPUTS>::createTracker(double value, int index){
    Dual<DIMENSIONS, DEGREES> res(0);
    res.real = value;
    res.derivatives[index][0] = 1;
    return res;
}