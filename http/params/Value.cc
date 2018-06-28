#ifndef VALUE_H
#include "Value.h"
#endif
ostream& operator<<(ostream &os, ValueBase &rhs) {
    rhs.output(os);
    return os;
}

bool equalsIgnoreCase(std::string s, std::string t) {
    return strcasecmp(s.c_str(), t.c_str()) == 0;
}
