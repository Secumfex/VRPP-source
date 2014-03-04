#include "RenderQueue.h"
#include <iostream>

using namespace std;

RenderQueue::RenderQueue() {
	resetQueue();
}

RenderQueue::~RenderQueue() {

}

/** \brief returns a pointer to this RenderQueue
 */
RenderQueue* RenderQueue::getRenderQueue() {
	return this;
}

void RenderQueue::addShader(Shader* sh) {
	cout << "Adding Shader to shaderList." << endl;
	shaderList.push_back(sh);
}

/** \brief adds a VO to the member list of VOs, also maps GC->VO and vice versa
 */
void RenderQueue::addVirtualObject(VirtualObject* vo) {
	cout << "Adding VO." << endl; // <-- REMOVE IN FINAL
	voList.push_back(vo);

	vector<GraphicsComponent*> gcVector;

	gcVector = vo->getGraphicsComponent();

	for (unsigned int i = 0; i < gcVector.size(); i++) {
		cout << "Sort: GC->VO, VO->GC" << endl; // <-- REMOVE IN FINAL

		vo2gcMap[vo].push_back(gcVector[i]); /// VO --> GC
		gc2voMap[gcVector[i]] = vo;
		gcList.push_back(gcVector[i]);
	}
}

/** \brief removes a single VO from the member list of VOs
 */
void RenderQueue::removeVirtualObject(VirtualObject* vo) {
	cout << "Removing VO." << endl; // <-- REMOVE IN FINAL
	voList.remove(vo);
}

/** \brief extract the first VO from the list and remove it after extraction before returning the pointer
 * @return  returns the VO the iterator was pointing at
 */
VirtualObject* RenderQueue::getNextObject() {
	cout << "Getting VO and iterating queue-iterator." << endl; // <-- REMOVE IN FINAL

	VirtualObject* vo = *currentFirstElement;
	currentFirstElement++;
	return vo;
}

/** \brief test if VO list is empty
 */
bool RenderQueue::hasNext() {
	if (currentFirstElement == voList.end()) {
		cout << "no more queued Virtual Objects remaining." << endl; // <-- REMOVE IN FINAL
		return false;
	} else {
		cout << "queued Virtual Objects remaining." << endl; // <-- REMOVE IN FINAL
		return true;
	}
}

/** \brief setting the iterator for the list of VOs to the start therefore resetting the RQ
 */
void RenderQueue::resetQueue() {
	currentFirstElement = voList.begin();
}

/** \brief getter for GCs sorted by flags
 */
map<string, vector<GraphicsComponent*> > RenderQueue::getGcFlagStorage() {
	return gcFlagStorage;
}

/** \brief getter for GCs sorted by shaders
 */
map<string, vector<GraphicsComponent*> > RenderQueue::getGcShaderStorage() {
	return gcShaderStorage;
}

/** \brief getter for GCs sorted by textures
 */
map<string, vector<GraphicsComponent*> > RenderQueue::getGcTexStorage() {
	return gcTexStorage;
}

/** \brief getter for GC->VO map
 */
map<GraphicsComponent*, VirtualObject*> RenderQueue::getGc2VoMap() {
	return gc2voMap;
}

/** \brief getter for VO->GC map
 */
map<VirtualObject*, vector<GraphicsComponent*> > RenderQueue::getVo2GcMap() {
	return vo2gcMap;
}

list<VirtualObject*> RenderQueue::getVirtualObjectList() {
	return voList;
}


	//Beim rendern, wenn ein Feld der Map leer ist, dann muss der GBuffer genutzt werden
	//Am besten noch eine Liste erstellen wo die shadowCast GCs reinkommen (müssen in mehr als einer Liste sein)
void RenderQueue::sortByAttributes() {
	resetQueue();
	cout<<"Entering sortByAttributes:"<<endl;

	GraphicsComponent* gc;
	Shader* sh;

	cout<<"- Creating iterators."<<endl;

	list<Shader*>::iterator sh_it = shaderList.begin(); //name totally unintended.
	list<GraphicsComponent*>::iterator gc_it = gcList.begin();
	list<Shader*>::iterator shAlt_it = shaderListAlternate.begin();
	list<Shader*>::iterator shCop_it = shaderListCopy.begin();

	cout<<"- Creating boolean isElement."<<endl;

	bool isElement = false;

	cout<<"- Starting key-fill-loop:"<<endl;

	for (sh_it = shaderList.begin(); sh_it != shaderList.end(); sh_it++) {
		cout << "- Filling the shaderList with keys" << endl;
		//shader2gcStorage[*sh_it];
		gc2shaderStorage[*gc_it];
	}

	cout<<"- main loop:"<<endl;

	for (gc_it = gcList.begin(); gc_it != gcList.end(); gc_it++) {
		cout << "- Is in sortByAttributes loop" << endl;

			//create copy of shaderList
		for (sh_it = shaderList.begin(); sh_it != shaderList.end(); sh_it++) {
			cout<<"- Inner loop: copy shaderList"<<endl;
			shaderListCopy.push_back(*sh_it);
		}
			//ShaderList 3 more uniforms then shader takes
		shaderListAlternate.clear();

		for (sh_it = shaderList.begin(); sh_it != shaderList.end(); sh_it++) {
			cout<<"- In inner loop: if-stuff"<<endl;
			//if s1.hasUniform("normalTexture") XOR gc1.hasNormalMap() --> doStuff :
			if (!((*sh_it)->hasUniform("normalTexture"))
					&& (*gc_it)->getMaterial()->hasNormalTexture()) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}

			if (!((*sh_it)->hasUniform("diffuseTexture")
					&& (*gc_it)->getMaterial()->hasDiffuseTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("ambient")
					&& (*gc_it)->getMaterial()->hasAmbientTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("emissiveMap")
					&& (*gc_it)->getMaterial()->hasEmissiveTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("heightMap")
					&& (*gc_it)->getMaterial()->hasHeightTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("opacityMap")
					&& (*gc_it)->getMaterial()->hasOpacityTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("specularMap")
					&& (*gc_it)->getMaterial()->hasSpecularTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("reflectionMap")
					&& (*gc_it)->getMaterial()->hasReflectionTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("shininessMap")
					&& (*gc_it)->getMaterial()->hasShininessTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("displacementMap")
					&& (*gc_it)->getMaterial()->hasDisplacementTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}
			if (!((*sh_it)->hasUniform("lightMap")
					&& (*gc_it)->getMaterial()->hasLightTexture())) {
				shaderListCopy.remove(*sh_it);
				shaderListAlternate.remove(*sh_it);
				isElement = false;
				continue;
			}

			cout<<"- More if stuff"<<endl;

			if (((*sh_it)->hasUniform("normalTexture"))
					&& !(*gc_it)->getMaterial()->hasNormalTexture()) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (((*sh_it)->hasUniform("diffuseMap")
					&& !((*gc_it)->getMaterial()->hasDiffuseTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (((*sh_it)->hasUniform("ambientMap")
					&& !((*gc_it)->getMaterial()->hasAmbientTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (((*sh_it)->hasUniform("emissiveMap")
					&& !((*gc_it)->getMaterial()->hasEmissiveTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (((*sh_it)->hasUniform("heightMap")
					&& !((*gc_it)->getMaterial()->hasHeightTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("opacityMap")
					&& !((*gc_it)->getMaterial()->hasOpacityTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("specularMap")
					&& !((*gc_it)->getMaterial()->hasSpecularTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("reflectionMap")
					&& !((*gc_it)->getMaterial()->hasReflectionTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("shininessMap")
					&& !((*gc_it)->getMaterial()->hasShininessTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("displacementMap")
					&& !((*gc_it)->getMaterial()->hasDisplacementTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}
			if (!((*sh_it)->hasUniform("lightMap")
					&& !((*gc_it)->getMaterial()->hasLightTexture()))) {
				shaderListAlternate.push_back(*sh_it);
				isElement = true;
			}

//			for(shAlt_it = shaderListAlternate.begin(); shAlt_it != shaderListAlternate.end(); shAlt_it++){
//				if(*shAlt_it == *sh_it)
//					isElement = true;
//			}
			cout<<"- Finished ifs, L2 or L3?"<<endl;

			if(isElement == false)
				shaderListCopy.push_back(*sh_it);
			isElement = false;
		}
		cout<<"- L2@"<<*gc_it<<endl;
		for (shCop_it = shaderListCopy.begin(); shCop_it != shaderListCopy.end(); shCop_it++) {
			gc2shaderStorage[*gc_it].push_back(*shCop_it);
			cout<<*shCop_it<<endl;
		}
		cout<<"- L3@"<<*gc_it<<endl;
		for (shAlt_it = shaderListAlternate.begin(); shAlt_it != shaderListAlternate.end(); shAlt_it++) {
			gc2shaderStorage[*gc_it].push_back(*shAlt_it);
			cout<<*shAlt_it<<endl;
		}
		cout<<"- done."<<endl;

	}
}

void RenderQueue::sortByShaders() {
	resetQueue();
	string shader = "DEFERRED_SHADING";
	VirtualObject* vo;
	vector<GraphicsComponent*> gcVector;

	cout << "Entering sortByShaders" << endl; // <-- REMOVE IN FINAL

	while (hasNext()) {
		vo = getNextObject();
		gcVector = vo->getGraphicsComponent();
		for (unsigned int i = 0; i < gcVector.size(); i++) {
			cout << "Adding GC to the map." << endl; // <-- REMOVE IN FINAL

			gcShaderStorage[shader].push_back(gcVector[i]); /// shader --> GC
			vo2gcMap[vo].push_back(gcVector[i]); /// VO --> GC

			gc2voMap[gcVector[i]] = vo;
		}
	}
}

void RenderQueue::sortByTextures() {
	resetQueue();
	string texID = "tex_stone";
	VirtualObject* vo;
	vector<GraphicsComponent*> gcTexVector;

	cout << "Entering sortByTextures" << endl; // <-- REMOVE IN FINAL

	while (hasNext()) {
		vo = getNextObject();
		gcTexVector = vo->getGraphicsComponent();
		for (unsigned int i = 0; i < gcTexVector.size(); i++) {
			cout << "Adding GC to the TextureMap." << endl; // <-- REMOVE IN FINAL

			gcTexStorage[texID].push_back(gcTexVector[i]); /// texture --> GC
			gcTex2voMap[vo].push_back(gcTexVector[i]); /// VO --> GC

			vo2gcTexMap[gcTexVector[i]] = vo;
		}
	}
}

void RenderQueue::sortByFlags() {
	resetQueue();
	string sString = "SHADOW";
	string eString = "EMISSION";
	string tString = "TRANSPARENCY";

	VirtualObject* vo;

	vector<GraphicsComponent*> gcFlagVector;

	cout << "entering sortByFlags" << endl; // <-- REMOVE IN FINAL

	while (hasNext()) {
		vo = getNextObject();
		gcFlagVector = vo->getGraphicsComponent();
		for (unsigned int i = 0; i < gcFlagVector.size(); i++) {
			cout << "Adding GC to the FlagMap." << endl;

			if (gcFlagVector[i]->hasEmission()) {
				gcFlagStorage[eString].push_back(gcFlagVector[i]);
			}

			if (gcFlagVector[i]->hasShadow()) {
				gcFlagStorage[sString].push_back(gcFlagVector[i]);
			}

			if (gcFlagVector[i]->hasTransparency()) {
				gcFlagStorage[tString].push_back(gcFlagVector[i]);
			}
		}
	}
}

