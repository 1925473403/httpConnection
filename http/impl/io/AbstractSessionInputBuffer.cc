#include "HttpException.h"
#ifndef ABSTRACTSESSIONINPUTBUFFER_H
#include "AbstractSessionInputBuffer.h"
#endif
int AbstractSessionInputBuffer::locateLF() {
    for (int i = bufferpos; i < bufferlen; i++) 
        if (buffer[i] == HTTP::LF) return i;
    return -1;
}
void AbstractSessionInputBuffer::init(InputStream *ins, int buffersize, HttpParams *params) : linebuffer(buffersize) {
    if (ins == NULL) throw IllegalArgumentException("Input stream may not be null");
    if (buffersize <= 0) throw IllegalArgumentException("Buffer size may not be negative or zero");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    instream = ins;
    buffer = new char[buffersize];
    bytebufferlen = buffersize;
    bufferpos = 0;
    bufferlen = 0;
    charset = HttpProtocolParams::getHttpElementCharset(params);
    ascii = (equalsIgnoreCase(HTTP::US_ASCII, charset) || equalsIgnoreCase(HTTP::ASCII, charset));
    maxLineLen = params->getIntParameter(CoreConnectionPNames::MAX_LINE_LENGTH, -1);
}
int AbstractSessionInputBuffer::fillBuffer() throw (IOException) {
    if (bufferpos > 0) {
        int len = bufferlen - bufferpos;
        if (len > 0) {
            for (int i = 0; i < len; i++) {
                buffer[i] = buffer[i+bufferpos];
            }
            bufferpos = 0;
            bufferlen = len;
        }
    }
    int l, off = bufferlen, len = bytebufferlen - bufferlen;
    l = instream->read(buffer, off, len);
    if (l == -1) return -1;
    else {
        bufferlen = off + l;
        return l;
    }
}
bool AbstractSessionInputBuffer::hasBufferedData() {
    return bufferpos < bufferlen;
}
int AbstractSessionInputBuffer::read () throw (IOException) {
    int noRead = 0;
    while (!hasBufferedData()) {
        noRead = fillBuffer();
        if (noRead == -1) return -1;
    }
    return buffer[bufferpos++] & 0xff;
}
int AbstractSessionInputBuffer::read(byte *b, int off, int len) throw (IOException) {
    if (b == NULL) return 0;
    int noRead = 0;
    while (!hasBufferedData()) {
        noRead = fillBuffer();
        if (noRead == -1) return -1;
    }
    int chunk = bufferlen - bufferpos;
    if (chunk > len) chunk = len;
    memcpy(b + off, buffer + bufferpos, chunk);
    bufferpos += chunk;
    return chunk;
}
int AbstractSessionInputBuffer::read(byte *b, int len) throw (IOException) {
    if (b == NULL) return 0;
    return read(b, 0, len);
}
int AbstractSessionInputBuffer::readLine(CharArrayBuffer &charbuffer) throw (IOException) {
    linebuffer.clear();
    int noRead= 0;
    bool retry = true;
    while (retry) {
        int i = locateLF();
        if (i != -1) {
            if (linebuffer.isEmpty()) return lineFromReadBuffer(charbuffer, i);
            retry = false;
            int len = i + 1 - bufferpos;
            linebuffer.append(buffer, bufferpos, len);
            bufferpos = i + 1;
        } else {
            if (hasBufferedData()) {
                int len = bufferlen - bufferpos;
                linebuffer.append(buffer, bufferpos, len);
                bufferpos = bufferlen;
            }
            noRead = fillBuffer();
            if (noRead == -1) retry = false;
        }
        if (maxLineLen > 0 && linebuffer.length() >= maxLineLen) throw IOException("Maximum line length limit exceeded");
    }
    if (noRead == -1 && linebuffer.isEmpty()) return -1;
    return lineFromLineBuffer(charbuffer);
}
int AbstractSessionInputBuffer::lineFromLineBuffer(CharArrayBuffer &charbuffer) throw (IOException) {
    int l = linebuffer.length();
    if (l > 0) {
        if (linebuffer.byteAt(l - 1) == HTTP::LF) {
            l--
            linebuffer.setLength(l);
        }
        if (l > 0) {
            if (linebuffer.byteAt(l - 1) == HTTP::CR) {
                l--;
                linebuffer.setLength(l);
            }
        }
    }
    l = linebuffer.length();
    /*
    if (ascii) charbuffer.append(linebuffer, 0, l);
    else {
        
    }
    */
    charbuffer.append(linebuffer, 0, l);
    return l;
}
int AbstractSessionInputBuffer::lineFromReadBuffer(CharArrayBuffer &charbuffer, int pos) throw (IOException) {
    int off = bufferpos;
    int len;
    bufferpos = pos + 1;
    if (pos > off && buffer[pos - 1] == HTTP::CR) pos --;
    len = pos - off;
    charbuffer.append(buffer, off, len);
    return len;
}
std::string readLine() throw (IOExecption) {
    CharArrayBuffer charbuffer(64);
    int l = readLine(charbuffer);
    if (l != -1) return charbuffer.toString();
    return "";
}
