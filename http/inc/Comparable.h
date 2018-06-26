#include "HttpException.h"
#ifndef COMPARABLE_H
#define COMPARABLE_H
template <class T> class Comparable {
    public :
        int compareTo(T &o);
};
#endif
