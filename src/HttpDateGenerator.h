#ifndef HTTPDATEGENERATOR_H
#define HTTPDATEGENERATOR_H
class HttpDateGenerator {
    long dateAsLong;
    std::string dateAsText;
    public:
    HttpDateGenerator();
    std::string getCurrentDate();
};
#endif
