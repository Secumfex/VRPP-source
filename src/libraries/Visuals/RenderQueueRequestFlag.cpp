#include "RenderQueueRequestFlag.h"
#include "RenderQueue.h"
#include "Shader.h"
#include "GraphicsComponent.h"
#include "Resource.h"

using namespace std;

FlagShadowCaster::FlagShadowCaster(){

}

list<GraphicsComponent*> FlagShadowCaster::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagUsesShader::FlagUsesShader(Shader* shader){
	mShader = shader;
}

list<GraphicsComponent*> FlagUsesShader::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagUsesObjectModel::FlagUsesObjectModel(Mesh* mesh){
	mMesh = mesh;
}

list<GraphicsComponent*> FlagUsesObjectModel::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagInViewFrustum::FlagInViewFrustum(){
	
}

list<GraphicsComponent*> FlagInViewFrustum::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagTransparency::FlagTransparency(){
	
}

list<GraphicsComponent*> FlagTransparency::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}

FlagScreenFillingPolygon::FlagScreenFillingPolygon(){
	
}

list<GraphicsComponent*> FlagScreenFillingPolygon::extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp){
	return rq->extrudeGCsForRequestFlag(this, temp);
}