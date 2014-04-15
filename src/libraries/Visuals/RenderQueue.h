#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <list>
#include <map>

#include "VirtualObject.h"
#include "Shader.h"
#include "Patterns/Visitor.h"
#include "RenderQueueRequestFlag.h"
//#include "FlagInViewFrustum.h"
//#include "FlagShadowCaster.h"
//#include "FlagScreenFillingPolygon.h"
//#include "FlagTransparent.h"
//#include "FlagUsesObjectModel.h"
//#include "FlagUsesShader.h"

using namespace std;

/*! @brief RenderQueue is a queue that contains all objects to be drawn in the scene.
 *
 *	@todo please write doxygen comments only in header file.
 */
class RenderQueue {
public: 
	/** \brief constructor
	 *
	 * create and reset RQ
	 */
	RenderQueue();

	/** \brief destructor
	 *
	 */
	~RenderQueue();

	/** \brief getter
	 *
	 * @return RenderQueue
	 */
	RenderQueue* getRenderQueue(); 

	/** \brief add Shader to ShaderList
	 *
	 * @param sh
	 */
	void addShader(Shader* sh);

	/** \brief add Shader to ShaderList
	 *
	 * @param sh
	 */
	void addCompositingShader(Shader* sh);

	/** \brief add VO to VO list
	 *
	 * @param vo
	 */
	void addVirtualObject(VirtualObject* vo);

	/** \brief remove VO from list
	 *
	 * @param vo
	 */
	void removeVirtualObject(VirtualObject* vo);

	/** \brief getter
	 *
	 * iterate list
	 * @return current first element (virtual object)
	 */
	VirtualObject* getNextObject();

	/** \brief is voList empty?
	 *
	 * @return true or false
	 */
	bool hasNext();

	/** \brief resetting iterator to list begin
	 *
	 */
	void resetQueue();

	/** \brief getter
	 *
	 * return list of all virtual objects in this queue
	 * @return voList
	 */
	list<VirtualObject* > getVirtualObjectList();

	/** \brief getter
	 *
	 * return list of all graphicscomponents in this queue
	 *
	 */
	 list<GraphicsComponent* > getGraphicsComponentList();

	/** \brief getter
	 *
	 * @return gcFlagStorage
	 */
	map<string, vector<GraphicsComponent* > > getGcFlagStorage();

	/** \brief getter
	 *
	 * @return gcShaderStorage
	 */
	map<string, vector<GraphicsComponent* > > getGcShaderStorage();

	/** \brief getter
	 *
	 * @return gcTexStorage
	 */
	map<string, vector<GraphicsComponent* > > getGcTexStorage();

	/** \brief getter
	 *
	 * @return vo2gcMap
	 */
	map<VirtualObject*, vector<GraphicsComponent* > > getVo2GcMap();

	/** \brief getter
	 *
	 * @return gc2voMap
	 */
	map<GraphicsComponent*, VirtualObject* > getGc2VoMap();

	/** \brief sort graphic components by attributes
	 *
	 */
	void sortByAttributes();

	/** \brief sort graphic components by shaders
	 *
	 * extracts GCs from all VOs in VO list and sorts them into the gcStorage map
	 */
	void sortByShaders();

	/** \brief sort graphic components by textures
	 *
	 * extracts GCs from all VOs in VO list and sorts them into the gcTexStorage map
	 */
	void sortByTextures();

	/** \brief sort graphic components by flags
	 *
	 * extracts GCs from all VOs and sorts them into gcFlagStorage by checking for transparency, shadow, etc
	 */
	void sortByFlags();

	/** \brief accept visitor method
	 *
	 * accepts a visitor to the RenderQueue object
	 */
	void accept(Visitor* v);

	/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagShadowCaster* flag, list<GraphicsComponent* > temp);

	/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagUsesShader* flag, list<GraphicsComponent* > temp);

	/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagTransparency* flag, list<GraphicsComponent* > temp);

	/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagUsesObjectModel* flag, list<GraphicsComponent* > temp);

	/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagScreenFillingPolygon* flag, list<GraphicsComponent* > temp);

		/** \brief overloaded. returns GC-list depending on flag
	 *
	 * overloaded method for any possible flag object. will extract a GC list depending on that object
	 */
	list<GraphicsComponent* > extrudeGCsForRequestFlag(FlagInViewFrustum* flag, list<GraphicsComponent* > temp);	
private:
	list<VirtualObject* >::iterator currentFirstElement; 			/**< VO pointer used with voList */
//	vector<GraphicsComponent>::iterator gcIterator; 				/**< iterator for gc-vectors */
	list<VirtualObject*> voList; 									/**< list of VOs */
	map<string, vector<GraphicsComponent* > > gcShaderStorage; 		/**< GC map sorted by shaders */
	map<string, vector<GraphicsComponent* > > gcTexStorage; 		/**< GC map sorted by Textures */
	map<VirtualObject*, vector<GraphicsComponent* > > vo2gcMap; 	/**< each GC is assigned to some VO */
	map<VirtualObject*, vector<GraphicsComponent* > > gcTex2voMap; 	/**< each GC is assigned to some VO */
	map<GraphicsComponent*, VirtualObject*> gc2voMap; 				/**< each VO is assigned to some GC */
	map<GraphicsComponent*, VirtualObject*> vo2gcTexMap; 			/**< each VO is assigned to some GC*/
	map<string, vector<GraphicsComponent* > > gcFlagStorage; 		/**< GC map sorted by flags */
	map<Shader*, vector<GraphicsComponent* > > shader2gcStorage; 	/**< Shader pointers to gc pointers */
	map<GraphicsComponent*, vector<Shader*> > gc2shaderStorage;		/**< docu pls */

	list<Shader*> shaderList;			/**< all shaders of the RQ */
	list<Shader*> compositingList;		/**< all compositing shaders */
	list<Shader*> shaderListCopy;		/**< L2 of the sortByAttributes method */
	list<Shader*> shaderListAlternate;	/**< L3 of the sortByAttributes method */
	list<GraphicsComponent*> gcList;	/**< all GCs of the RQ */
};

#endif /* RENDERQUEUE_H */
