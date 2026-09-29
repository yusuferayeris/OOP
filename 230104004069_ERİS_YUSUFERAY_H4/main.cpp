#include <iostream>
#include <string>
#include "connectfourabstract.h"
#include "connectfourplus.h"
#include "connectfourdiag.h"
#include "connectfourplusundo.h"

using namespace std;
using namespace YusufEray;

int main() {
    char mode;
    cout << "---------------------------------------" << endl;
    cout << "Welcome to Connect Four Game!" << endl;
    cout << "Select Game Mode:" << endl;
    cout << "P : Connect Four PLUS (Only Horizontal/Vertical wins)" << endl;
    cout << "D : Connect Four DIAG (Only Diagonal wins)" << endl;
    cout << "U : Connect Four PLUS with UNDO feature" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter mode: ";
    cin >> mode;

    connectfourabstract *game = nullptr;

    if (mode == 'P' || mode == 'p') {
        game = new connectfourplus();
        cout << "Mode selected: PLUS" << endl;
    } 
    else if (mode == 'D' || mode == 'd') {
        game = new connectfourdiag();
        cout << "Mode selected: DIAG" << endl;
    }
    else if (mode == 'U' || mode == 'u') {
        game = new connectfourplusundo();
        cout << "Mode selected: PLUS with UNDO" << endl;
    }
    else {
        cout << "Invalid selection! Defaulting to PLUS mode." << endl;
        game = new connectfourplus();
    }

    try {
        game->playgame();
    }
    catch(const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    delete game; 

    return 0;
}