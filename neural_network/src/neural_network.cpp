#include <armadillo>
#include <cmath>

#include "tic_tac_toe.cpp"

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
        return 1.0;
    }

    double sigmoid(double x){
        return 1 / (1 + exp(-x));
    }



};

mat convert_to_matrix(const std::vector<std::vector<bool>>& v) {
    size_t rows = v.size();
    size_t cols = (rows > 0) ? v[0].size() : 0;

    arma::mat result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = static_cast<double>(v[i][j]);
        }
    }

    return result;
}

int play(neural_network player1, neural_network player2){
    game g;
    int player_num = 1;
    while (g.available_moves().size() > 0){
        g.print_board();
        vector<double> scores;
        for (auto move : g.available_moves()){
            auto copy = g;
            copy.set(move.first, move.second, player_num);

            if (player_num == 1){
                scores.push_back(player1.forward(convert_to_matrix(copy.board)));
            }
            else{
                scores.push_back(player2.forward(convert_to_matrix(copy.board)));
            }
        }

        auto best_move = g.available_moves()[distance(scores.begin(), max_element(scores.begin(), scores.end()))];
        g.set(best_move.first, best_move.second, player_num);
        player_num = 3 - player_num;
    }
    return g.winner();
}

class genetic_algorithm{
public:
    int population_size = 50;
    vector<neural_network> population;

    void generate_neural_networks(int size = 50){
        neural_network nn;
        for (int i = 0; i < size; i++){
            population.push_back(nn);
        }
    }

    vector<neural_network> select(int num = 10, int games_per_network = 10){
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<std::mt19937::result_type> random_index(0,population_size - 1);

        vector<vector<int>> results;

        int ind, result;
        for (int i = 0; i < population_size; i++){
            while (results[i][0] + results[i][1] + results[i][2] < games_per_network){
                ind = random_index(rng);
                if (results[ind][0] + results[ind][1] + results[ind][2] < games_per_network){
                    result = play(population[i], population[ind]);

                    if (result == 0){
                        results[i][2] += 1;
                        results[ind][2] += 1;
                    }
                    else if (result == 1){
                        results[i][0] += 1;
                        results[ind][1] += 1;
                    }
                    else if (result == 2){
                        results[i][1] += 1;
                        results[ind][0] += 1;
                    }
                }
            }

            for (auto res : results){
                cout << res[0] << " " << res[1] << " " << res[2] << endl;

            }
        }
        return population;
    }

};