#include <iostream>
#include <string>
#include <unordered_map>
#include "HttpContext.h"
#include "HttpException.h"
class BasicHttpContext : public HttpContext {
    private:
        HttpContext *parentContext;
        std::unordered_map<std::string, HttpContext*> map;
    public:
        BasicHttpContext() : parentContext(NULL) { }
        BasicHttpContext(HttpContext *obj) : parentContext(obj) { }
        ~BasicHttpContext() { }
        HttpContext* getAttribute(std::string &id) {
            if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
            HttpContext *obj = NULL;
            std::unordered_map<std::string, HttpContext*>::iterator it = map.end();
            if (map.size() != 0) it = map.find(id);
            if (it == map.end() && parentContext != NULL)
                obj = parentContext->getAttribute(id);
            return obj;
        }
        void setAttribute(std::string &id, HttpContext *obj) {
            if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
            map.insert(std::make_pair(id, obj));
        }
        HttpContext *removeAttribute(std::string &id) {
            HttpContext *obj = NULL;
            if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
            std::unordered_map<std::string, HttpContext*>::iterator it = map.find(id);
            if (it != map.end()) {
                obj = it->second;
                map.erase(it);
            }
            return obj;
        }
};
