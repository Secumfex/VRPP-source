#include "RenderQueueRequestFlag.h"
#include "RenderQueue.h"

using namespace std;


/*! @brief specific flag class
 *
 * one of the non-abstract flag-classes for the RQ
 */
class FlagUsesShader : public RenderQueueRequestFlag 
{ 
	list<GraphicsComponent*> extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
		return rq->extrudeGCsForRequestFlag(this, temp);
	}
}; 