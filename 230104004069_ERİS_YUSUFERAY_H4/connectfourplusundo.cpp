#include "connectfourplusundo.h"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace YusufEray{

    connectfourplusundo::connectfourplusundo() : connectfourplus() {}
    connectfourplusundo::connectfourplusundo(int w, int h) : connectfourplus(w,h) {}

    void connectfourplusundo::play(char col, char symbol) {
        connectfourplus::play(col, symbol);
        history.push_back(col - 'a');
    }

    void connectfourplusundo::play() {
        int * availablecols = new int[width];
        int count = 0;
        for(int i = 0; i < width; i++){
            if(board[0][i].getplayer() == '.'){
                availablecols[count] = i;
                count++;
            }
        }

        if(count > 0){
            int randIndex = rand() % count;
            int col = availablecols[randIndex];

            for(int i = height - 1; i >= 0; i--){
                if(board[i][col].getplayer() == '.'){
                    board[i][col].setplayer('C');
                    cout << "Computer played in collumn " << char('a' + col) << endl;
                    history.push_back(col);
                    break;
                }
            }
        }
        delete[] availablecols;
    }

    void connectfourplusundo::undo() {
        if(history.empty()){
            cout<<"No moves to undo"<<endl;
            return;
        }

        int lastCol = history.back();
        history.pop_back();

        for(int i = 0; i < height; i++){
            if(board[i][lastCol].getplayer() != '.'){
                board[i][lastCol].setplayer('.');
                return;
            }
        }
    }
}