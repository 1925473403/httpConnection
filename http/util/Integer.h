#include "HttpException.h"
class Integer {
    Integer();
    Integer(const Integer &);
    Integer& operator=(const Integer &);
    public:
        static int parseInt(const char *str) {
            int x = 0;
            for (int i = 0; i < strlen(str); i++) {
                if (i == 0 && (str[i] == '-' || str[i] =='+')) continue;
                if (i != 0 && (str[i] == '-' || str[i] =='+')) throw NumberFormatException("%s is not a number", str);
                if (!isdigit(str[i])) throw NumberFormatException("%s is not a number", str);
            }
            if (str != NULL) {
                x = atoi(str);
            }
            return x;
        }
        static std::string toString(const int x) {
            char str[128] = { 0 };
            snprintf(str, 127, "%d", x);
            return std::string(str);
        }
        static int parseInt(std::string s) {
            return Integer::parseInt(s.c_str());
        }
        static std::string toHexString(int i) {
            stringstream s;
            s << std::hex << i ;
            return s.str();
        }
};
