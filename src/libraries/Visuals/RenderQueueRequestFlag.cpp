#include "RenderQueueRequestFlag.h"
#include "RenderQueue.h"
#include "Shader.h"
#include "GraphicsComponent.h"
#include "VirtualObject.h"
#include "Resource.h"

using namespace std;

RenderQueueRequestFlag::RenderQueueRequestFlag()
{
	mInvertCondition = false;
}

void RenderQueueRequestFlag::setInvertCondition(bool to)
{
	mInvertCondition = to;
}

bool RenderQueueRequestFlag::getInvertCondition()
{
	return mInvertCondition;
}

FlagShadowCaster::FlagShadowCaster(bool invertedCondition){
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& FlagShadowCaster::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagUsesShader::FlagUsesShader(Shader* shader, bool invertedCondition){
	mShader = shader;
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& FlagUsesShader::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagUsesMesh::FlagUsesMesh(Mesh* mesh, bool invertedCondition){
	setInvertCondition(invertedCondition);
	mMesh = mesh;
}

list<GraphicsComponent*>& FlagUsesMesh::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagPartOfVirtualObject::FlagPartOfVirtualObject(VirtualObject* vo, bool invertedCondition){
	setInvertCondition(invertedCondition);
	mVO = vo;
}

VirtualObject* FlagPartOfVirtualObject::getVirtualObject()
{
	return mVO;
}

list<GraphicsComponent*>& FlagPartOfVirtualObject::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagInViewFrustum::FlagInViewFrustum(bool invertedCondition){
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& FlagInViewFrustum::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagTransparency::FlagTransparency(bool invertedCondition){
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& FlagTransparency::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagScreenFillingPolygon::FlagScreenFillingPolygon(bool invertedCondition){
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& FlagScreenFillingPolygon::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

CurrentRenderQueueFlag::CurrentRenderQueueFlag(bool invertedCondition){
	setInvertCondition(invertedCondition);
}

list<GraphicsComponent*>& CurrentRenderQueueFlag::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* >& temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}
