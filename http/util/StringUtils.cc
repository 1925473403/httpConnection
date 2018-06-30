#include "StringUtils.h"

bool equalsIgnoreCase(std::string s, std::string anotherString) {
    return (strcasecmp(s.c_str(), anotherString.c_str()) == 0);
}
