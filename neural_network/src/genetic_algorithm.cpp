#include <iostream>
#include <armadillo>

#include "main.h"

using namespace std;
using namespace arma;

cube convert_board(const vector<std::vector<int>>& v) {
    // Создадим тензор 3x3x2
    cube result(3, 3, 2);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            result(i, j, 0) = v[i][j] == 1;
            result(i, j, 1) = v[i][j] == 2;
        }
    }
    return result;
}


void genetic_algorithm::generate_neural_networks(int size) {
    population_size = size;
    population.clear();
    for (int i = 0; i < population_size; i++) {
        population.push_back(neural_network());
    }
}

vector<neural_network> genetic_algorithm::select(int num, int games_per_network) {
    vector<neural_network> selected;
    vector<double> scores;
    double total_score = 0;

    for (int i = 0; i < population_size; i++) {
        double score = evaluate_score(population[i], games_per_network);
        scores.push_back(score);
        total_score += score;
    }

    // Выбираем сети с вероятностью, пропорциональной их счету
    for (int i = 0; i < num; i++) {
        double r = ((double) rand() / (RAND_MAX)) * total_score;
        for (int j = 0; j < population_size; j++) {
            if (r < scores[j]) {
                selected.push_back(population[j]);
                break;
            }
            r -= scores[j];
        }
    }

    return selected;
}

void genetic_algorithm::mutate(neural_network &nn) {
    normal_distribution d{0.0, 2.0};
    random_device rd{};
    mt19937 gen{rd()};

    nn.weights1 += d(gen);
    nn.weights2 += d(gen);
    nn.weights3 += d(gen);
}

void genetic_algorithm::crossover(neural_network &nn1, neural_network &nn2) {
    nn1.weights1 = nn1.weights1 + nn2.weights1;
}


void genetic_algorithm::train(int generations) {
    for (int i = 0; i < generations; i++) {
        cout << "Generation " << i << endl;
        auto selected = select(10, 15);
        vector<neural_network> new_population = selected;
        while (new_population.size() < population_size) {
            for (int j = 0; j < selected.size(); j++) {
                if (rand() % 2 == 0) {
                    neural_network mutated = selected[j];
                    mutate(mutated);
                    new_population.push_back(mutated);
                    if (new_population.size() >= population_size) break;
                }
                for (int k = j + 1; k < selected.size(); k++) {
                    neural_network child1 = selected[j];
                    neural_network child2 = selected[k];
                    crossover(child1, child2);
                    new_population.push_back(child1);
                    if (new_population.size() >= population_size) break;
                    new_population.push_back(child2);
                    if (new_population.size() >= population_size) break;
                }
                if (new_population.size() >= population_size) break;
            }
        }
        population = new_population;
    }
}

int genetic_algorithm::play(neural_network player1, neural_network player2) {
    game g;
    int player_num = 1;
    while (g.winner() == -1){
        vector<double> scores;
        for (auto move : g.available_moves()){
            auto copy = g;
            copy.set(move.first, move.second, player_num);
            if (player_num == 1){
                scores.push_back(player1.forward(convert_board(copy.board)));
            }
            else{
                scores.push_back(player2.forward(convert_board(copy.board)));
            }
        }
        auto best_move = g.available_moves()[distance(scores.begin(), max_element(scores.begin(), scores.end()))];
        g.set(best_move.first, best_move.second, player_num);
        player_num = 3 - player_num;
    }
    return g.winner();
}

double genetic_algorithm::evaluate_score(neural_network &nn, int games_per_network) {
    double score = 0;
    int res;
    for (int i = 0; i < games_per_network; i++) {
        res = play(nn, neural_network());
        if (res == 1){
            score += 1;
        }
        else if (res == 2){
            score -= 1;
        }
        else{
            score += 0.1;
        }
    }
    return score / games_per_network;
}
