#include "HttpException.h"
#ifndef WIRE_H
#define WIRE_H
class Wire {
    typedef unsigned char byte;
    void wire(std::string &header, InputStream *instream) throw(IOException);
    public:
    Wire(Log &l);
    bool enabled();
    void output(InputStream *outstream) throw (IOException);
    void input(InputStream *instream) throw (IOException);
    void output(byte b[], int size, int off, int len) throw(IOException);
    void input(byte b[], int size, int off, int len) throw(IOException);
    void output(byte b[], int size) throw(IOException);
    void input(byte b[], int size) throw(IOException);
    void output(int b) throw(IOException);
    void input(int b) throw(IOException);
    void output(std::string &s) throw(IOException);
    void input(std::string &s) throw(IOException);
};
#endif
