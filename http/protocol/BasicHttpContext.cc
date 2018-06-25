#include "Value.h"
#include "HttpContext.h"
#ifndef BASICHTTPCONTEXT_H
#include "BasicHttpContext.h"
#endif
BasicHttpContext::BasicHttpContext() : parentContext(NULL) { }
BasicHttpContext::BasicHttpContext(HttpContext *obj) : parentContext(obj) { }
ValueBase* BasicHttpContext::getAttribute(std::string id) {
    if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
    ValueBase *obj = NULL;
    std::unordered_map<std::string, ValueBase*>::iterator it = map.end();
    if (map.size() != 0) it = map.find(id);
    if (it == map.end() && parentContext != NULL)
        obj = parentContext->getAttribute(id);
    return obj;
}
void BasicHttpContext::setAttribute(std::string id, ValueBase *obj) {
    if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
    map.insert(std::make_pair(id, obj));
}
ValueBase *BasicHttpContext::removeAttribute(std::string id) {
    ValueBase *obj = NULL;
    if (id.length() == 0) throw IllegalArgumentException("Id may not be null");
    std::unordered_map<std::string, ValueBase*>::iterator it = map.find(id);
    if (it != map.end()) {
        obj = it->second;
        map.erase(it);
    }
    return obj;
}
