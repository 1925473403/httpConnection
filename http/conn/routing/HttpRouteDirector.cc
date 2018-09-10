#ifndef HTTPROUTEDIRECTOR_H
#include "HttpRouteDirector.h"
#endif
/** Indicates that the route can not be established at all. */
int HttpRouteDirector::UNREACHABLE = -1;

/** Indicates that the route is complete. */
int HttpRouteDirector::COMPLETE = 0;

/** Step: open connection to target. */
int HttpRouteDirector::CONNECT_TARGET = 1;

/** Step: open connection to proxy. */
int HttpRouteDirector::CONNECT_PROXY = 2;

/** Step: tunnel through proxy to target. */
int HttpRouteDirector::TUNNEL_TARGET = 3;

/** Step: tunnel through proxy to other proxy. */
int HttpRouteDirector::TUNNEL_PROXY = 4;

/** Step: layer protocol (over tunnel). */
int HttpRouteDirector::LAYER_PROTOCOL = 5;


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
