#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

mat convolve_matrix(mat input = randu<mat>(5, 5), mat kernel = randu<mat>(2, 2)){
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

mat convolve_tensors(cube input = randu<cube>(5, 5, 3), cube kernel = randu<cube>(2, 2, 3)) {
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

class neural_network{
public:
    mat weights1 = randu<mat>(3, 3);
    mat weights2 = randu<vec>(9, 1);

    double forward(mat input){
        mat convolved = convolve_matrix(input, weights1);
        vec flattened = flatten(convolved);
        if (flattened.n_elem != weights2.n_elem) {
            flattened.resize(weights2.n_elem);
        }
        return output(flattened);
    }

    vec flatten(mat input){
        return vectorise(input);
    }

    double output(vec input){
        double result = dot(input, weights2);
        return sigmoid(result);
    }

    double sigmoid(double x){
        return 1 / (1 + exp(-x));
    }
};