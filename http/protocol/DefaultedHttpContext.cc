#include "Value.h"
#include "HttpContext.h"
#ifndef DEFAULTEDHTTPCONTEXT_H
#include "DefaultedHttpContext.h"
#endif
DefaultedHttpContext::DefaultedHttpContext(HttpContext *l, HttpContext *d) {
    if (l == NULL) throw IllegalArgumentException("HTTP context may not be null");
    local = l;
    defaults = d;
}
ValueBase *DefaultedHttpContext::getAttribute(std::string id) {
    ValueBase *obj = local->getAttribute(id);
    if (obj == NULL) return defaults->getAttribute(id);
    return obj;
}
ValueBase *DefaultedHttpContext::removeAttribute(std::string id) {
    return local->removeAttribute(id);
}
HttpContext *DefaultedHttpContext::getDefaults() { return defaults; }
void DefaultedHttpContext::setAttribute(std::string id, ValueBase *obj) {
    local->setAttribute(id, obj);
}
