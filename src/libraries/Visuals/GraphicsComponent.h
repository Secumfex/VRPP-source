#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <vector>
#include "Visuals/Resource.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <btBulletCollisionCommon.h>
#include "Physics/PhysicWorld.h"
#include "Animation/AnimationLoop.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

/*! @brief GraphicsComponent .
 *
 *	@todo detailed description please
 */
class GraphicsComponent{
public:



	/** \brief setter
	 *
	 * sets/changes mMesh
	 * @param mesh
	 */
	void setMesh(Mesh* mesh);

	/** \brief setter
	 *
	 * sets/changes mMaterial
	 * @param material
	 */
	void setMaterial(Material* material);

	/** \brief getter
	 *
	 * @return mMesh
	 */

	Mesh* getMesh();

	/** \brief getter
	 *
	 * @return mMaterial
	 */
	Material* getMaterial();

	/** \brief setter
	 *
	 * sets/changes mDynamic
	 * @param value
	 */
	void setDynamic(bool value);

	/** \brief checks if graphic component is dynamic
	 *
	 * @return true or false
	 */
	bool isDynamic();

	/** \brief setter
	 *
	 * sets/changes the modelMatrixGc
	 * @param matrix
	 */
	void setModelMatrixGc(glm::mat4 matrix);

	/** \brief getter
	 *
	 * @return the modelMatrixGc
	 */
	glm::mat4 getModelMatrix();


	/** \brief setter
	 *
	 * turns the emission either "on" or "off"
	 * @param value
	 * @todo default value?
	 * @todo which value means what?
	 */
	void setEmission(bool value);

	/** \brief setter
	 *
	 * turns the the ability to cast shadows of this component either "on" or "off"
	 * @param value
	 * @todo default value?
	 * @todo which value means what?
	 */
	void setShadow(bool value);

	/** \brief setter
	 *
	 * sets if the component is transparent or not
	 * @param value
	 * @todo default value?
	 * @todo which value means what?
	 */
	void setTransparency(bool value);

	/** \brief checks if graphic component has emission
	 *
	 * @return 1 if component has emission turned on
	 * @return 0 if it has emission turned off
	 */
	bool hasEmission();

	/** \brief checks if graphic component has shadow
	 *
	 * @return 1 if component casts shadows
	 * @return 0 if component has shadows turned off
	 */
	bool hasShadow();

	/** \brief checks if graphic component has transparency
	 *
	 * @return 1 if component is transparent
	 * @return 0 if component is not transparent
	 */
	bool hasTransparency();

	/** brief setter
	 *
	 * @param min,max
	 */
	void setGhostObject(glm::vec3 min, glm::vec3 max);

	/** brief getter
	 *
	 * @return mGhostObject
	 */
	btGhostObject* getGhostObject();

	/** \brief adds Bone*
	 *
	 *@param bone
	 */

	void addBone(Bone* bone);

	/** brief getter
	 *
	 * @return mBones
	 */
	vector<Bone*> getBones();

	/** \brief setter
	 *
	 * sets if the component has animation or not
	 * @param animated
	 * @todo default value?
	 * @todo which value means what?
	 */

	void setAnimated(bool animated);

	/** \brief checks if graphic component has animation
	 *
	 * @return 1 if component is transparent
	 * @return 0 if component is not transparent
	 */
	bool hasAnimation();

	/** \brief default constructor without parameters
	 *
	 */
	GraphicsComponent();

	/** \brief constructor
	 *
	 * @param mesh
	 * @param material
	 */

	GraphicsComponent(Mesh* mesh, Material* material);


private:
	Mesh *mMesh;					/**< !docu pls! */
	Material *mMaterial;			/**< !docu pls! */

	vector<Bone*> mBones;

	glm::mat4 modelMatrixGc;		/**< !docu pls! */

	btGhostObject *mGhostObject;	/**< !docu pls! */

	bool mAnimated;					/**< !docu pls! */
	bool mDynamic;					/**< !docu pls! */
	bool mEmission;					/**< !docu pls! */
	bool mShadow;					/**< !docu pls! */
	bool mTranparency;				/**< !docu pls! */


};


#endif /* GRAPHICSCOMPONENT_H */
