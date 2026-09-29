#include "cell.h"
#include<iostream>
using namespace std;

YusufEray::cell::cell() : rowposition(1), colposition('a'), player('.') {}

void YusufEray::cell::setcol(char c){colposition = c; }
void YusufEray::cell::setrow(int r){rowposition = r; }
void YusufEray::cell::setplayer(char c){
    if(c != '.' && c!= 'X' && c!='O' && c!='C' && c!=' ' ){ cerr<<"wrong input for player"; exit(1);}
    else{
        player = c;
    }
}

int YusufEray::cell::getrow() const {return rowposition;}
char YusufEray::cell::getcol()const {return colposition;}
char YusufEray::cell::getplayer()const {return player;}

YusufEray::cell& YusufEray::cell::operator++(){
    switch (player)
    {
    case '.':
        player = 'X'; break;
    case 'X':
        player = 'O'; break;
    case 'O':
        player = 'C'; break;
    case 'C':
        player = '.'; break;
    
    default:
        break;
    }
    return *this;
}
YusufEray::cell YusufEray::cell::operator++(int){
    cell temp = *this;
    ++*this;
    return temp;
}
bool YusufEray::cell::operator==(const cell& other){
                return player==other.player;
            }
ostream& YusufEray::operator<<(ostream& os, const cell& c){
    os<<c.player;
    return os;
}
