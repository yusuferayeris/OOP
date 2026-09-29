#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "connectfourabstract.h"

namespace YusufEray{
    
    class connectfourplus : public connectfourabstract{
        public:
        connectfourplus();
        connectfourplus(int w, int h);
        bool vertical(cell ** c,int i,int y);
        bool horizontal(cell ** c,int x, int y);
        bool iswin() override;
        bool isgameend() override;

    };
}



#endif