#ifndef CHESS_AI_MAIN_H
#define CHESS_AI_MAIN_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;


class neural_network{
public:
    cube weights1 = randu(2, 2, 2);
    vec weights2 = randu(4);
    cube weights3 = randu(2, 2, 2);

    double forward(cube input);
    mat convolution(mat input, mat weights);
    cube convolution(cube input, cube weights);
    cube zero_borders(cube input, int padding);
    mat pool(mat input, int stride);
    cube pool(cube input, int stride);
    mat tensor_to_matrix(cube input);
    vec flatten(mat input);
    vec fully_connected(vec input, vec weights);
    double output(vec input);
};

class game{
public:
    vector<vector<int>> board;

    game() : board(3, vector<int>(3, 0)) {}

    void print_board();
    void set(int x, int y, int player_num);
    vector<pair<int, int>> available_moves();
    int winner();
    static cube convert_board(const vector<std::vector<int>>& v, int your_team);
};

#endif //CHESS_AI_MAIN_H
