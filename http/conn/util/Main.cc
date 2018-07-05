#include <regex>
#include <iostream>
#include <string>
using namespace std;

int main () {
    //regex r ("25[0-5]|2[0-4][[:d:]]|[0-1]?[[:d:]]?[[:d:]]");
    try {
    std::string regexStr = "";
    std::cout << "Enter regular expression : " ;
    std::getline(std::cin, regexStr);
    std::cout << "you entered: " << regexStr << std::endl;
    std::regex r(regexStr);
    std::string s = "";
    std::cout << "Enter integer between 1 - 255: " ;
    std::getline(std::cin, s);
    if (regex_match(s, r)) std::cout << "Regex matches : " << s << std::endl;
    } catch (const std::regex_error &e) {
        std::cerr << "regex_error caught: " << e.what() << std::endl;
    }
    return 0;
}
