#ifndef VISITOR_H
#define VISITOR_H

#include "Visuals/RenderQueue.h"

//using namespace std;

/*! @brief Visitor is the super  class of more specific visitor.
 *
 *	
 */
class Visitor{
private:
public:
	Visitor();
	void visitRenderQueue(RenderQueue* rq);
};

#endif