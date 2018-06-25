#include "HttpException.h"
#ifndef PROTOCOLVERSION_H
#define PROTOCOLvERSION_H
class ProtocolVersion {
    protected:
        std::string protocol;
        int maj;
        int min;
    public:
        ProtocolVersion(std::string p, int ma, int mi) ;
        virtual ~ProtocolVersion() { }
        std::string getProtocol() const ;
        int getMajor() const { return maj; }
        int getMinor() const { return min; }
        ProtocolVersion(const ProtocolVersion& rhs) ;
        ProtocolVersion& operator=(const ProtocolVersion &rhs) ;
        ProtocolVersion* forVersion(int ma, int mi) ;
        long hashCode() ;
        bool equals(ProtocolVersion &rhs) const ;
        bool isComparable(ProtocolVersion &rhs) const ;
        int compareToVersion(ProtocolVersion &rhs) const ;
        bool greaterEquals(ProtocolVersion &version) const ;
        bool lessEquals(ProtocolVersion &version) const ;
        std::string toString() ;
};
#endif
