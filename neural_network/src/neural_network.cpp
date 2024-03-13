#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void main1() {
    cout << "Hello, World!" << endl;
    mat A = randu<mat>(4,5);
    mat B = randu<mat>(4,5);
    cout << A*B.t() << endl;
}
