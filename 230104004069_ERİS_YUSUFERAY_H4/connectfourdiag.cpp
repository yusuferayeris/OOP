#include "connectfourdiag.h"
#include <iostream>

namespace YusufEray{

    connectfourdiag::connectfourdiag() : connectfourabstract() {}
    connectfourdiag::connectfourdiag(int w, int h) : connectfourabstract(w,h) {}

        bool connectfourdiag::diagonal1(cell ** c, int i , int y){
            for(int a = 0; a < 4 ; a++){
                if(i + a >= height || y + a >= width ) return 0;
                if(c[i][y] == c[i+a][y+a]) continue;
                else return 0;
            }
            return 1;
        }
        bool connectfourdiag::diagonal2(cell ** c, int i , int y){
            for(int a = 0; a < 4 ; a++){
                if(i - a < 0 || y + a >= width ) return 0;
                if(c[i][y] == c[i-a][y+a]) continue;
                else return 0;
            }
            return 1;
        }

        bool connectfourdiag::iswin(){
            for(int i = 0; i< width; i++){
                for(int a = 0; a < height; a++){
                    if((diagonal1(board,a,i) || diagonal2(board,a,i)) && (board[a][i].getplayer() != ' ') && (board[a][i].getplayer() != '.')) return 1;
                }
            }
            return 0;
        }
        bool connectfourdiag::isgameend(){
            for(int i = 0 ; i<width; i++){
            for(int j = 0; j<height; j++){
                if(board[j][i].getplayer() == '.') return 0;
            }
        }
        return 1;
        }
}