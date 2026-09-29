#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

class connectfour{
    private:
        // Inner class representing a single cell on the game board
        class cell{
        public:
            char symbol; // Character in the cell (X, O, etc.)
            char col;    // Column identifier
            int row;     // Row identifier
            bool statu;  // Status: 0 for empty, 1 for occupied
            
            // Default constructor
            cell(): symbol('.'), col('a'), row(0), statu(0){}
            
            // Parameterized constructor
            cell(char s, char r, int c): symbol(s), col(r), row(c), statu(0){}
            
            // Equality operator to compare cell symbols
            bool operator == (const cell& c){
            return symbol == c.symbol;
            }
            
            // Prefix increment operator: Cycles the cell symbol
            cell & operator++ (){
                if(symbol == '.') symbol = 'X';
                else if(symbol == 'X') symbol = 'O';
                else if(symbol == 'O') symbol = 'C';
                else if(symbol == 'C') symbol = '.';
                return *this;
            }
            
            // Postfix increment operator
            cell operator++ (int){
                cell temp = *this;
                ++(*this);
                return temp;
            }
            
            // Overloaded stream operator to print the cell symbol
            friend ostream& operator<<(ostream& os, const cell& c){
                os << c.symbol;
                return os;
            }
        };  
        
        cell **board; // 2D array for the game board
        int cols;
        int rows;
        
        public:
        // Default constructor: Creates a 5x5 board
        connectfour(): cols(5), rows(5){
            board = new cell*[rows];
            for(int i = 0; i < rows; i++){
                board[i] = new cell[cols];
            }
        }
        
        // Copy constructor: Performs a deep copy of the board
        connectfour(const connectfour& other){
            rows = other.rows;
            cols = other.cols;
            board = new cell*[rows];
            for(int i=0;i<rows;i++){
                board[i] = new cell[cols];
                for(int j=0;j<cols;j++) board[i][j] = other.board[i][j];
            }
        }  

        // Assignment operator: Handles deep copy and memory cleanup
        connectfour& operator= (const connectfour& other){
            if(this != &other){ // Self-assignment check
                // Clean up old memory
                for(int i = 0; i < rows; i++){
                    delete[] board[i];
                }
                delete[] board;
                
                // Allocate and copy new data
                rows = other.rows;
                cols = other.cols;
                board = new cell*[rows];
                for(int i = 0; i < rows; i++){
                    board[i] = new cell[cols];
                }
                for(int i = 0; i < rows; i++){
                    for(int a = 0; a < cols; a++){
                        board[i][a] = other.board[i][a];
                    }
                }
            }
            return *this;
        }

        // Equality operator: Checks if two boards are identical
        bool operator== (const connectfour& other){
            if(rows != other.rows || cols != other.cols) return 0;
            for(int i = 0; i < rows; i++){
                for(int a = 0; a < cols; a++){
                    if(board[i][a] == other.board[i][a]) continue;
                    else return 0;
                }
            }
            return 1;
        }

        // Inequality operator
        bool operator!= (const connectfour& other){
            return !(*this == other);
        }

        // Constructor with custom dimensions
        connectfour(int r, int c): cols(c), rows(r){
            board = new cell*[rows];
            for(int i = 0; i < rows; i++){
                board[i] = new cell[cols];
            }
            // Initialize column characters
            for(int i = 0; i< cols; i++){
                for(int a = 0; a< rows; a++){
                    board[a][i].col = 'a' + i; 
                }
            }
            // Initialize row numbers
            for(int i = 0; i < rows; i++){
                for(int a = 0; a < cols; a++){
                    board[i][a].row = 0 + i;
                }
            }
        }

        // Constructor that initializes the board from a file
        connectfour(string filename){
             ifstream file;
            file.open(filename);
            char ch;
            rows = 1;
            cols = 0;
            int tempc = 0;
            
            // First pass: Determine rows and columns
            while(file.get(ch)){
                if(ch == ' ' || ch == '*'){
                    tempc++;
                    if(tempc > cols){
                        cols = tempc;
                    }
                }
                if(ch == '\n'){
                    rows++; 
                    tempc = 0;
                }
                
            }
            board = new cell*[rows];
            for(int i = 0; i < rows; i++){
                board[i] = new cell[cols];
            }
            
            // Reset file pointer to beginning
            file.clear();
            file.seekg(0, ios::beg);
            

            for(int i = 0; i< cols; i++){
                for(int a = 0; a< rows; a++){
                    board[a][i].col = 'a' + i; 
                }
            }
            // Initialize board state
            for(int i = 0; i < rows; i++){
                for(int a = 0; a < cols; a++){
                    board[i][a].row = 0 + i;
                    board[i][a].symbol = ' ';
                    board[i][a].statu = 1; // Mark as occupied initially (for non-playable spaces)
                }
            }
            int r = 0, c = 0;
            // Second pass: Read actual board configuration
            while(file.get(ch)){              
                if(ch == '*'){
                    board[r][c].symbol = '.';
                    board[r][c].statu = 0; // Mark as playable empty spot
                    c++;
                }
                else if(ch == ' '){
                    c++;
                }
                else if(ch == '\n'){
                    r++;
                    c = 0;
                }
            }
            file.close();

        





        } 
        
        // Destructor: Frees dynamically allocated memory
        ~connectfour(){
            for(int i = 0; i < rows; i++){
                delete[] board[i];
            }
            delete[] board;
        }

        // Prints the current state of the board to the console
        void printboard(){
            cout<<endl;
            cout<<"  ";
            for(int i = 0; i < cols; i++){
                cout<< char('a' + i) << " ";
            }
            cout<<endl;
            for(int i = 0; i < rows; i++){
                cout<< i << " ";
                for(int a = 0; a < cols; a++){
                    cout<< board[i][a].symbol << " ";
                }
                cout<<endl;
                
            }
        }

        // Checks for a vertical win condition (4 in a row)
        bool vertical(cell ** c,int i,int y){
            for(int a = 0; a < 4 ; a++){
                if(i + a >= rows) return 0;
                if(c[i][y] == c[i+a][y]) continue;
                else return 0;
            }
            return 1;
        }
        
        // Checks for a horizontal win condition
        bool horizontal(cell ** c,int x, int y){
            for(int a = 0; a < 4 ; a++){
                if(y + a >= cols) return 0;
                if(c[x][y] == c[x][y+a]) continue;
                else return 0;
            }
            return 1;
        }

        // Checks for a diagonal win condition (top-left to bottom-right)
        bool diagonal1(cell ** c, int i , int y){
            for(int a = 0; a < 4 ; a++){
                if(i + a >= rows || y + a >= cols ) return 0;
                if(c[i][y] == c[i+a][y+a]) continue;
                else return 0;
            }
            return 1;
        }
        
        // Checks for a diagonal win condition (top-right to bottom-left)
        bool diagonal2(cell ** c, int i , int y){
            for(int a = 0; a < 4 ; a++){
                if(i - a < 0 || y + a >= cols ) return 0;
                if(c[i][y] == c[i-a][y+a]) continue;
                else return 0;
            }
            return 1;
        }

        // Iterates through the board to check if there is a winner
        bool win(){
            for(int i = 0; i< cols; i++){
                for(int a = 0; a < rows; a++){
                    if( (diagonal1(board,a,i) || diagonal2(board,a,i) || vertical(board,a,i) || horizontal(board,a,i)) == 1 && (board[a][i].statu == 1) && (board[a][i].symbol != ' ')) return 1;
                }
            }
            return 0;
        }

        // Checks if the game has ended in a draw (board full)
        bool gameend(){
            for(int i = 0; i< cols; i++){
                for(int a = 0; a < rows; a++){
                    if(board[a][i].statu == 0) return 0;
                }
            }
            return 1;
        }

        // Handles a move by a specific player (Human or specific symbol)
        void play(char col, char symbol){
            char flag = 0;
            // Simulates gravity: Start from bottom row up
            for(int i = rows - 1; i >= 0; i-- ){
                if(board[i][col-'a'].statu == 0){
                    board[i][col - 'a'].symbol = symbol;
                    board[i][col - 'a'].statu = 1;
                    flag = 1;
                    break;
                }
            }
            // If column is full, ask for input again
            if(flag == 0){
                cout<<"the collumn "<< col << " is full try any other move "<<endl;
                cout<<"enter new move : ";
                cin>>col;
                play(col,symbol);
            }
            // Check win condition
            if(win()){
                printboard();
                cout<< "player "<<symbol<<" win concurlations!!!";
                exit(1);
            }
            // Check draw condition
            if(gameend())
            {
                printboard();
                cout<< "game end there is no winner :(";
                exit(1);
            }


        }

        // Handles the Computer's move (AI Logic)
        void play(){
            // 1. Check if Computer can win in the next move
            for(int i = 0; i < cols; i++){
                for(int a = rows - 1; a >= 0; a-- ){
                    if(board[a][i].statu == 0){
                        board[a][i].symbol = 'C';
                        board[a][i].statu = 1;
                        if(win()){
                            cout << "Computer played in collumn " << char('a' + i) << endl;
                            cout<<"Computer wins concurlations!!!"<<endl;
                            printboard();
                            exit(1);
                        }
                        else{
                            board[a][i].symbol = '.'; // Revert if not winning
                            board[a][i].statu = 0;
                            break;
                        }
                    }
                }      
            } 
            bool flag = 0;
            // 2. Check if Player X is about to win and block them
            for(int i = 0; i < cols; i++){
                for(int a = rows - 1; a >= 0; a-- ){
                    if(board[a][i].statu == 0){
                        board[a][i].symbol = 'X';
                        board[a][i].statu = 1;
                        if(win()){
                            board[a][i].symbol = 'C'; // Block the spot
                            cout << "Computer played in collumn " << char('a' + i) << endl;
                            printboard();
                            flag = 1;
                            break; 
                            
                        }
                        else{
                            board[a][i].symbol = '.';
                            board[a][i].statu = 0;
                            break;
                        }
                    }
                }      
            }
            
            // 3. If no win or block, play a random available column
            if(flag == 0){
                
                int * availablecols = new int[cols];
                int count = 0;
                for(int i = 0; i < cols; i++){
                    for(int a = 0; a < rows; a++){
                        if(board[a][i].statu == 0){
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
                for(int b = rows - 1; b >= 0; b-- ){
                    if(board[b][randcol].statu == 0){
                        board[b][randcol].symbol = 'C';
                        board[b][randcol].statu = 1;
                        cout << "Computer played in collumn " << char('a' + randcol) << endl;
                        flag = 1;
                        break;
                    }
                }
            }
        }              

        // Main game loop and menu system
        void playgame(){
            cout<<"welcome to connect four game!"<<endl;
            cout<<" MENU "<<endl;
            cout<<" 1- play with another player "<<endl;
            cout<<" 2- play with computer "<<endl;
            cout<<" enter your choice : ";
            int choice;
            cin>> choice;
            if(choice == 1){ // PvP Mode
                    char move;
                    while(1){
                        printboard();
                        cout<<"player 1 enter your move (a - "<< char('a' + cols - 1) <<") : ";
                        cin>> move;
                        play(move,'X');
                        printboard();
                        cout<<"player 2 enter your move (a - "<< char('a' + cols - 1) <<") : ";
                        cin>> move;
                        play(move,'O');
                    }    
                
            }
                           
            else if(choice == 2){ // PvC Mode
                
                    char move;
                    while(1){
                        printboard();
                        cout<<"your turn enter your move (a - "<< char('a' + cols - 1) <<") : ";
                        cin>> move;
                        play(move,'X');
                        play(); // Computer moves
                    }    
                
            }
                
            
            else{
                cout<<"invalid choice exiting the game "<<endl;
                exit(1);

            }
        }
                        
             
            
        
};

int main(){
    connectfour game("board3.txt"); // Initialize game using board.txt
    game.playgame();
    

    return 0;
}