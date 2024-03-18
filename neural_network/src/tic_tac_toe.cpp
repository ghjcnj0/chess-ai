#include <iostream>
#include <vector>

using namespace std;

class game{
public:
    int num1 = 0;
    int num2 = 0;
    vector<vector<bool>> board;
    vector<vector<int>> points {{2, 9, 7}, {3, 1, 8}, {4, 5, 5}};

    game() : board(3, vector<bool>(3, false)) {}

    void print_board(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "First: " << num1 << " Second: " << num2 << endl;
    }

    void set(int x, int y, int player_num){
        if (board[x][y]){
            throw invalid_argument("This cell is already occupied");
        }
        board[x][y] = true;
        if (player_num == 1){
            num1 += points[x][y];
        } else {
            num2 += points[x][y];
        }
    }

    vector<pair<int, int>> available_moves(){
        vector<pair<int, int>> result;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (!board[i][j]){
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }

    int winner(){
        if (num1 > num2){
            return 1;
        } else if (num2 > num1){
            return 2;
        } else {
            return 0;
        }
    }


};