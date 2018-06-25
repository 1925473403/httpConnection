#include "HttpException.h"
#ifndef VERSIONINFO_H
#define VERSIONINFO_H
class VersionInfo {
    private:
    std::string infoPackage;
    std::string infoModule;
    std::string infoRelease;
    std::string infoTimestamp;
    std::string infoClassloader;
    public:
    static std::string UNAVAILABLE;
    static std::string VERSION_PROPERTY_FILE;
    static std::string PROPERTY_MODULE;
    static std::string PROPERTY_RELEASE;
    static std::string PROPERTY_TIMESTAMP;
    protected:
    VersionInfo(std::string &pckg, std::string &module, std::string &release, std::string &time, std::string &clsldr);
    public:
    VersionInfo(const VersionInfo &versionInfo);
    VersionInfo& operator=(const VersionInfo &versionInfo);
    std::string getPackage() const;
    std::string getModule() const;
    std::string getRelease() const;
    std::string getTimestamp() const;
    std::string getClassloader() const;
    std::string toString();
    static vector<VersionInfo> loadVersionInfo(vector<std::string> pckgs);
    static VersionInfo loadVersionInfo(std::string pckg);
    static VersionInfo fromMap(std::string pckg, unordered_map<std::string, std::string> &info);
};
#endif
