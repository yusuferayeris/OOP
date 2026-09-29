#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "connectfourplus.h"
#include <vector>

namespace YusufEray{
    class connectfourplusundo : public connectfourplus {
    public:
        connectfourplusundo();
        connectfourplusundo(int w, int h);
        void play(char col, char symbol) override;
        void play() override;
        void undo();
    private:
        std::vector<int> history;
    };
}

#endif