#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
using namespace std;


int main() {
    std::string filename ; /*cin >> filename;*/
    filename="my.txt";
    ifstream ifs(filename.c_str(), std::ifstream::in);
    ifs.seekg(0, ifs.end);
    long size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char arr[size + 1] ; arr[size] = 0;
    ifs.read(arr, size);
    filename.assign(arr);

    for (int i = filename.find("<li>"); i != string::npos; i = filename.find("<li>", i)) {
        int j = filename.find("</li>", i);
        if (j != string::npos) {
            int ahrefstart = filename.find("<a href=", i + 1);
            ahrefstart += strlen("<a href=\"");
            int ahrefend = filename.find("\" title=\"", ahrefstart);
            int titlestart = ahrefend + strlen("\" title=\"");
            int titleend = filename.find("\">", titlestart);
            std::cout << filename.substr(ahrefstart, ahrefend - ahrefstart) << " - " << filename.substr(titlestart, titleend - titlestart) << std::endl;
            i = j;
            j += strlen("</li>");
/*
            if ((filename[j+0] == '<') &&
                (filename[j+1] == '/') &&
                (filename[j+2] == 'u') &&
                (filename[j+3] == 'l') &&
                (filename[j+4] == '>'))
                break;
*/
        }
    }
    return 0;
}
