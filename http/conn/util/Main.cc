#include <regex>
#include <iostream>
#include <string>
#include "InetAddressUtils.h"
using namespace std;

int main () {
    //regex r ("25[0-5]|2[0-4][[:d:]]|[0-1]?[[:d:]]?[[:d:]]");
    try {
        std::string ipaddr;
        std::getline(std::cin, ipaddr);
        if (InetAddressUtils::isIPv4Address(ipaddr)) std::cout << "Ipv4 addr: " << ipaddr << std::endl;
    } catch (const std::regex_error &e) {
        std::cerr << "regex_error caught: " << e.what() << std::endl;
    }
    return 0;
}
