#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>
#include <map>

#include "VirtualObject.h"

using namespace std;

/*! @brief RenderQueue is a queue that contains all objects to be drawn in the scene.
 *
 *	@todo please write doxygen comments only in header file.
 *	@todo please describe the parameters only if there are any parameters to the method you are commenting ;-)
 */
class RenderQueue {
public: 
	RenderQueue(); //create and reset RQ
	~RenderQueue();
	RenderQueue* getRenderQueue(); 
	void addVirtualObject(VirtualObject* vo); //add VO to VO list
	void removeVirtualObject(VirtualObject* vo); //remove VO from list
	VirtualObject* getNextObject(); //iterate list
	bool hasNext(); //is voList empty?
	void resetQueue();	//resetting iterator to list begin
	list<VirtualObject* > getVirtualObjectList(); //!< return list of all virtual objects in this queue
	map<string, vector<GraphicsComponent* > > getGcFlagStorage();
	map<string, vector<GraphicsComponent* > > getGcShaderStorage();
	map<string, vector<GraphicsComponent* > > getGcTexStorage();
	map<VirtualObject*, vector<GraphicsComponent* > > getVo2GcMap();
	map<GraphicsComponent*, VirtualObject* > getGc2VoMap();
	void sortByShaders(); //extracts GCs from all VOs in VO list and sorts them into the gcStorage map
	void sortByTextures(); //extracts GCs from all VOs in VO list and sorts them into the gcTexStorage map
	void sortByFlags(); //extracts GCs from all VOs and sorts them into gcFlagStorage by checking for transparency, shadow, etc
private:
	list<VirtualObject* >::iterator currentFirstElement; ///< VO pointer used with voList
//	vector<GraphicsComponent>::iterator gcIterator; ///< iterator for gc-vectors
	list<VirtualObject*> voList; ///< list of VOs
	map<string, vector<GraphicsComponent* > > gcShaderStorage; ///< GC map sorted by shaders
	map<string, vector<GraphicsComponent* > > gcTexStorage; ///< GC map sorted by Textures
	map<VirtualObject*, vector<GraphicsComponent* > > vo2gcMap; ///< each GC is assigned to some VO
	map<VirtualObject*, vector<GraphicsComponent* > > gcTex2voMap; ///< each GC is assigned to some VO
	map<GraphicsComponent*, VirtualObject*> gc2voMap; ///< each VO is assigned to some GC
	map<GraphicsComponent*, VirtualObject*> vo2gcTexMap; ///< each VO is assigned to some GC
	map<string, vector<GraphicsComponent* > > gcFlagStorage; ///< GC map sorted by flags
};

#endif /* RENDERQUEUE_H */
