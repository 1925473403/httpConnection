#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "HttpDateGenerator.h"
using namespace std;

int main() {
    HttpDateGenerator d;
    for (int i = 0; i < 10 && !(sleep(1)); i++)
        std::cout << d.getCurrentDate() << std::endl;
    return 0;
}
