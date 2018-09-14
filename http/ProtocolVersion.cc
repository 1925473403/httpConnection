#include "ProtocolVersion.h"
#include "CharArrayBuffer.h"
ProtocolVersion::ProtocolVersion(std::string &p, int ma, int mi):protocol(p), maj(ma), min(mi) {
    if (p.length() == 0) throw IllegalArgumentException("Protocol name must not be null.");
    if (maj < 0) throw IllegalArgumentException("Protocol maj version number must not be negative.");
    if (min < 0) throw IllegalArgumentException("Protocol min version number may not be negative");
}
ProtocolVersion::ProtocolVersion(const char *p, int ma, int mi):protocol(p), maj(ma), min(mi) {
    if ((p == NULL) || (strlen(p) == 0))  throw IllegalArgumentException("Protocol name must not be null.");
    if (maj < 0) throw IllegalArgumentException("Protocol maj version number must not be negative.");
    if (min < 0) throw IllegalArgumentException("Protocol min version number may not be negative");
}
std::string ProtocolVersion::getProtocol() const { return protocol; }
ProtocolVersion::ProtocolVersion(const ProtocolVersion& rhs) {
    protocol = rhs.getProtocol();
    maj = rhs.getMajor();
    min = rhs.getMinor();
}
ProtocolVersion& ProtocolVersion::operator=(const ProtocolVersion &rhs) {
    if (this != &rhs) {
        protocol = rhs.getProtocol();
        maj = rhs.getMajor();
        min = rhs.getMinor();
    }
    return *this;
}
ProtocolVersion* ProtocolVersion::forVersion(int ma, int mi) {
    if (getMajor() == ma && getMinor() == mi) return this;
    return new ProtocolVersion(protocol, ma, mi);
}
long ProtocolVersion::hashCode() {
    long hash = std::hash<std::string> { } (protocol);
    hash ^= (std::hash<int>{ } (maj));
    hash ^= (std::hash<int>{ } (min));
    return hash;
}
bool ProtocolVersion::equals(ProtocolVersion &rhs) const {
    if (this == &rhs) return true;
    return (protocol == rhs.getProtocol() && (maj == rhs.getMajor()) && (min == rhs.getMinor()));
}
bool ProtocolVersion::isComparable(ProtocolVersion &rhs) const {
    return equals(rhs);
}
int ProtocolVersion::compareToVersion(ProtocolVersion &rhs) const {
    if (protocol != rhs.getProtocol()) throw IllegalArgumentException("Versions for different protocols cannot be compared. %s %s", protocol.c_str(), rhs.getProtocol().c_str());
    int delta = getMajor() - rhs.getMajor();
    if (delta == 0) delta = getMinor() - rhs.getMinor();
    return delta;
}
bool ProtocolVersion::greaterEquals(ProtocolVersion &version) const {
    return isComparable(version) && (compareToVersion(version) >= 0);
}
bool ProtocolVersion::lessEquals(ProtocolVersion &version) const {
    return isComparable(version) && (compareToVersion(version) <= 0);
}
std::string ProtocolVersion::toString() {
    CharArrayBuffer buffer(16);
    buffer.append(protocol);
    buffer.append('/');
    buffer.append(maj);
    buffer.append('.');
    buffer.append(min);
    return buffer.toString();
}
