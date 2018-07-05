#include "HttpException.h"
#ifndef ABSTRACTSESSIONOUTPUTBUFFER_H
#include "AbstractSessionOutputBuffer.h"
#endif
char AbstractSessionOutputBuffer::CLRF[2] = { HTTP::CR, HTTP::LF };
int AbstractSessionOutputBuffer::MAX_CHUNK = 256;
void AbstractSessionOutputBuffer::init(OutputStream *oustream, int buffersize, HttpParams *params) : buffer(buffersize) {
    if (oustream == NULL) throw IllegalArgumentException("Input stream may not be null");
    if (buffersize < 0) throw IllegalArgumentException("Buffer size may not be negative or zero");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    outstream = oustream;
    charset = HttpProtocolParams::getHttpElementCharset(params);
    ascii = (equalsIgnoreCase(HTTP::US_ASCII, charset) || equalsIgnoreCase(HTTP::ASCII, charset));
}
void AbstractSessionOutputBuffer::flushBuffer () throw (IOException) {
    int len = buffer.length();
    if (len > 0) {
        outstream->write(buffer.buffer(), 0, len);
        buffer.clear();
    }
}
void AbstractSessionOutputBuffer::flush() throw(IOException) {
    flushBuffer();
    outstream->flush();
}
void AbstractSessionOutputBuffer::write(byte *b, int off, int len) throw (IOException) {
    if (b == NULL) return;
    if (len > AbstractSessionOutputBuffer::MAX_CHUNK || len > buffer.capacity()) {
        flushBuffer();
        outstream->write(b, off, len);
    } else {
        int freecapacity = buffer.capacity() - buffer.length();
        if (len > freecapacity) {
            flushBuffer();
        }
        buffer.append(b, off, len);
    }
}
void AbstractSessionOutputBuffer::write(byte *b, int len) throw (IOException) {
    if (b == NULL) { return; }
    write(b, 0, len);
}
void AbstractSessionOutputBuffer::write(int b) throw (IOException) {
    if (buffer.isFull()) flushBuffer();
    buffer.append(b);
}
void AbstractSessionOutputBuffer::writeLine(std::string s) throw (IOException) {
    if (s == "") return;
    if (s.length() > 0) write(s.data(), s.length());
    write(CRLF, 2);
}
void AbstractSessionOutputBuffer::writeLine(CharArrayBuffer &s) throw (IOException) {
    int off = 0;
    int remaining  = s.length();
    while (remaining > 0) {
        int chunk = buffer.capacity() - buffer.length();
        chunk = std::min<int>(chunk, remaining);
        if (chunk > 0) buffer.append(s, off, chunk);
        if (buffer.isFull()) flushBuffer();
        off += chunk;
        remaining -= chunk;
    }
    write(CRLF, 2);
}
