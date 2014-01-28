 class UploadUniformModelMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 void UploadUniformModelMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();

 	glm::mat4 model = currentVO->getModelMatrix();
 	shader->uploadUniform(model, "uniformModel");
 }

 class UploadUniformViewMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 void UploadUniformViewMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	Camera* activeCamera = RenderManager::getInstance()->getCamera();
	
 	glm::mat4 view = activeCamera->getViewMatrix();
 	shader->uploadUniform(view, "uniformView");
 }

 class UploadUniformProjectionMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 void UploadUniformProjectionMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	
 	glm::mat4 model = RenderManager::getInstance()->getProjectionMatrix();
 	shader->uploadUniform(model, "uniformProjection");
 }

 class UploadUniformInverseModelViewMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 void UploadUniformInverseModelViewMatrixListener::update(){
 	Shader* shader = RenderManager::getInstance()->getCurrentShader();
 	VirtualObject* currentVO = RenderManager::getInstance()->getCurrentVO();
 	Camera* activeCamera = RenderManager::getInstance()->getCamera();
	
 	glm::mat4 model = currentVO->getModelMatrix();
 	glm::mat4 view = activeCamera->getViewMatrix();

 	glm::mat4 transposeInverseModelView = glm::transpose(glm::inverse(view * model));

 	shader->uploadUniform(transposeInverseModelView, "uniformInverse");
 }
