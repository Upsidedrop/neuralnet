#include "NeuralNet.hpp"

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