#include "HttpException.h"
#ifndef CHUNKEDOUTPUTSTREAM_H
#include "ChunkedOutputStream.h"
#endif
void ChunkedOutputStream::flushCache() throw (IOException) {
    if (cachePosition > 0) {
        out->writeLine(Integer::toHexString(cachePosition));
        out->write(cache, 0, cachePosition);
        out->writeLine("");
        cachePosition = 0;
    }
}

void ChunkedOutputStream::flushCacheWithAppend(byte *bufferToAppend, int off, int len) throw (IOException) {
    out->writeLine(Integer::toHexString(cachePosition + len));
    out->write(cache, 0, cachePosition);
    out->write(bufferToAppend, off, len);
    out->writeLine("");
    cachePosition = 0;
}

void ChunkedOutputStream::writeClosingChunk() throw (IOException) {
    out->writeLine("0");
    out->writeLine("");
}

ChunkedOutputStream::ChunkedOutputStream(SessionOutputBuffer *outbuf, int bufferSize) : cachePosition(0), cachelen(buffersize), wroteLastChunk(false), closed(false) {
    cache = new byte[cachelen];
    out = outbuf;
}

ChunkedOutputStream::ChunkedOutputStream(SessionOutputBuffer *outbuf) : ChunkedOutputStream(outbuf, 2048) {
}

ChunkedOutputStream::ChunkedOutputStream(const ChunkedOutputStream &rhs) {
    delete[] cache;
    cachelen = rhs.cachelen;
    cache = new byte[rhs.cachelen];
    memcpy(cache, rhs.cache, cachelen);
    cachePosition = rhs.cachePosition;
    wroteLastChunk = rhs.wroteLastChunk;
    closed = rhs.wroteLastChunk;
    out = rhs.out;
}
ChunkedOutputStream& ChunkedOutputStream::operator=(const ChunkedOutputStream &rhs) {
    if (this != &rhs) {
        delete[] cache;
        cachelen = rhs.cachelen;
        cache = new byte[rhs.cachelen];
        memcpy(cache, rhs.cache, cachelen);
        cachePosition = rhs.cachePosition;
        wroteLastChunk = rhs.wroteLastChunk;
        closed = rhs.wroteLastChunk;
        out = rhs.out;
    }
    return *this;
}
void ChunkedOutputStream::finish() throw (IOException) {
    if (!wroteLastChunk) {
        flushCache();
        writeClosingChunk();
        wroteLastChunk = true;
    }
}

void ChunkedOutputStream::write(int b) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    cache[cachePosition] = (byte) b;
    cachePosition++;
    if (cachePosition == cachelen) flushCache();
}

void ChunkedOutputStream::write(byte *b, int blen) throw (IOException) {
    write(b, 0, blen);
}

void ChunkedOutputStream::write(byte *b, int off, int len) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    if (len >= cachelen - cachePosition) flushCacheWithAppend(src, off, len);
    else {
        memcpy(cache + cachePosition, b + off, len);
        cachePosition += len;
    }
}

void ChunkedOutputStream::flush() throw (IOException) {
    flushCache();
    out->flush();
}

void ChunkedOutputStream::close() throw (IOException) {
    if (!closed) {
        closed = true;
        finish();
        out->flush();
    }
}
