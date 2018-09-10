#ifndef ROUTEDREQUEST_H
#define ROUTEDREQUEST_H
class RoutedRequest {
    protected:
        RequestWrapper *request;
        HttpRoute *route;
    public:
        RoutedRequest(RequestWrapper *req, HttpRoute *r):request(req), route(r) { }
        RequestWrapper* getRequest() const { return request; }
        HttpRoute* getRoute() const { return route }
};
#endif
