#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <exception>
#include <assert.h>
#include <errno.h>

#ifndef __utils_h__
#define __utils_h__

typedef struct pcap_hdr_s {
    uint32_t magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
} pcap_hdr_t;

typedef struct pcaprec_hdr_s {
    uint32_t ts_sec;         /* timestamp seconds */
    uint32_t ts_usec;        /* timestamp microseconds */
    uint32_t incl_len;       /* number of octets of packet saved in file */
    uint32_t orig_len;       /* actual length of packet */
    uint64_t unused;
} pcaprec_hdr_t;

class snoopFile {
    public:
        snoopFile(char *snoopFileName);
        snoopFile(int snoopFilefd = 0);
        ~snoopFile();

        int getNextFrame(unsigned char *apStr, size_t len);
        int openSnoopFile();
        off_t getSize();
        int getFrameCount();
        void getEpocTime(double &epocTime);
        void getDeltaTime(double &deltaTime);
        void dumpPackets(unsigned char *packetBuffer, size_t packetLen);
        void getDst(unsigned char*, int);
        void getSrc(unsigned char *, int);
        off_t getoffset() const ;
        void setdebug(int d) { debug = d; }
    private:
        snoopFile(const snoopFile &rhs);
        snoopFile& operator=(const snoopFile&);

        void computeFrameLenAndCapturedBytes(unsigned char *ipBuffer, int *frameLen, int *capturedBytes, int *packetRecordLength, int swapLen);
        void computePacketLen(unsigned char *ipBuffer, int *packetLen);
        void computeEpochTime(unsigned char *ipBuffer, size_t *seconds, size_t *nanoseconds, int);
        void assertLens(int readLen, int packetLen);
        void readSrcAndDst(unsigned char *ipBuffer, int *packetLen);

        int m_snoopFilefd;
        int offset;
        int m_frameCnt;
        off_t m_snoopFileSize;
        char *m_snoopFileName;
        size_t seconds;
        size_t nanoseconds;
        size_t prev_seconds;
        size_t prev_nanoseconds;
        char srcAddr[32];
        char dstAddr[32];
        int debug;
};

class FileReadException: public std::exception {
    public:
        FileReadException(const char *fileName) {
            if ((fileName) && (fileName != NULL))
                snprintf(m_reason, 511, "%s", fileName);
        }
        const char *what() const throw() {
            return m_reason;
        }
        int describe(char* apStr, size_t len) {
            if ((apStr) && (apStr != NULL)) {
                return snprintf(apStr, len, "%s", m_reason);
            }
            return 0;
        }
    private:
        char m_reason[512];
};

class FileOpenException : public std::exception {
    public:
        FileOpenException(const char *fileName) {
            if ((fileName) && (fileName != NULL))
                snprintf(m_reason, 511, "Cannot open file: %s", fileName);
        }
        const char *what() const throw() {
            return m_reason;
        }
        int describe(char* apStr, size_t len) {
            if ((apStr) && (apStr != NULL)) {
                return snprintf(apStr, len, "%s", m_reason);
            }
            return 0;
        }
    private:
        char m_reason[512];
};

class FileEndException : public std::exception {
    public:
        FileEndException(const char *fileName) {
            if ((fileName) && (fileName != NULL))
                snprintf(m_reason, 511, "Reached end of file: %s", fileName);
        }
        const char *what() const throw() {
            return m_reason;
        }
        int describe(char* apStr, size_t len) {
            if ((apStr) && (apStr != NULL)) {
                return snprintf(apStr, len, "%s", m_reason);
            }
            return 0;
        }
    private:
        char m_reason[512];
};

#endif
