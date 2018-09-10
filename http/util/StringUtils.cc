#include <string.h>
#include <string>
using namespace std;
#include "StringUtils.h"

int compareIgnoreCase(std::string &c1, std::string &c2) {
    int n1 = c1.length(), n2 = c2.length();
    int min = std::min<int> (n1, n2);
    for (int i = 0; i < min; i++) {
        char ch1 = c1[i], ch2 = c2[i];
        if (ch1 != ch2) {
            ch1 = toupper(ch1);
            ch2 = toupper(ch2);
            if (ch1 != ch2) {
                ch1 = tolower(ch1);
                ch2 = tolower(ch2);
                if (ch1 != ch2) return ch1 - ch2;
            }
        }
    }
    return n1 - n2;
}

std::string& trim(std::string &s) {
    int i = 0, j = s.length() - 1, k;
    while (s[i] == ' ') i++;
    while (s[j] == ' ') j--;
    for (k = 0; i <= j; k++) s[k] = s[i++];
    s.resize(k);
    return s;
}

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

void toLowerCase(std::string &s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
}

void toUpperCase(std::string &s) {
    for (int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
}
