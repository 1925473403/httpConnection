#include "HttpException.h"
#ifndef URIPATTERNMATCHER_H
#include "UriPatternMatcher.h"
#endif
void UriPatternMatcher::registerUri(std::string pattern, ValueBase *handler) {
    if (pattern.length() == 0) throw IllegalArgumentException("URI request pattern may not be null");
    if (handler == NULL) throw IllegalArgumentException("HTTP request handelr may not be null");
    handlerMap.insert(std::make_pair(pattern, handler));
}
void UriPatternMatcher::unregister(std::string pattern) {
    if (pattern.length() == 0) throw IllegalArgumentException("URI request pattern may not be null");
    unordered_map<std::string, ValueBase *>::iterator it = handlerMap.find(pattern);
    if (it != handlerMap.end()) {
        ValueBase *v = it->second;
        delete v;
        handlerMap.erase(it);
    }
}
void UriPatternMatcher::setHandlers(unordered_map<std::string, ValueBase *> &map) {
    if (map.size() == 0) throw IllegalArgumentException("Map of handlers may not be null");
    for (unordered_map<std::string, ValueBase *>::iterator it = handlerMap.begin(); it != handlerMap.end(); it++) {
        ValueBase *v = it->second;
        delete v;
    }
    handlerMap.erase(handlerMap.begin(), handlerMap.end());
    for (unordered_map<std::string, ValueBase *>::iterator it = map.begin(); it != map.end(); it++)
        handlerMap.insert(std::make_pair(it->first, it->second));
}
ValueBase* UriPatternMatcher::lookup(std::string requestURI) {
    if (requestURI.length() == 0) throw IllegalArgumentException("URI request pattern may not be null");
    int index = requestURI.find("?");
    if (index != std::string::npos) {
        requestURI = requestURI.substring(0, index);
    }
    ValueBase *handler;
    unordered_map<std::string, ValueBase *>::iterator it = handlerMap.find(requestURI);
    if (it == handlerMap.end()) {
        std::string bestMatch = "";
        for (it = handlerMap.begin(); it != handlerMap.end(); it++) {
            std::string pattern = it->first;
            if (matchUriRequestPattern(pattern, requestURI)) {
                if (bestMatch.length() == 0 || (bestMatch.length() < pattern.length()) || (bestMatch.length() == pattern.length() && pattern[pattern.length() - 1] == '*')) {
                    unordered_map<std::string, ValueBase *>::iterator iter = handlerMap.find(pattern);
                    if (iter != handlerMap.end()) {
                        handler = iter->second;
                        bestMatch = pattern;
                    }
                }
            }
        }
    } else handler = it->second;
    return handler;
}

bool UriPatternMatcher::matchUriRequestPattern(std::string pattern, std::string requestUri) {
    if (pattern == "*") return true;
    else {
        return (pattern[pattern.length() - 1] == '*' && starts_with(requestUri, pattern.substr(0, pattern.length() - 1))) ||
        (pattern[0] == '*' && ends_with(requestUri, pattern.substr(1, pattern.length())));
    }
}

bool UriPatternMatcher::starts_with(std::string requestUri, std::string pattern) {
    for (int i = 0; i < std::min<int>(requestUri.length(), pattern.length()); i++) {
        if (requestUri[i] != pattern[i]) return false;
    }
    return true;
}

bool UriPatternMatcher::ends_with(std::string requestUri, std::string pattern) {
    int k = pattern.length() - 1;
    int j = requestUri.length() - 1;
    for (int i = std::min<int>(requestUri.length(), pattern.length()); i >= 0; i--) {
        if (requestUri[j] != pattern[k]) return false;
        j--; k--;
    }
    return true;
}
