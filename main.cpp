#include <iostream>
#include <armadillo>
#include <chrono>
#include <vector>
#include <algorithm>

#include "neural_network/src/neural_network.cpp"
#include "neural_network/src/genetic_algorithm.cpp"


using namespace std;

void play_with_nn(neural_network nn){
    game g;
    auto moves = g.available_moves();
    int player_num = 1;
    while (g.winner() == -1){
        g.print_board();
        if (player_num == 1) {
            int x, y;
            cout << "Enter x and y: ";
            cin >> x >> y;
            g.set(x, y, 1);
        } else {
            vector<double> scores;

            for (auto move: g.available_moves()) {
                auto copy = g;

                copy.set(move.first, move.second, player_num);
                cout << nn.forward(convert_board(copy.board)) << endl;
                scores.push_back(nn.forward(convert_board(copy.board)));
            }

            auto best_move = g.available_moves()[distance(scores.begin(), max_element(scores.begin(), scores.end()))];
            g.set(best_move.first, best_move.second, player_num);
        }
        player_num = 3 - player_num;
    }
}


int main(){
    genetic_algorithm ga;
    ga.generate_neural_networks(20);
    ga.train(10);

    // получим лучшю модель
    neural_network best_model = ga.select(1, 10)[0];
    cout << best_model.weights1 << endl;

    play_with_nn(best_model);

}