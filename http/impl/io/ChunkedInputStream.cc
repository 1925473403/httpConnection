#include "HttpException.h"
#ifndef CHUNKEDINPUTSTREAM_H
#include "ChunkedInputStream.h"
#endif
void ChunkedInputStream::nextChunk() throw (IOException) {
    chunkSize = getChunkSize();
    if (chunkSize < 0) throw MalformedChunkCodingException("Negative chunk size");
    bof = false;
    pos = 0;
    if (chunkSize == 0) {
        eof = true;
        parseTrailerHeaders();
    }
}
int ChunkedInputStream::getChunkSize() throw (IOException) {
    int len = -1;
    if (!bof) {
        int cr = in->read();
        int lf = in->read();
        if ((cr != HTTP::CR) || (lf != HTTP::LF)) throw MalformedChunkCodingException("CRLF expected at end of chunk");
    }
    buffer.clear();
    int i = in->readLine(buffer);
    if (i == -1) throw MalformedChunkCodingException("Chunked stream ended unexpectedly");
    int separator = buffer.indexOf(';');
    if (separator < 0) separator = buffer.length();
    try {
        len = Integer::parseInt(buffer.substringTrimmed(0, separator));
    } catch (const NumberFormatException &e) {
        throw MalformedChunkCodingException("Bad chunk header");
    }
    return len;
}
void ChunkedInputStream::parseTrailerHeaders() throw (IOException) {
    try {
        AbstractMessageParser::parseHeaders(in, -1, -1, NULL, footers);
    } catch (const HttpException &e) {
        throw;
    }
}
ChunkedInputStream::ChunkedInputStream(SessionInputBuffer *inbuf) : buffer(16) {
    if (inbuf == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    in = inbuf;
    pos = 0;
}
int ChunkedInputStream::read() throw (IOException) {
    if (closed) throw IOException("Attempted read from closed stream.");
    if (eof) return -1;
    if (pos >= chunkSize) {
        nextChunk();
        if (eof) return -1;
    }
    pos++;
    return in->read();
}
int ChunkedInputStream::read (byte *b, int blen, int off, int len) throw (IOException) {
    if (closed) throw IOException("Attempted read from closed stream.");
    if (eof) return -1;
    if (pos >= chunkSize) {
        nextChunk();
        if (eof) return -1;
    }
    len = std::min<int>(len, chunkSize - pos);
    int count = in->read(b, blen, off, len);
    pos += count;
    return count;
}
int ChunkedInputStream::read(byte *b, int blen) throw (IOException) {
    return read(b, 0, blen);
}
void ChunkedInputStream::close() throw (IOException) {
    if (!closed) {
        try {
            if (!eof) exhaustInputStream(this);
        } catch (...) { }
        eof = true;
        closed = true;
    }
}
void ChunkedInputStream::getFooters(vector<Header *> &res) {
    for (int i = 0; i < footers.size(); i++) res.push_back(footers[i]);
}
void ChunkedInputStream::exhaustInputStream(InputStream *inStream) throw (IOException) {
    byte buffer[1024];
    while (inStream->read(buffer) >= 0) ;
}
