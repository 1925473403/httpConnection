#include "HttpException.h"
#ifndef VERSIONINFO_H
#include "VersionInfo.h"
#endif
std::string VersionInfo::UNAVAILABLE("UNAVAILABLE");
std::string VersionInfo::VERSION_PROPERTY_FILE("version.properties");
std::string VersionInfo::PROPERTY_MODULE("info.module");
std::string VersionInfo::PROPERTY_RELEASE("info.release");
std::string VersionInfo::PROPERTY_TIMESTAMP("info.timestamp");
VersionInfo::VersionInfo(std::string &pckg, std::string &module, std::string &release, std::string &time, std::string &clsldr) {
    if (pckg.length() == 0) throw IllegalArgumentException("Package identifier must not be null.");
    infoPackage     = pckg;
    infoModule      = ((module.length()  != 0)? module  : UNAVAILABLE);
    infoRelease     = ((release.length() != 0) ? release : UNAVAILABLE);
    infoTimestamp   = ((time.length()    != 0) ? time    : UNAVAILABLE);
    infoClassloader = ((clsldr.length()  != 0) ? clsldr  : UNAVAILABLE);
}

VersionInfo::VersionInfo(const VersionInfo &versionInfo) {
    infoPackage = versionInfo.infoPackage;
    infoModule = versionInfo.infoModule;
    infoRelease = versionInfo.infoRelease;
    infoTimestamp = versionInfo.infoTimestamp;
    infoClassloader = versionInfo.infoClassloader;
}

VersionInfo& VersionInfo::operator=(const VersionInfo &versionInfo) {
    if (this != &versionInfo) {
        infoPackage = versionInfo.infoPackage;
        infoModule = versionInfo.infoModule;
        infoRelease = versionInfo.infoRelease;
        infoTimestamp = versionInfo.infoTimestamp;
        infoClassloader = versionInfo.infoClassloader;
    }
    return *this;
}

std::string VersionInfo::getPackage() const {
    return infoPackage;
}

std::string VersionInfo::getModule() const {
    return infoModule;
}

std::string VersionInfo::getRelease() const {
    return infoRelease;
}

std::string VersionInfo::getTimestamp() const {
    return infoTimestamp;
}

std::string VersionInfo::getClassloader() const {
    return infoClassloader;
}

std::string VersionInfo::toString() {
    stringstream ss ;
    ss << "VersionInfo(" ;
    ss << infoPackage ;
    ss << ":" ;
    ss << infoModule;
    if (infoRelease != UNAVAILABLE) { ss << ":" ; ss<< infoRelease; }
    if (infoTimestamp != UNAVAILABLE) { ss << ":" ; ss<< infoTimestamp; }
    ss << ")";
    if (infoClassloader != UNAVAILABLE) { ss << "@"; ss << infoClassloader; }
    return ss.str();
}

vector<VersionInfo> VersionInfo::loadVersionInfo(vector<std::string> pckgs) {
    if (pckgs.length() == 0) throw IllegalArgumentException ("Package identifier list must not be null.");
    vector<VersionInfo> vil;
    for (int i=0; i<pckgs.length; i++) {
        VersionInfo vi = loadVersionInfo(pckgs[i]);
        vil.push_back(vi);
    }
    return vil;
}

VersionInfo VersionInfo::loadVersionInfo(std::string pckg) {
    if (pckg.length() == 0) throw IllegalArgumentException("Package identifier must not be null.");
    Properties vip;
    try {
        std::replace_if<char>(pckg.begin(), pckg.end(), '.', '/');
        std::string filename = pckg + "/" + VERSION_PROPERTY_FILE;
        ifstream ifs(filename, std::ios_base::in);
        if (ifs.is_open()) {
            try {
                Properties props(ifs);
                vip = props;
            } catch(...) {
            }
            ifs.close();
        }
    } catch (const IOException &ex) {
    }
    VersionInfo result = fromMap(pckg, vip);
    return result;
}

VersionInfo VersionInfo::fromMap(std::string pckg, Properties &info) {
    if (pckg.length() == 0) throw IllegalArgumentException("Package identifier must not be null.");
    std::string module ="", release = "", timestamp = "";
    module = info.get(PROPERTY_MODULE);
    release = info.get(PROPERTY_RELEASE);
    timestamp info.get(PROPERTY_TIMESTAMP);
    return VersionInfo(pckg, module, release, timestamp, "");
}
