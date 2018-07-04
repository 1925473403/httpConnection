#ifndef VALUE_H
#include "Value.h"
#endif
ostream& operator<<(ostream &os, ValueBase &rhs) {
    rhs.output(os);
    return os;
}
