#include "HttpException.h"
#ifndef HTTPROUTEDIRECTOR_H
#define HTTPROUTEDIRECTOR_H
class HttpRouteDirector {
    public:
    /** Indicates that the route can not be established at all. */
    static int UNREACHABLE;

    /** Indicates that the route is complete. */
    static int COMPLETE;

    /** Step: open connection to target. */
    static int CONNECT_TARGET;

    /** Step: open connection to proxy. */
    static int CONNECT_PROXY;

    /** Step: tunnel through proxy to target. */
    static int TUNNEL_TARGET;

    /** Step: tunnel through proxy to other proxy. */
    static int TUNNEL_PROXY;

    /** Step: layer protocol (over tunnel). */
    static int LAYER_PROTOCOL;


    /**
     * Provides the next step.
     *
     * @param plan      the planned route
     * @param fact      the currently established route, or
     *                  <code>null</code> if nothing is established
     *
     * @return  one of the constants defined in this interface, indicating
     *          either the next step to perform, or success, or failure.
     *          0 is for success, a negative value for failure.
     */
    virtual int nextStep(RouteInfo plan, RouteInfo fact) = 0;
    virtual ~HttpRouteDirector() { }
};
#endif
