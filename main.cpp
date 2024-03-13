#include <iostream>
#include <armadillo>
#include <vector>

#include "dependencies/olmallet81/GALGO-2.0/GALGO-2.0-master/src/Galgo.hpp"
#include "neural_network/src/neural_network.cpp"

using namespace std;
using namespace arma;
using namespace galgo;


template <typename T>
class MyObjective{
public:
    static std::vector<T> Objective(const std::vector<T>& x)
    {
        return {- (x[0] - 1) * (x[0] - 3)};
    }
};


int main(){
    Parameter<double> par1({0.0, 10.0});

    GeneticAlgorithm<double> ga(MyObjective<double>::Objective,100,500,true,par1);

    ga.run();
}