#include "connectfourplus.h"
#include <iostream>

using namespace std;

namespace YusufEray{
    
    connectfourplus::connectfourplus() : connectfourabstract() {}
    connectfourplus::connectfourplus(int w, int h) : connectfourabstract(w,h) {}
     bool connectfourplus::vertical(cell ** c,int i,int y){
            for(int a = 0; a < 4 ; a++){
                if(i + a >= height) return 0;
                if(c[i][y] == c[i+a][y]) continue;
                else return 0;
            }
            return 1;
        }
        
        bool connectfourplus::horizontal(cell ** c,int x, int y){
            for(int a = 0; a < 4 ; a++){
                if(y + a >= width) return 0;
                if(c[x][y] == c[x][y+a]) continue;
                else return 0;
            }
            return 1;
        }
        bool connectfourplus::iswin(){
            for(int i = 0; i< width; i++){
                for(int a = 0; a < height; a++){
                    if( ((vertical(board,a,i) || horizontal(board,a,i)) == 1)  && (board[a][i].getplayer() != ' ') && (board[a][i].getplayer() != '.') ) return 1;
                }
            }
            return 0;
        }
    bool connectfourplus::isgameend(){
        for(int i = 0 ; i<width; i++){
            for(int j = 0; j<height; j++){
                if(board[j][i].getplayer() == '.') return 0;
            }
        }
        return 1;
        
    }

}