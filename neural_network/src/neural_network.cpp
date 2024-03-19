#include <armadillo>
#include <cmath>

#include "tic_tac_toe.cpp"
#include "main.h"

using namespace std;
using namespace arma;


double neural_network::forward(cube input){
    mat layer1 = convolve_tensors(input, weights1);
    // Добавим полносвязный слой
    vec layer2 = flatten(layer1) * weights2;

    return output(layer2);
}

vec neural_network::flatten(mat input){
    return vectorise(input);
}

double neural_network::output(vec input){
    return relu(dot(input, weights2));
}

double neural_network::relu(double x){
    return max(0.0, x);
}

mat neural_network::convolve_matrix(mat input = randu<mat>(5, 5), mat kernel = randu<mat>(2, 2)){
    int a = input.n_rows;
    int b = kernel.n_rows;

    mat result = randu<mat>(a - b + 1, a - b + 1);
    for (int i = 0; i < a - b + 1; i++){
        for (int j = 0; j < a - b + 1; j++){
            mat submat = input.submat(i, j, i + b - 1, j + b - 1);
            result(i, j) = accu(submat % kernel);
        }
    }
    return result;
}

mat neural_network::convolve_tensors(cube input = randu<cube>(5, 5, 3), cube kernel = randu<cube>(2, 2, 3)) {
    int a = input.n_rows;
    int b = kernel.n_rows;
    int c = input.n_slices;

    if (input.n_slices != kernel.n_slices) {
        throw invalid_argument("The number of channels in the input and kernel must be the same");
    }

    mat result = randu<mat>(a - b + 1, a - b + 1);
    for (int i = 0; i < c; i++) {
        result += convolve_matrix(input.slice(i), kernel.slice(i));
    }
    return result;
}
