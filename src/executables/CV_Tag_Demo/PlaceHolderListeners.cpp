#include "PlaceHolderListeners.h"
#include <iostream>

/******************* FEATURE UNDER WATER *********************/

UnderwaterScene::SetClearColorListener::SetClearColorListener(float r, float g,
		float b, float a) {
	this->clearColorVec3 = new glm::vec3(r, g, b);
	this->clearColorVec4 = 0;
	this->a = a;
}

UnderwaterScene::SetClearColorListener::SetClearColorListener(
		glm::vec3* clearColor, float a) {
	this->clearColorVec3 = clearColor;
	this->clearColorVec4 = 0;
	this->a = a;
}

UnderwaterScene::SetClearColorListener::SetClearColorListener(
		glm::vec4* clearColor) {
	this->clearColorVec4 = clearColor;
	this->clearColorVec3 = 0;
	this->a = a;
}

void UnderwaterScene::SetClearColorListener::update() {
	if (clearColorVec4 == 0) {
		glClearColor(clearColorVec3->x, clearColorVec3->y, clearColorVec3->z,
				a);
	} else {
		glClearColor(clearColorVec4->r, clearColorVec4->g, clearColorVec4->b,
				clearColorVec4->a);
	}
}

UnderwaterScene::UnderOrAboveWaterListener::UnderOrAboveWaterListener(
		Camera* cam, float* sea_level_y) {
	this->cam = cam;
	this->sea_level_y = sea_level_y;
	underwater = false;
}

void UnderwaterScene::UnderOrAboveWaterListener::update() {
	if (cam->getPosition().y < *(this->sea_level_y)) {
		if (!underwater) {

			notify("ENTER_WATER");

			underwater = true;
		}
	} else {
		if (underwater) {

			notify("EXIT_WATER");

			underwater = false;
		}
	}
}

void UnderwaterScene::UnderOrAboveWaterListener::attachListenerOnEnterWater(
		Listener* listener) {
	listener->setName("ENTER_WATER");
	attach(listener);
}

void UnderwaterScene::UnderOrAboveWaterListener::attachListenerOnExitWater(
		Listener* listener) {
	listener->setName("EXIT_WATER");
	attach(listener);
}

UnderwaterScene::UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(
		Camera* cam, Camera* cam_target, float* water_height) {
	this->water_height = water_height;
	this->cam_source = cam;
	this->cam_target = cam_target;
}

UnderwaterScene::UpdateReflectedCameraPositionListener::UpdateReflectedCameraPositionListener(
		Camera* cam, Camera* cam_target, float water_height) {
	this->water_height = new float(water_height);
	this->cam_source = cam;
	this->cam_target = cam_target;
}

void UnderwaterScene::UpdateReflectedCameraPositionListener::update() {
	glm::vec3 reflected_campos = cam_source->getPosition();
	glm::vec3 reflected_center = cam_source->getPosition()
			+ cam_source->getViewDirection();
	reflected_campos.y = 2.0f * *water_height - reflected_campos.y;
	reflected_center.y = 2.0f * *water_height - reflected_center.y;
	(*cam_target).setPosition(reflected_campos);
	(*cam_target).setCenter(reflected_center);
}

UnderwaterScene::UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(
		std::string name, float* t, float frequency, float phase,
		std::string uniform_name) {
	this->t = t;
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

UnderwaterScene::UploadUniformSinusWaveListener::UploadUniformSinusWaveListener(
		std::string name, float t, float frequency, float phase,
		std::string uniform_name) {
	this->t = new float(t);
	this->frequency = frequency;
	this->phase = phase;
	this->uniform_name = uniform_name;
	setName(name);
}

void UnderwaterScene::UploadUniformSinusWaveListener::update() {
	float sinus = std::sin((*t) * frequency + phase);

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform(sinus, uniform_name);
}
UnderwaterScene::UpdateParticleSystemListener::UpdateParticleSystemListener(
		ParticleSystem* particleSystem, float* t) {
	this->particleSystem = particleSystem;
	this->t = t;
}

void UnderwaterScene::UpdateParticleSystemListener::update() {
	particleSystem->update(*t);
}

UnderwaterScene::KeepOffsetListener::KeepOffsetListener(VirtualObject* vo,
		glm::vec3* target, glm::vec3* offset) {

	this->vo = vo;
	this->target = target;
	this->offset = offset;

	if (!offset) {
		offset = new glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void UnderwaterScene::KeepOffsetListener::update() {
	glm::vec3 targetPosition = *target + *offset;
	vo->getPhysicsComponent()->setPosition(targetPosition.x, targetPosition.y,
			targetPosition.z);
	vo->updateModelMatrixViaPhysics();
}

UnderwaterScene::SetCameraListener::SetCameraListener(Camera* cam){
	this->cam = cam;
}

UnderwaterScene::SetCameraPositionListener::SetCameraPositionListener(Camera* cam, glm::vec3 position){
	this->cam 			= cam;
	this->position = position;
}
void UnderwaterScene::SetCameraPositionListener::update(){
	cam->setPosition(position);
}

void UnderwaterScene::SetCameraListener::update(){
	RenderManager::getInstance()->setCamera(cam);
}

OculusFeature::SetViewPortListener::SetViewPortListener(int x, int y, int width,
		int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void OculusFeature::SetViewPortListener::update() {
	RenderManager::getInstance()->setViewPort(x,y,width,height);
}

OculusFeature::StereoRenderPassActivateRenderEyeSettingsListener::StereoRenderPassActivateRenderEyeSettingsListener(
		RenderPass* renderPass, Oculus* oculus, OculusCamera* oculusCam,
		OVR::Util::Render::StereoEye eye, bool isActiveEye)
: setEyeListener(oculusCam, eye)
, setViewPortListener(
			(eye == OVR::Util::Render::StereoEye_Left) ?
					renderPass->getViewPortX() :
					renderPass->getViewPortX()
							+ renderPass->getViewPortWidth() / 2,
			renderPass->getViewPortY(),
			renderPass->getViewPortWidth() / 2,
			renderPass->getViewPortHeight())
, setPerspectiveListener(oculus, eye)
{
this->renderPass = renderPass;
this->eye = eye;
this->isActiveEye = isActiveEye;

this->defaultClearColorBufferSetting = renderPass->getClearColorBufferBit();
this->defaultClearDepthBufferSetting = renderPass->getClearDepthBufferBit();
}

void OculusFeature::StereoRenderPassActivateRenderEyeSettingsListener::update()
{
	if ( isActiveEye )
	{
		isActiveEye = false;

		setEyeListener.update();
		setViewPortListener.update();
		setPerspectiveListener.update();

		if ( eye == OVR::Util::Render::StereoEye_Right )
		{	// make sure left eye render will not be cleared
			renderPass->setClearColorBufferBit( false );
			renderPass->setClearDepthBufferBit( false );
		}

		notify("EYE_SETTINGS_ACTIVATION");

	}
	else{	// war nicht aktiv, beim n�chstem mal aber
		isActiveEye = true;

		if ( eye == OVR::Util::Render::StereoEye_Right )
		{	// make sure default clear color buffer setting is active for left eye
			renderPass->setClearColorBufferBit( defaultClearColorBufferSetting );
			renderPass->setClearDepthBufferBit( defaultClearDepthBufferSetting );
		}
	}
}

void OculusFeature::StereoRenderPassActivateRenderEyeSettingsListener::attachListenerOnEyeSettingsActivation( Listener* listener )
{
	listener->setName("EYE_SETTINGS_ACTIVATION");
	attach(listener);
}

OculusFeature::StereoRenderPassRenderAgainListener::StereoRenderPassRenderAgainListener(
		RenderPass* renderPass)
{
		this->renderPass = renderPass;
		shouldRender = true;
}



void OculusFeature::StereoRenderPassRenderAgainListener::update() {
	{
		if (shouldRender) {
			shouldRender = false;

			renderPass->activate();
			renderPass->render();
			renderPass->deactivate();

			return;
		} else {	// will trigger next time again
			shouldRender = true;
			return;
		}
	}
}

void UnderwaterScene::SetCameraListener::setCamera(Camera* cam) {
	this->cam = cam;
}

void UnderwaterScene::UpdateReflectedCameraPositionListener::setCamSource(
		Camera* camera) {
	this->cam_source = camera;
}

void UnderwaterScene::UpdateReflectedCameraPositionListener::setCamTarget(
		Camera* camera) {
	this->cam_target = camera;
}

UpdateBoidsListener::UpdateBoidsListener(Flock* flock){
	mFlock = flock;
}
void UpdateBoidsListener::update(){
	mFlock->update(IOManager::getInstance()->getDeltaTime());
}

UpdateBoidsSwimCycleListener::UpdateBoidsSwimCycleListener(Flock* flock){
	mFlock = flock;
}
void UpdateBoidsSwimCycleListener::update(){
	float angle = glfwGetTime() / 5.0f;
	mFlock->setPlaceToGo(glm::vec3(glm::sin(angle) * 10.0f, 4.0f, glm::cos(angle) * 5.0f));
}

UpdateBoidsAvoidanceListener::UpdateBoidsAvoidanceListener(Flock* flock){
	mFlock = flock;
}
void UpdateBoidsAvoidanceListener::update(){
	glm::vec3 camposition = RenderManager::getInstance()->getCamera()->getPosition();
	mFlock->setPlaceToAvoid(camposition);
}

UpdateAnimationLoopListener::UpdateAnimationLoopListener(AnimationLoop* animation){
	mAnimation = animation;
}
void UpdateAnimationLoopListener::update(){
	mAnimation->updateNodes(glfwGetTime());
}

LookAtCameraListener::LookAtCameraListener(VirtualObject* vo, glm::mat4 mat, glm::vec3 pos){
	mVO = vo;
	mMat = mat;
	mPos = pos;
}
void LookAtCameraListener::update(){
	glm::vec3 orientation = RenderManager::getInstance()->getCamera()->getPosition() - mPos;
	glm::vec3 initial = glm::vec3(1.0f, 0.0f, 0.0f);

	orientation = orientation / glm::length(orientation);

	if(orientation == initial){
		mVO->setModelMatrix(mMat);
		return;}

	glm::vec3 axis = glm::cross(initial, orientation);
		axis = glm::vec3(0.0f, axis.y, axis.z);
		axis /= glm::length(axis);

		float angle = glm::dot(orientation, initial);
		angle = glm::acos(angle);

		glm::mat4 rot_matrix = glm::rotate(glm::mat4(), glm::degrees(angle), axis);

		mVO->setModelMatrix(rot_matrix * mMat);

}

UploadUniformAirListener::UploadUniformAirListener(std::string name, std::string uniform_name, float maxAir){
	this->maxAir = maxAir;
	airLeft = 1.0f;
	this->uniform_name = uniform_name;
	this->windowTime = NULL;			//no window time before application is running
	startTime = 0;
	this->camPosition = NULL;			//same same here
	timeUnderWater = 1.0f;
}

void UploadUniformAirListener::update(){
	if ( windowTime == NULL)																//initialise after application boot
		this->windowTime =  IOManager::getInstance()->getWindowTimePointer();
	if ( startTime == 0)
		startTime = IOManager::getInstance()->getWindowTime();								//same same
	if ( camPosition == NULL)
		camPosition = RenderManager::getInstance()->getCamera()->getPositionPointer();		//same same

	if ( camPosition->y < 10.0){						//test if under or above water surface
		if ( timeUnderWater != 0.0){					//test if already underwater or just diving in
			timeUnderWater = *windowTime - startTime;	//update time (under water)
		}
		else {
			timeUnderWater = 1.0;
			startTime = *windowTime;					//when diving in, start counting the time (under water)
		}

	}
	else
		timeUnderWater = 0.0;							//restore air when above water surface (while being under water before)

	airLeft = (maxAir - timeUnderWater) / maxAir;		//noralize

	//-------------------------------------

	Shader* shader = RenderManager::getInstance()->getCurrentShader();
	shader->uploadUniform( airLeft, uniform_name);		//upload uniform

}
