#ifndef CHESS_AI_MAIN_H
#define CHESS_AI_MAIN_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;


class neural_network{
public:
    cube weights1 = randu<cube>(2, 2, 2);
    mat weights2 = randu<mat>(1, 4);
    mat weights3 = randu<mat>(1, 8);

    double forward(cube input);
    vec flatten(mat input);
    double output(vec input);
    double relu(double x);
    mat convolve_matrix(mat input, mat kernel);
    mat convolve_tensors(cube input, cube kernel);
};

class game{
public:
    vector<vector<int>> board;

    game() : board(3, vector<int>(3, 0)) {}

    void print_board();
    void set(int x, int y, int player_num);
    vector<pair<int, int>> available_moves();
    int winner();
};

class genetic_algorithm{
public:
    int population_size = 50;
    vector<neural_network> population;
    vector<neural_network> old;

    void generate_neural_networks(int size = 50);
    double evaluate_score(neural_network &nn, int games_per_network = 10);
    vector<neural_network> select(int num = 10, int games_per_network = 10);
    void mutate(neural_network &nn);
    void crossover(neural_network &nn1, neural_network &nn2);
    void train(int generations = 100);
    int play(neural_network player1, neural_network player2);
};

#endif //CHESS_AI_MAIN_H
