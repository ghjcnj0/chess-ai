#include <iostream>
#include <armadillo>
#include <chrono>
#include <vector>
#include <algorithm>

#include "neural_network/src/neural_network.cpp"
#include "neural_network/src/tic_tac_toe.cpp"

using namespace std;


int main()
{
    game g;
    neural_network nn;
    g.set(0, 0, 1);
    cout << nn.forward(g.board) << endl;
}