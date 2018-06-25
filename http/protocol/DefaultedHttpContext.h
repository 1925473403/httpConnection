#include <iostream>
#include <string>
#include <unordered_map>
#include "HttpContext.h"
#include "HttpException.h"
class DefaultedHttpContext : public HttpContext {
    private:
        HttpContext* local;
        HttpContext *defaults;
    public:
        DefaultedHttpContext(HttpContext *l, HttpContext *d) {
            if (l == NULL) throw IllegalArgumentException("HTTP context may not be null");
            local = l;
            defaults = d;
        }
        HttpContext *getAttribute(std::string &id) {
            HttpContext *obj = local->getAttribute(id);
            if (obj == NULL) return defaults->getAttribute(id);
            return obj;
        }
        HttpContext *removeAttribute(std::string &id) {
            return local->removeAttribute(id);
        }
        HttpContext *getDefaults() { return defaults; }
        void setAttribute(std::string &id, HttpContext *obj) {
            local->setAttribute(id, obj);
        }
}; 
