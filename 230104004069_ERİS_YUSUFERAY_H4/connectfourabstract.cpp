#include "connectfourabstract.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

namespace YusufEray{
    connectfourabstract::connectfourabstract() : width(5), height(5) {
        board = new cell*[height];
        for(int i = 0; i<height ; i++){
            board[i] = new cell[width];
        }
        for(int i = 0; i< height; i++){
            for(int j = 0; j<width;j++){
                board[i][j].setplayer('.');
                board[i][j].setcol('a'+j);
                board[i][j].setrow(i+1);
            }
        }
    }
    connectfourabstract::connectfourabstract(int w, int h) : width(w), height(h) {
        board = new cell*[height];
        for(int i = 0; i<height ; i++){
            board[i] = new cell[width];
        }
        for(int i = 0; i< height; i++){
            for(int j = 0; j<width;j++){
                board[i][j].setplayer('.');
                board[i][j].setcol('a'+j);
                board[i][j].setrow(i+1);
            }
        }
    }

    connectfourabstract::~connectfourabstract(){
        for(int i = 0; i<height ; i++){
           delete[] board[i];
        }
        delete[] board;
    }

    void connectfourabstract::display(){
        for(int k = 0; k<width;k++) cout<<(char)('a' + k)<<" ";
        cout<<endl;
        for(int i = 0; i<height; i++){
            for(int j = 0; j< width; j++){
               cout<< board[i][j].getplayer()<<" ";
            }
            cout<<endl;
        }
    }

    void connectfourabstract::play(){
          for(int i = 0; i < width; i++){
                for(int a = height - 1; a >= 0; a-- ){
                    if(board[a][i].getplayer() == '.'){
                        board[a][i].setplayer('C');
                        if(iswin()){
                            cout << "Computer played in collumn " << char('a' + i) << endl;
                            display();
                            cout<<"computer win!!!";
                            exit(1);
                        }
                        else{
                            board[a][i].setplayer('.');
                            break;
                        }
                    }
                }      
            } 
            
            for(int i = 0; i < width; i++){
                for(int a = height- 1; a >= 0; a-- ){
                    if(board[a][i].getplayer() == '.'){
                        board[a][i].setplayer('X');
                        if(iswin()){
                            board[a][i].setplayer('C');
                            cout << "Computer played in collumn " << char('a' + i) << endl;
                            display();
                            return; 
                            
                        }
                        else{
                            board[a][i].setplayer('.');
                            break;
                        }
                    }
                }      
            }
            
            
                
                int * availablecols = new int[width];
                int count = 0;
                for(int i = 0; i < width; i++){
                    for(int a = 0; a < height; a++){
                        if(board[a][i].getplayer() == '.'){
                            availablecols[count] = i;
                            count++;
                            break;
                        }
                    }
                }
                srand(time(0));
                int randcol = rand() % count;
                randcol = availablecols[randcol];
                delete[] availablecols;
                int flag = 0;
                for(int b = height - 1; b >= 0; b-- ){
                    if(board[b][randcol].getplayer() == '.' ){
                        board[b][randcol].setplayer('C');
                        cout << "Computer played in collumn " << char('a' + randcol) << endl;
                        flag = 1;
                        break;
                    }
                }
            
    }
    void connectfourabstract::play(char col, char symbol){
        if(col - 'a' > width || 0 > col - 'a' ){
            cerr<<"undefined col";
            exit(1);
        }
        char flag = 0;
            for(int i = height - 1; i >= 0; i-- ){
                if(board[i][col-'a'].getplayer() == '.' ){
                    board[i][col - 'a'].setplayer(symbol);
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                cout<<"the collumn "<< col << " is full try any other move "<<endl;
                cout<<"enter new move : ";
                cin>>col;
                play(col,symbol);
            }

    }
    bool isnumber(string s){
        for(char c : s){
            if(isdigit(c) == 0) return false;
        }
        return true;
    }
    
    void connectfourabstract::playgame(){
        string input;
        int w = 0, h = 0;
        cout<<"enter width or to play older game enter 'LOAD' "<<endl;
        cin>>input;
        if(input == "LOAD" || input == "load"){
            string fname;
            cout<<"enter file name : ";
            cin>>fname;
            char currentplayer = readfromfile(fname);

            
            bool isVsComputer = false;
            bool hasPlayer2Token = false; 
            bool hasComputerToken = false; 

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    char p = board[i][j].getplayer();
                    if(p == 'C') hasComputerToken = true;
                    if(p == 'O') hasPlayer2Token = true;
                }
            }

            
            if(hasComputerToken) {
                isVsComputer = true; 
            }
            else if(hasPlayer2Token) {
                isVsComputer = false; 
            }
            else {
                
                cout << "Detected new game. Is this vs Computer? (y/n): ";
                char ans;
                cin >> ans;
                if(ans == 'y' || ans == 'Y') isVsComputer = true;
                else isVsComputer = false;
            }

            if(currentplayer == 'X'){
                string move;
                char playercol;
                while(1){
                        
                        cout<<"Player 1 (X) enter move or to save enter 'SAVE' : ";
                        cin>>move;
                        
                        if(move == "save" || move == "SAVE"){
                            cout<<"enter file name: ";
                            string fname;
                            cin>>fname;
                            writetofile(fname,'X');
                            return;
                        }
                        else{
                            if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                cerr<<"false input";
                                exit(1);
                            }
                            playercol = move[0];
                            play(playercol,'X');
                        }
                        display();
                        if(iswin()){
                            cout<<"Player 1 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }

                       
                        if(isVsComputer){
                            cout << "Computer is playing..." << endl;
                            play(); 
                        }
                        else{
                            cout<<"Player 2 (O) enter move or to save enter 'SAVE' : ";
                            cin>>move;
                            if(move == "save" || move == "SAVE"){
                                cout<<"enter file name: ";
                                string fname;
                                cin>>fname;
                                writetofile(fname,'O');
                                return;
                            }
                            else{
                                if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                    cerr<<"false input";
                                    exit(1);
                                }
                                playercol = move[0];
                                play(playercol,'O');
                            }
                        }
                        
                        display();
                        if(iswin()){
                            if(isVsComputer) cout<<"computer win !!!!";
                            else cout<<"Player 2 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }
                    }
            }
            
            else if(currentplayer == 'O'){
                string move;
                char playercol;
                while(1){
                        
                        if(isVsComputer){
                             
                             cout << "Computer is playing..." << endl;
                             play();
                        }
                        else{
                             
                             cout<<"Player 2 (O) enter move or to save enter 'SAVE' : ";
                             cin>>move;
                             if(move == "save" || move == "SAVE"){
                                 cout<<"enter file name: ";
                                 string fname;
                                 cin>>fname;
                                 writetofile(fname,'O'); 
                                 return;
                             }
                             else{
                                 if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                     cerr<<"false input";
                                     exit(1);
                                 }
                                 playercol = move[0];
                                 play(playercol,'O');
                             }
                        }

                        display();
                        if(iswin()){
                            if(isVsComputer) cout<<"Computer win !!!!";
                            else cout<<"Player 2 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }

                        
                        cout<<"Player 1 (X) enter move or to save enter 'SAVE' : ";
                        cin>>move;
                        if(move == "save" || move == "SAVE"){
                            cout<<"enter file name: ";
                            string fname;
                            cin>>fname;
                            writetofile(fname,'X'); 
                            return;
                        }
                        else{
                            if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                cerr<<"false input";
                                exit(1);
                            }
                            playercol = move[0];
                            play(playercol,'X');
                        }
                        display();
                        if(iswin()){
                            cout<<"Player 1 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }
                }
            }
            
            else{
                
                string move;
                char playercol;
                while(1){
                        cout << "Computer is playing..." << endl;
                        play(); 
                        
                        display();
                        if(iswin()){
                            cout<<"computer win!!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"there is no winner";
                            exit(1);
                        }

                        cout<<"enter your move or to save enter 'SAVE' "<<endl;
                        cin>>move;
                        if(move == "save" || move == "SAVE"){
                            cout<<"enter file name";
                            string fname;
                            cin>>fname;
                            
                            writetofile(fname,'C'); 
                            return;
                        }
                        else{
                            if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                cerr<<"false input";
                                exit(1);
                            }
                            playercol = move[0];
                            play(playercol,'X');
                        }
                        display();
                        if(iswin()){
                            cout<<"you win!!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"there is no winner";
                            exit(1);
                        }
                }
            }
        }
        else{
            if(isnumber(input)){
                w = stoi(input);
                cout<<"enter height"<<endl;
                cin>>h;
                for(int i = 0; i<height ; i++){
                    delete[] board[i];
                }
                delete[] board;

                height = h;
                width = w;

                board = new cell*[height];
                for(int i = 0; i<height ; i++){
                    board[i] = new cell[width];
                }
                for(int i = 0; i< height; i++){
                    for(int j = 0; j<width;j++){
                        board[i][j].setplayer('.'); 
                        board[i][j].setcol('a'+j);
                        board[i][j].setrow(i+1);
                    }
                }

                cout<<"enter game mode "<<endl<<"1. player vs player"<<endl<<"2. player vs computer"<<endl;
                int choose;
                cin>>choose;
                string move;
                char playercol;
                switch (choose)
                {
                case 1:
                    while(1){
                        cout<<"player 1 enter move or to save enter 'SAVE' "<<endl;
                        cin>>move;
                        if(move == "save" || move == "SAVE"){
                            cout<<"enter file name";
                            string fname;
                            cin>>fname;
                            writetofile(fname,'X');
                            return;
                        }
                        else{
                            if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                cerr<<"false input";
                                exit(1);
                            }
                            playercol = move[0];
                            play(playercol,'X');
                            

                        }
                        display();
                        if(iswin()){
                            cout<<"player 1 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }
                        cout<<"player 2 enter move or to save enter 'SAVE' "<<endl;
                        cin>>move;
                        if(move == "save" || move == "SAVE"){
                            cout<<"enter file name";
                            string fname;
                            cin>>fname;
                            writetofile(fname,'O');
                            return;
                        }
                        else{
                            if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                cerr<<"false input";
                                exit(1);
                            }
                            playercol = move[0];
                            play(playercol,'O');
                            

                        }
                        display();
                        if(iswin()){
                            cout<<"player 2 win !!!!";
                            exit(1);
                        }
                        if(isgameend()){
                            cout<<"gameend there is no winner";
                            exit(1);
                        }

                    }
                    break;
                case 2:
                    while(1){
                        cout<<"enter your move or to save enter 'SAVE' "<<endl;
                            cin>>move;
                            if(move == "save" || move == "SAVE"){
                                cout<<"enter file name";
                                string fname;
                                cin>>fname;
                                writetofile(fname,'O');
                                return;
                            }
                            else{
                                if(move.size() != 1 || move[0] < 'a' || move[0]> 'z'){
                                    cerr<<"false input";
                                    exit(1);
                                }
                                playercol = move[0];
                                play(playercol,'X');
                                

                            }
                            display();
                            if(iswin()){
                                cout<<"you win!!!!";
                                exit(1);
                            }
                            if(isgameend()){
                                cout<<"there is no winner";
                                exit(1);
                            }
                            play();
                            display();
                    }
                    break;
                default:
                    break;
                }


                
            }
            else{
                cerr<<"invalid input ";
                exit(1);
            }

        }
    }
    char connectfourabstract::readfromfile(string filename){
    ifstream yf;
    yf.open(filename);
    if (!yf.is_open()) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    string firstline;
    getline(yf, firstline); 
    char nextplayer = firstline.back();
    
    if(nextplayer != 'X' && nextplayer != 'O' && nextplayer != 'C') {
        cerr<<"wrong file format";
        exit(1);
    }

    char ch;
    int maxwidth = 0;
    int maxheight = 0;
    int tempc = 0;

    while(yf.get(ch)){
        if(ch == ' ' || ch == '*' || ch == 'X' || ch == 'O' || ch == 'C' || ch == '.'){
            tempc++;
            if(tempc > maxwidth){
                maxwidth = tempc;
            }
        }
        if(ch == '\n'){
            maxheight++; 
            tempc = 0;
        }
    }
    if(tempc > 0) maxheight++;

    for(int i = 0; i < height ; i++){
        delete[] board[i];
    }
    delete[] board;

    width = maxwidth;
    height = maxheight;

    board = new cell*[height];
    for(int i = 0; i < height; i++){
        board[i] = new cell[width];
    }

    for(int i = 0; i< height; i++){
        for(int j = 0; j<width;j++){
            board[i][j].setplayer('.');
            board[i][j].setcol('a'+j);
            board[i][j].setrow(i+1); 
        }
    }

    yf.clear();
    yf.seekg(0, ios::beg);
    getline(yf, firstline);

    int r = 0, c = 0;
    while(yf.get(ch)){
        if(ch == 'X' || ch == 'O' || ch == 'C' || ch == '*' || ch == '.'){
            if(ch == '*') ch = '.'; 
            
            board[r][c].setplayer(ch);
            c++;
        }
        else if(ch == '\n'){
                r++;
                c = 0;
        }
        else {
            c++;
        }
    }
    
    yf.close();
    return nextplayer;
}
    void connectfourabstract::writetofile(string filename,char player){
        ofstream yf;
        yf.open(filename);
        yf<<"player : "<<player<<endl;
        for(int i = 0; i < height ; i++){
            for(int j = 0; j < width ; j++){
                yf<< board[i][j].getplayer();
            }
            yf<<endl;
        }

    }

}