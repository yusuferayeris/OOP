#ifndef CONNECTFOURDİAG_H
#define CONNECTFOURDİAG_H
#include "connectfourabstract.h"

namespace YusufEray{
    class connectfourdiag : public connectfourabstract{
        public:
            connectfourdiag();
            connectfourdiag(int w, int h);

            bool diagonal1(cell ** c, int i , int y);
            bool diagonal2(cell ** c, int i , int y);
            bool iswin() override;
            bool isgameend() override;

    };
}

#endif