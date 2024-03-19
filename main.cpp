#include <iostream>
#include <armadillo>
#include <chrono>
#include <vector>
#include <algorithm>

#include "neural_network/src/neural_network.cpp"


using namespace std;

int main() {
    neural_network nn;
    cube tensor = randu(3, 3, 2);
    cout << nn.forward(tensor) << endl;
}