#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include "cell.h"
#include <string>
#include <iostream>

namespace YusufEray{
    class connectfourabstract{
        protected:
            cell ** board;
            int width;
            int height;
        public:
            connectfourabstract();
            connectfourabstract(int w, int h);
            void display();
            virtual ~connectfourabstract();
            virtual void play();
            virtual void play(char col, char symbol);

            char readfromfile(std::string filename);
            void writetofile(std::string filename, char player);


            bool virtual isgameend() = 0;
            bool virtual iswin() = 0;

            void playgame();


    };
}
#endif