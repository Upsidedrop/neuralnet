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