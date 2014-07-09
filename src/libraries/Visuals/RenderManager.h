#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
//#include "IO/IOManager.h"   @todo problem due to multiple includes of glfw and stuff
#include "Visuals/RenderQueue.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"
#include "IO/Camera.h"
#include "Visuals/Shader.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/RenderLoop.h"
#include "Visuals/Frustum.h"


/// RenderManager is a Singleton and can be called by getInstance(), it is also a Subject
class RenderManager : public Singleton<RenderManager>, public Subject{
	friend class Singleton <RenderManager>;  //nötig damit Singleton Zugriff auf private und protected Membervariablen von RenderManager hat
protected:
	/** \brief constructor
	 *
	 */
	RenderManager();
public:
	/** \brief destructor
	 *
	 */
    ~RenderManager ();
	//RenderQueue renderQueue;

    /** \brief setter
     *
     * sets/changes mRenderqueue
     * @param currentRQ
     */
	void setRenderQueue(RenderQueue* currentRQ);

    /** \brief setter
     *
     * sets/changes mCamera
     * @param camera
     */
	void setCamera(Camera* camera);

    /** \brief setter
     *
     * @param gc
     */
	void setCurrentGC(GraphicsComponent* gc);

    /** \brief setter
     *
     * sets/changes mCurrentShader
     * @param shader
     */
	void setCurrentShader(Shader* shader);

    /** \brief setter
     *
     * sets/changes mCurrentFBO
     * @param fbo
     */
	void setCurrentFBO(FrameBufferObject* fbo);

    /** \brief setter
     *
     * sets/changes mRenderLoop
     * @param renderLoop
     */
	void setRenderLoop(RenderLoop* renderLoop);

    /** \brief setter
     *
     * @param fovy,aspect,near,far
     */
	void setPerspectiveMatrix(float fovy, float aspect, float near, float far);

    /** \brief setter
     *
     */
	void setDefaultPerspectiveMatrix();

    /** \brief setter
     *
     * sets/changes mFrustum
     * @param frustum
     */
	void setCurrentFrustum(Frustum* frustum);

    /** \brief setter
     *
     * @param pos
     * @param index
     */
	void setLightPosition (glm::vec3 pos, int index);


	/** \brief setter
	 *
	 * set the active viewport
	 */
	void setViewPort( glm::vec4 viewPort );

	/** \brief setter
	 *
	 * set the active viewport
	 */
	void setViewPort( float viewPort_x, float viewPort_y,  float viewPort_width, float viewPort_height );

	/** \brief getter
	 *
	 * @return mCurrentVO
	 */
	VirtualObject* getCurrentVO();

	/** \brief getter
	 *
	 * @return mCurrentGC
	 */
	GraphicsComponent* getCurrentGC();

	/** \brief getter
	 *
	 * @return mCurrentShader
	 */
	Shader* getCurrentShader();

	/** \brief getter
	 *
	 * @return mCamera
	 */
	Camera* getCamera();

	/** \brief getter
	 *
	 * @return mCurrentFBO
	 */
	FrameBufferObject* getCurrentFBO();

	 /** \brief getter
     *
     * @return mCurrentRenderLoop
     */
	RenderLoop* getCurrentRenderLoop();

	/** \brief getter
	 *
	 * @return window
	 */
	GLFWwindow* getWindow();

	/** \brief getter
	 *
	 * @return active viewport
	 */
	glm::vec4 getViewPort();

	/** \brief getter
	 *
	 * @return mRenderqueue
	 */
	RenderQueue* getRenderQueue();

	/** \brief getter
	 *
	 * @return mFrustum
	 */
	Frustum* getCurrentFrustum();

	/** \brief getter
	 *
	 * @return perspective matrix
	 */
	glm::mat4 getPerspectiveMatrix();

	/** \brief getter
	 *
	 * @return light perspective matrix
	 */
	glm::mat4 getLightPerspectiveMatrix(int index);

	/** \brief getter
	 *
	 * @return position of light at index
	 */
	glm::vec3 getLightPosition(int index);

	/** \brief !docu pls!
	 *
	 */
	void libInit();

	/** \brief !docu pls!
	 *
	 */
	void manageShaderProgram();

	/** \brief !docu pls!
	 *
	 */
	void renderLoop();

	/** \brief attach listener
	 *
	 * attach a listener that will be called at the beginning of a frameloop
	 * @param listener
	 */
	void attachListenerOnNewFrame(Listener* listener);

	/** \brief attach listener
	 *
	 * attach a listener that will be called at the closure of the GLFW window
	 * @param listener
	 */
	void attachListenerOnWindowShouldClose(Listener* listener);

	/** \brief create four light sources
	 *	create four Light sources for fun
	 */
	void createFourLightsources();
private:

	GLuint vbo;							/**< !docu pls! */
	GLuint MVPHandle;					/**< !docu pls! */
	GLuint shaderProgramHandle;			/**< !docu pls! */

	GLFWwindow* window;					/**< !docu pls! */

	Frustum *mFrustum;					/**< !docu pls! */
	Camera* mCamera;					/**< !docu pls! */
	RenderQueue* mRenderqueue;			/**< !docu pls! */
	Shader* mCurrentShader;				/**< !docu pls! */
	GraphicsComponent* mCurrentGC;		/**< !docu pls! */
	VirtualObject* mCurrentVO;			/**< !docu pls! */
	FrameBufferObject* mCurrentFBO;		/**< !docu pls! */
	vector<glm::vec3> mLightPositions;	/**< !docu pls! */
	RenderLoop* mRenderLoop;		/**< current renderloop */

	glm::vec4 mViewPort;					/**< active viewport */

};

#endif /* RENDERMANAGER_H */
