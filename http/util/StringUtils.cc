#include <string.h>
#include <string>
using namespace std;
#include "StringUtils.h"

bool equalsIgnoreCase(std::string s, std::string anotherString) {
    return (strcasecmp(s.c_str(), anotherString.c_str()) == 0);
}

bool starts_with(std::string requestUri, std::string pattern) {
    int to = 0;
    int po = 0;
    int pc = pattern.length();
    if (requestUri.length() - pc < 0) return false;
    while (--pc >= 0) {
        if (requestUri[to++] != pattern[po]) return false;
    }
    return true;
}

bool ends_with(std::string requestUri, std::string pattern) {
    int toffset = requestUri.length() - pattern.length();
    int to = toffset;
    int po = 0;
    int pc = pattern.length();
    if ((toffset < 0) || (toffset > requestUri.length() - pc)) return false;
    while (--pc >= 0) {
        if (requestUri[to++] != pattern[po++]) return false;
    }
    return true;
}

void toLowerCase(std::string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
}

void toUpperCase(std::string s) {
    for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
}
