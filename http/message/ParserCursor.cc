#include "CharArrayBuffer.h"
#include "Integer.h"
#include "ParserCursor.h"
ParserCursor::ParserCursor(int l, int u):lowerBound(l), upperBound(u), pos(l) {
    if (lowerBound < 0) throw IndexOutOfBoundsException("Lower bound cannot be negative");
    if (lowerBound > upperBound) throw IndexOutOfBoundsException("Lower bound cannot be greater then upper bound");
}
void ParserCursor::updatePos(int pos) {
    if (pos < lowerBound) throw IndexOutOfBoundsException();
    if (pos > upperBound) throw IndexOutOfBoundsException();
    pos = pos;
}
std::string ParserCursor::toString() {
    CharArrayBuffer buffer(16);
    buffer.append('[');
    buffer.append(Integer::toString(lowerBound).c_str());
    buffer.append('>');
    buffer.append(Integer::toString(pos).c_str());
    buffer.append('>');
    buffer.append(Integer::toString(upperBound).c_str());
    buffer.append(']');
    return buffer.toString();
}
