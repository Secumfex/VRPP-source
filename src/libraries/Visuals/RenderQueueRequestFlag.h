#ifndef RENDERQUEUEREQUESTFLAG_H
#define RENDERQUEUEREQUESTFLAG_H

//#include "RenderQueue.h"
#include "Patterns/Visitor.h"
#include <list>

using namespace std;

/*! @brief Proxyclass for forward including
 *
 *
 */
class RenderQueue;

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
	/*! @brief Send flag-objects to the RenderQueue
	 *
	 * Abstract method, sends Flag objects to overloaded metods ín the RenderQueue
	 */
	virtual list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* temp>);
};

#endif