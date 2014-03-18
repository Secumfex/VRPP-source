#ifndef RENDERQUEUEREQUESTFLAG_H
#define RENDERQUEUEREQUESTFLAG_H

#include "RenderQueue.h"

/*! @brief Proxyclass for forward including
 *
 *
 */
class GrapicsComponent;

/*! @brief Parent flag-class
 *
 * Other flags will be derived from this class
 */
class RenderQueueRequestFlag{
private:
public:
	list<GraphicsComponent*> extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >);
};

#endif