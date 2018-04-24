#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <exception>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#ifndef __utils_h__
#include "utils.h"
#endif
using namespace std;
#include <iostream>

#define SNOOP_START_LEN 16
#define FRAME_START_LEN 24
#define ETHERNET_LEN 14
//#define SNOOP_START_LEN 24
//#define FRAME_START_LEN 16
//#define ETHERNET_LEN 16
#define IP_PKT_LEN 20
#define PKT_LEN_OFFSET 2
#define TCP_PKT_LEN 12
#define UDP_PKT_LEN 8


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;


snoopFile::snoopFile(char *snoopFileName) {
    memset(srcAddr, 0, 32);
    memset(dstAddr, 0, 32);
    m_snoopFilefd = -1;
    offset = -1;
    std::cout << "sizeof(pcap_hdr_t): " << sizeof(pcap_hdr_t) << ", sizeof(pcaprec_hdr_t): " << sizeof(pcaprec_hdr_t) << std::endl;
    if ((snoopFileName) && (snoopFileName != NULL)) {
        m_snoopFileName = new char[strlen(snoopFileName) + 1];
        strcpy(m_snoopFileName, snoopFileName);
        openSnoopFile();
    }
}

snoopFile::~snoopFile() {
    if (m_snoopFileName)
        delete[] m_snoopFileName;
    if (m_snoopFilefd != -1)
        close(m_snoopFilefd);
    m_snoopFilefd = -1;
    offset = -1;
}

void dump(pcap_hdr_t p_hdr) {
    std::cout << "Packet Header {" << std::endl;
    std::cout << "\tmagic_number: " << p_hdr.magic_number << std::endl;
    std::cout << "\tversion_major: " << p_hdr.version_major << std::endl;
    std::cout << "\tversion_minor: " << p_hdr.version_minor << std::endl;
    std::cout << "\tthiszone: " << p_hdr.thiszone << std::endl;
    std::cout << "\tsigfigs: " << p_hdr.sigfigs << std::endl;
    std::cout << "\tsnaplen: " << p_hdr.snaplen << std::endl;
    std::cout << "\tnetwork: " << p_hdr.network << std::endl;
    std::cout << "};" << std::endl;

}

void dump(pcaprec_hdr_t p_rechdr) {
    std::cout << "Record Packet Header: {" << std::endl;
    std::cout << "\ttimestamp seconds: " << p_rechdr.ts_sec << std::endl;
    std::cout << "\ttimestamp microseconds: " << p_rechdr.ts_usec << std::endl;
    std::cout << "\tincl_len: " << p_rechdr.incl_len << std::endl;
    std::cout << "\torig_len: " << p_rechdr.orig_len << std::endl;
    std::cout << "};" << std::endl;
}

int snoopFile::openSnoopFile() {
    struct stat l_statbuf;
    offset = -1;
    m_snoopFilefd = open(m_snoopFileName, O_RDONLY);
    if (m_snoopFilefd == -1)
        throw FileOpenException(m_snoopFileName);
    fstat(m_snoopFilefd, &l_statbuf);
    m_snoopFileSize = l_statbuf.st_size;
    pcap_hdr_t p_hdr;
    bzero(&p_hdr, sizeof(pcap_hdr_t));
    offset = read(m_snoopFilefd, (void *)&p_hdr, sizeof(pcap_hdr_t));
//    offset = lseek(m_snoopFilefd, SNOOP_START_LEN + 8, SEEK_CUR);
    dump(p_hdr);
    return offset;
}

off_t snoopFile::getoffset() const {
    return lseek(m_snoopFilefd, 0, SEEK_CUR);
}

snoopFile::snoopFile(int snoopFilefd) {
    struct stat l_statbuf;
    if (snoopFilefd > 0) {
        if (m_snoopFilefd != -1)
            close(m_snoopFilefd);
        m_snoopFilefd = snoopFilefd;
        fstat(m_snoopFilefd, &l_statbuf);
        m_snoopFileSize = l_statbuf.st_size;
    }
}

void snoopFile::computeFrameLenAndCapturedBytes(unsigned char *ipBuffer, int *frameLen, int *capturedBytes, int *packetRecordLength, int swapLen) {
    int i = 0;
    unsigned char frameLenChar[4] = { 0 }, capturedBytesChar[4] = { 0 }, packetRecordLengthChar[4] = { 0 };
    if (ipBuffer && frameLen && capturedBytes) {
        memcpy(frameLenChar, ipBuffer + 8, 4);
        if (!swapLen)
            for (; i < sizeof(uint32_t); i++)
                *frameLen = ((*frameLen) * 256) + frameLenChar[i];
        else
            for (i = 3; i >= 0; i--)
                *frameLen = ((*frameLen) * 256) + frameLenChar[i];
        if (debug)
            printf("[%d], frameLen: %d ", swapLen, *frameLen);
        memcpy(capturedBytesChar, ipBuffer + 12, 4);
        i = 0;
        if (!swapLen)
            for (; i < sizeof(uint32_t); i++)
                *capturedBytes = ((*capturedBytes) * 256) + capturedBytesChar[i];
        else
            for (i = 3; i >= 0; i--)
                *capturedBytes = ((*capturedBytes) * 256) + capturedBytesChar[i];
        if (debug)
            printf("capturedBytes: %d\n", *capturedBytes);
        
        memcpy(packetRecordLengthChar, ipBuffer + 8, 4);
        i = 0;
        if (!swapLen)
            for (; i < sizeof(uint32_t); i++)
                *packetRecordLength = ((*packetRecordLength) * 256) + packetRecordLengthChar[i];
        else
            for (i = 3; i >= 0; i--)
                *packetRecordLength = ((*packetRecordLength) * 256) + packetRecordLengthChar[i];
         
        if (debug)
            printf("packetRecordLength: %d\n", *packetRecordLength);

    }
    return;
}

void snoopFile::computePacketLen(unsigned char *ipBuffer, int *packetLen) {
    if (ipBuffer && packetLen) {
        *packetLen = (ipBuffer[2] * 256) + ipBuffer[3];
    }
    return;
}

void snoopFile::readSrcAndDst(unsigned char *ipBuffer, int *packetLen) {
    snprintf(srcAddr, 31, "%d.%d.%d.%d", ipBuffer[12], ipBuffer[13], ipBuffer[14], ipBuffer[15]);
    snprintf(dstAddr, 31, "%d.%d.%d.%d", ipBuffer[16], ipBuffer[17], ipBuffer[18], ipBuffer[19]);
}

void snoopFile::getDst(unsigned char* apStr, int len) {
    if (apStr && (len > strlen(dstAddr)))
        snprintf((char *)apStr, len - 1, "%s", dstAddr);
}

void snoopFile::getSrc(unsigned char *apStr, int len) {
    if (apStr && (len > strlen(srcAddr)))
        snprintf((char *)apStr, len - 1, "%s", srcAddr);
}

void snoopFile::assertLens(int readLen, int packetLen) {
    if (readLen != packetLen) {
        char msg[128] = { 0 };
        sprintf(msg, "readLen: %d != packetLen: %d\n", readLen, packetLen);
        throw FileReadException(msg);
    }
    return;
}

void snoopFile::dumpPackets(unsigned char *packetBuffer, size_t packetLen) {
    unsigned int i = 1;
    if (packetLen > 0) {
        printf("Frame[%d]: %d bytes\n", m_frameCnt, packetLen);
        for (; i < packetLen + 1; i++) {
            printf("%02x ", packetBuffer[i - 1]);
            if (i%16 == 0)
                printf("\n");
        }
        printf("\n");
    }
}

void snoopFile::computeEpochTime(unsigned char *ipBuffer, size_t *_seconds, size_t *_nanoseconds, int swapLen) {
    int i = 0;
    unsigned char secondsChar[4] = { 0 };
    unsigned char nanosecondsChar[4] = { 0 };

    memcpy(secondsChar, ipBuffer + 0, 4);
    memcpy(nanosecondsChar, ipBuffer + 4, 4);

    if (!swapLen)
        for (; i < sizeof(uint32_t); i++)
            *_seconds = (*_seconds << 8) + secondsChar[i];
    else
        for (i = 3; i >= 0; i--)
            *_seconds = (*_seconds << 8) + secondsChar[i];

    if (!swapLen)
        for (; i < sizeof(uint32_t); i++)
            *_nanoseconds = (*_nanoseconds << 8) + nanosecondsChar[i];
    else
        for (i = 3; i >= 0; i--)
            *_nanoseconds = (*_nanoseconds << 8) + nanosecondsChar[i];


    return;
}

off_t snoopFile::getSize() {
    return m_snoopFileSize;
}

int snoopFile::getFrameCount() {
    return m_frameCnt;
}

void snoopFile::getEpocTime(double &epocTime) {
    epocTime = ((double)seconds + ((double)nanoseconds * 0.000001));
    return;
}

void snoopFile::getDeltaTime(double &deltaTime) {
    deltaTime = ((double)seconds + ((double)nanoseconds * 0.000001)) - 
        ((double)prev_seconds + ((double)prev_nanoseconds * 0.000001));
    return;
}

int snoopFile::getNextFrame(unsigned char *packetBuffer, size_t readLen) {
    unsigned char ipBuffer[512] = { 0 };

    int packetLen = 0, tcpOctets = 0;
    int capturedBytes = 0, frameLen = 0, packetRecordLength = 0, proto = -1, padding = 0;

    if (offset == -1)
        return 0;

    while (offset < m_snoopFileSize) {
        // skip frame pkt which is 26 bytes
        readLen = read(m_snoopFilefd, ipBuffer, sizeof(pcaprec_hdr_t));
        pcaprec_hdr_t p_rechdr;
        bzero(&p_rechdr, sizeof(pcaprec_hdr_t));
        memcpy((void *)&p_rechdr, ipBuffer, sizeof(pcaprec_hdr_t));
        assertLens(readLen , sizeof(pcaprec_hdr_t));
        dump(p_rechdr);
        //dumpPackets(ipBuffer, readLen);
        //computeFrameLenAndCapturedBytes(ipBuffer, &frameLen, &capturedBytes, &packetRecordLength, 1);
        frameLen = p_rechdr.incl_len;
        packetRecordLength = p_rechdr.incl_len;
        capturedBytes = p_rechdr.orig_len;
        prev_seconds = seconds;
        prev_nanoseconds = nanoseconds;
        seconds = 0;
        nanoseconds = 0;
        //computeEpochTime(ipBuffer, &seconds, &nanoseconds, 1);
        seconds = p_rechdr.ts_sec; nanoseconds = p_rechdr.ts_usec;

        offset += sizeof(pcaprec_hdr_t);
        padding = packetRecordLength - capturedBytes - sizeof(pcaprec_hdr_t);
        //padding = capturedBytes - FRAME_START_LEN;

        //skip Ethernet pkt which is 14 bytes
        offset = lseek(m_snoopFilefd, ETHERNET_LEN, SEEK_CUR);
        capturedBytes -= ETHERNET_LEN;

        //skip IP packet which is 20 bytes
        readLen = read(m_snoopFilefd, ipBuffer, IP_PKT_LEN);
        assertLens(readLen , IP_PKT_LEN);
        computePacketLen(ipBuffer, &packetLen);
        readSrcAndDst(ipBuffer, &packetLen);
        if (ipBuffer[9] == 0x11)
            proto = 0;
        else if (ipBuffer[9] == 0x06)
            proto = 1;
        offset += IP_PKT_LEN;
        packetLen -= IP_PKT_LEN;
        capturedBytes -= IP_PKT_LEN;

        if (proto) {
            //skip tcp packet
            readLen = read(m_snoopFilefd, ipBuffer, TCP_PKT_LEN);
            assertLens(readLen , TCP_PKT_LEN);
            //dumpPackets(ipBuffer, readLen);
            offset += TCP_PKT_LEN;
            packetLen -= TCP_PKT_LEN;
            capturedBytes -= TCP_PKT_LEN;
            readLen = read(m_snoopFilefd, ipBuffer, 1);
            assertLens(readLen, 1);
            offset += 1;
            packetLen -= 1;
            capturedBytes -= 1;
            packetRecordLength -= 1;
            tcpOctets = ((ipBuffer[0] & 0xf0) >> 4);
            tcpOctets = (tcpOctets * 4) - TCP_PKT_LEN - 1;
            readLen = read(m_snoopFilefd, ipBuffer, tcpOctets);
            assertLens(readLen , tcpOctets);
            offset += tcpOctets;
            packetLen -= tcpOctets;
            capturedBytes -= tcpOctets;
            //printf("tcpOctets: %d, packetLen: %d, padding: %d\n", tcpOctets, packetLen, padding);
        } else if (proto == 0) {

            //skip udp packet
            readLen = read(m_snoopFilefd, ipBuffer, UDP_PKT_LEN);
            assertLens(readLen , UDP_PKT_LEN);
            offset += UDP_PKT_LEN;
            packetLen -= UDP_PKT_LEN;
            capturedBytes -= UDP_PKT_LEN;
        }

        if (packetLen > 0) {
            readLen = read(m_snoopFilefd, packetBuffer, packetLen);
            assertLens (readLen , packetLen);
            //Logic to send message should go here.
            offset += readLen;
            capturedBytes -= packetLen;
            packetLen -= readLen;
            if (capturedBytes > 0) {
                capturedBytes -= lseek(m_snoopFilefd, capturedBytes, SEEK_CUR);
            }
        } else if (packetLen == 0) {
            offset = lseek(m_snoopFilefd, capturedBytes, SEEK_CUR);
            readLen = packetLen;
        } else {
            if (capturedBytes > 0) {
                capturedBytes -= lseek(m_snoopFilefd, capturedBytes, SEEK_CUR);
            }
        }
        if (padding > 0)
            offset = lseek(m_snoopFilefd, padding, SEEK_CUR);
        ++m_frameCnt;
        return readLen;
    }
    if (offset >= m_snoopFileSize) {
        throw FileEndException(m_snoopFileName);
    }
    return 0;
}
