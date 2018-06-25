#include "HttpException.h"
#include <time.h>
#include <sys/time.h>
#ifndef HTTPDATEGENERATOR_H
#include "HttpDateGenerator.h"
#endif
const char wday_name[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char mon_name[][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
HttpDateGenerator::HttpDateGenerator() {
    struct timeval t;
    gettimeofday(&t, NULL);
    dateAsLong = t.tv_sec;
    time_t rawtime;
    struct tm *ptm;
    time ( &rawtime );
    ptm = gmtime ( &rawtime );
    char result[32] = { 0 };
    snprintf(result, 31, "%s, %02d %s %d %d:%d:%d GMT", wday_name[ptm->tm_mon], ptm->tm_mday, mon_name[ptm->tm_mon], 1900 + ptm->tm_year, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    dateAsText.assign(result);
}
std::string HttpDateGenerator::getCurrentDate() {
    time_t rawtime;
    struct tm *ptm;
    struct timeval t;
    gettimeofday(&t, NULL);
    time ( &rawtime );
    ptm = gmtime ( &rawtime );
    char result[32] = { 0 };
    snprintf(result, 31, "%s, %02d %s %d %d:%d:%d GMT", wday_name[ptm->tm_mon], ptm->tm_mday, mon_name[ptm->tm_mon], 1900 + ptm->tm_year, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    if (t.tv_sec - dateAsLong > 1) {
        dateAsLong = t.tv_sec;
        dateAsText.assign(result);
    }
    return dateAsText;
}
