#include "HttpException.h"
#ifndef PARSERCURSOR_H
#define PARSERCURSOR_H
class ParserCursor {
    int lowerBound;
    int upperBound;
    int pos;
    public:
        ParserCursor(int l, int u) ;
        int getLowerBound() const { return lowerBound; }
        int getUpperBound() const { return upperBound; }
        int getPos() const { return pos; }
        void updatePos(int pos);
        bool atEnd() const { return pos >= upperBound; }
        std::string toString();
};
#endif
