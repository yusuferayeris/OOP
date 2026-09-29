#ifndef CELL_H
#define CELL_H
#include<iostream>
using namespace std;

namespace YusufEray{
    class cell{
        private:
            char player;
            char colposition;
            int rowposition;
            
        public:
            cell();
            void setrow(int r);
            void setcol(char c);
            void setplayer(char c);
            

            int getrow() const;
            char getcol() const;
            char getplayer() const;
        

            cell& operator++();
            cell operator++(int);
            friend ostream& operator<<(ostream& os,const cell& c);

            bool operator==(const cell& other);

    };
}
#endif