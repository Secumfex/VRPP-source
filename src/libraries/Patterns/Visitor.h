#ifndef VISITOR_H
#define VISITOR_H

//using namespace std;

/*! @brief Proxyclass for forward including
 *
 *
 */
class RenderQueue;

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